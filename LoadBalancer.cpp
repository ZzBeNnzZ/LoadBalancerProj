#include "LoadBalancer.h"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

static int randomGenerator(int startRange, int endRange)
{
    // Use clock for unique seed
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Pseudo-random generator
    mt19937 gen(seed);

    uniform_int_distribution<int> dist(startRange, endRange);
    return dist(gen);
}

static string generateRandomIp()
{
    string ip = "";

    for (int i = 0; i < 4; i++)
    {
        ip += to_string(randomGenerator(0, 255));

        if (i < 3)
        {
            ip += '.';
        }
    }

    return ip;
}

LoadBalancer::LoadBalancer(Config *cfg, Logger *log, Stats *st, IPBlocker *blocker)
{
    config = cfg;
    logger = log;
    stats = st;
    ipBlocker = blocker;
    cooldownTimer = 0;
    nextServerId = 0;
}

LoadBalancer::~LoadBalancer()
{
    for (int i = 0; i < (int)servers.size(); i++)
    {
        delete servers[i];
    }
    servers.clear();
}

void LoadBalancer::init(int serverCount)
{
    for (int i = 0; i < serverCount; i++)
    {
        servers.push_back(new WebServer(nextServerId++));
    }

    logger->log("Initialized " + to_string(serverCount) + " web servers.", COLOR_CYAN);
}

Request LoadBalancer::makeRandomRequest()
{
    Request req;
    req.ipIn = generateRandomIp();
    req.ipOut = generateRandomIp();
    req.serviceTime = randomGenerator(config->minServiceTime, config->maxServiceTime);
    // req.serviceTime = randomGenerator(0, 50);

    // Random Generator to decide P or S
    float roll = (float)randomGenerator(0, 100) / 100.0;
    if (roll < config->streamingProbability)
    // if (roll <= 0.5)

    {
        req.jobType = 'S';
    }
    else
    {
        req.jobType = 'P';
    }

    return req;
}

void LoadBalancer::generateInitialQueue()
{
    int count = config->initialQueue;
    int accepted = 0;
    for (int i = 0; i < count; i++)
    {
        Request req = makeRandomRequest();
        stats->reqGenerated();

        if (ipBlocker->isBlocked(req.ipIn))
        {
            stats->reqBlocked();
            continue;
        }

        requestQueue.push(req);
        stats->reqAccepted();
        accepted++;

        logger->log("Generated initial queue: " + to_string(accepted) + " requests accepted, " +
                        to_string(count - accepted) + " blocked. Queue size: " +
                        to_string((int)requestQueue.size()),
                    COLOR_CYAN);
        stats->updateQueueStats((int)requestQueue.size());
    }
}

void LoadBalancer::randomIncomingRequests(int cycle)
{
    float roll = (float)randomGenerator(0, 100) / 100.0;
    if (roll >= config->newRequestProbability)
    {
        return;
    }

    // Random number of request coming in
    int count = randomGenerator(1, 10);
    int accepted = 0;

    for (int i = 0; i < count; i++)
    {
        Request req = makeRandomRequest();
        stats->reqGenerated();

        if (ipBlocker->isBlocked(req.ipIn))
        {
            stats->reqBlocked();
            logger->log("[Cycle " + to_string(cycle) + "] BLOCKED request from " +
                            req.ipIn,
                        COLOR_RED);
            continue;
        }

        requestQueue.push(req);

        stats->reqAccepted();
        accepted++;
    }

    if (accepted > 0)
    {
        logger->log("[Cycle " + to_string(cycle) + "] " + to_string(accepted) +
                        " new request(s) arrived. Queue size: " +
                        to_string((int)requestQueue.size()),
                    COLOR_CYAN);
    }

    stats->updateQueueStats((int)requestQueue.size());
}

void LoadBalancer::oneCyclePast(int cycle)
{
    for (int i = 0; i < (int)servers.size(); i++)
    {
        bool wasBusy = !servers[i]->isAvailable();

        servers[i]->oneCycle();

        if (wasBusy && servers[i]->isAvailable())
        {
            stats->reqCompleted();
            Request done = servers[i]->getCurrentRequest();
            logger->log("[Cycle " + to_string(cycle) + "] Server " +
                            to_string(servers[i]->getId()) + " completed request from " +
                            done.ipIn + " -> " + done.ipOut +
                            " (type: " + done.jobType + ")",
                        COLOR_GREEN);
        }
    }
}

void LoadBalancer::dispatchRequests(int cycle)
{
    for (int i = 0; i < (int)servers.size(); i++)
    {
        if (servers[i]->isAvailable() && requestQueue.size() > 0)
        {
            Request nextReq = requestQueue.front();
            requestQueue.pop();
            servers[i]->assign(nextReq);
            logger->log("[Cycle " + to_string(cycle) + "] Server " +
                            to_string(servers[i]->getId()) + " assigned with request from " +
                            nextReq.ipIn + " -> " + nextReq.ipOut +
                            " (type: " + nextReq.jobType + ", service time: " +
                            to_string(nextReq.serviceTime) + ")",
                        COLOR_WHITE);
        }
    }
}

void LoadBalancer::scaleIfNeeded(int cycle)
{
    if (cooldownTimer > 0)
    {
        cooldownTimer--;
        return;
    }

    int numServers = (int)servers.size();
    int queueSize = (int)requestQueue.size();
    int lowThreshold = 50 * numServers;
    int highThreshold = 80 * numServers;

    if (queueSize > highThreshold)
    {
        servers.push_back(new WebServer(nextServerId++));
        stats->serverScaledUp();
        cooldownTimer = config->cooldownTime;
        logger->log("[Cycle " + to_string(cycle) + "] SCALE UP: Queue=" +
                        to_string(queueSize) + " > " + to_string(highThreshold) +
                        ". Added server. Total: " + to_string((int)servers.size()),
                    COLOR_YELLOW);
    }
    else if (queueSize < lowThreshold && numServers > 1)
    {
        // Queue is too small — remove a server (keep at least 1)
        delete servers.back();
        servers.pop_back();
        stats->serverScaledDown();
        cooldownTimer = config->cooldownTime;
        logger->log("[Cycle " + to_string(cycle) + "] SCALE DOWN: Queue=" +
                        to_string(queueSize) + " < " + to_string(lowThreshold) +
                        ". Removed server. Total: " + to_string((int)servers.size()),
                    COLOR_RED);
    }
}
void LoadBalancer::run()
{
    for (int cycle = 1; cycle < config->totalCycles; cycle++)
    {
        oneCyclePast(cycle);
        dispatchRequests(cycle); // assign jobs
        randomIncomingRequests(cycle);
        scaleIfNeeded(cycle);

        if (cycle % config->summaryCycles == 0)
        {
            // status every summaryCycles (defined with config) cycles
            logger->logCycleSummary(cycle, (int)servers.size(), (int)requestQueue.size());
        }

        this_thread::sleep_for(chrono::milliseconds(config->cycleDelayMs));
    }
}

// int main()
// {
//     for (int i = 0; i < 10; i++)
//     {
//         Request req = makeRandomRequest();
//         cout << "REQUEST content: " << endl;
//         cout << req.ipIn << " -> " << req.ipOut << endl;
//         cout << "service time: " << req.serviceTime << endl;
//         cout << "job type: " << req.jobType << endl;
//     }
// }