#include "LoadBalancer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    Config config;
    if (config.loadFromFile("config.txt"))
    {
        cout << COLOR_CYAN << "Loaded configuration from config.txt" << COLOR_RESET << endl;
    }
    else
    {
        cout << COLOR_RED << "config.txt not found, using defaults." << COLOR_RESET << endl;
    }

    // If initialQueue was left as 0, default to servers * 100
    if (config.initialQueue == 0)
    {
        config.initialQueue = config.initialServers * 100;
    }

    // ----- Print configuration -----
    cout << COLOR_CYAN << "========================================" << COLOR_RESET << endl;
    cout << COLOR_CYAN << "     LOAD BALANCER CONFIGURATION" << COLOR_RESET << endl;
    cout << COLOR_CYAN << "========================================" << COLOR_RESET << endl;
    cout << "Initial servers:         " << config.initialServers << endl;
    cout << "Total cycles:            " << config.totalCycles << endl;
    cout << "Initial queue size:      " << config.initialQueue << endl;
    cout << "Cooldown time:           " << config.cooldownTime << " cycles" << endl;
    cout << "New request probability: " << config.newRequestProbability << endl;
    cout << "Streaming probability:   " << config.streamingProbability << endl;
    cout << "Service time range:      " << config.minServiceTime << " - " << config.maxServiceTime << endl;
    cout << "IP block threshold:      " << config.ipBlockThreshold << endl;
    cout << "Blocked IP range:        " << config.blockedRangeStart << " - " << config.blockedRangeEnd << endl;
    cout << "Log file:                " << config.logFileName << endl;
    cout << COLOR_CYAN << "========================================" << COLOR_RESET << endl;
    cout << endl;

    // ----- Create all objects -----
    Logger logger(config.logFileName);
    Stats stats;
    IPBlocker ipBlocker(config.ipBlockThreshold, config.blockedRangeStart, config.blockedRangeEnd);
    LoadBalancer loadBalancer(&config, &logger, &stats, &ipBlocker);

    // ----- Initialize servers -----
    loadBalancer.init(config.initialServers);

    // -----Generate initial queue -----
    loadBalancer.generateInitialQueue();

    // -----Run the simulation -----
    cout << endl;
    loadBalancer.run();

    cout << endl;
    cout << COLOR_GREEN << "Simulation complete successfully. Full log saved to: "
         << config.logFileName << COLOR_RESET << endl;

    return 0;
}
