/**
 * @file LoadBalancer.h
 * @brief Defines the LoadBalancer class that orchestrates the entire simulation.
 *
 * The LoadBalancer manages a queue of requests, a pool of web servers,
 * and uses the IPBlocker, Logger, Stats, and Config classes.
 *
 * Relationships (from UML):
 *   LoadBalancer --uses--> IPBlocker
 *   LoadBalancer --uses--> Logger
 *   LoadBalancer --uses--> Stats
 *   LoadBalancer --uses--> Config
 *   LoadBalancer --manages--> WebServer (many)
 *   WebServer --current (0..1)--> Request
 *   LoadBalancer queue --many--> Request
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Request.h"
#include "WebServer.h"
#include "IPBlocker.h"
#include "Logger.h"
#include "Stats.h"
#include "config.h"
#include <queue>
#include <vector>

/**
 * @class LoadBalancer
 * @brief Orchestrates the simulation: manages web servers, the request queue,
 *        dynamic scaling, firewall filtering, logging, and statistics.
 */
class LoadBalancer
{
private:
    queue<Request> requestQueue;   ///< Queue of pending requests waiting for a server
    vector<WebServer *> servers;   ///< Pool of currently active web servers
    int cooldownTimer;             ///< Cycles remaining before next scaling action is allowed

    Config *config;       ///< Pointer to the simulation configuration
    Logger *logger;       ///< Pointer to the logger for console/file output
    Stats *stats;         ///< Pointer to the statistics tracker
    IPBlocker *ipBlocker; ///< Pointer to the IP firewall/blocker

    int nextServerId; ///< Counter used to assign unique IDs to new servers

public:
    /**
     * @brief Constructor. Stores pointers to all dependency objects.
     * @param cfg Pointer to the loaded Config.
     * @param log Pointer to the Logger.
     * @param st Pointer to the Stats tracker.
     * @param blocker Pointer to the IPBlocker firewall.
     */
    LoadBalancer(Config *cfg, Logger *log, Stats *st, IPBlocker *blocker);

    /**
     * @brief Destructor. Frees all dynamically allocated WebServer objects.
     */
    ~LoadBalancer();

    /**
     * @brief Creates the initial pool of web servers.
     * @param serverCount Number of servers to start with.
     */
    void init(int serverCount);

    /**
     * @brief Fills the request queue with an initial batch of random requests.
     *        The count is controlled by config->initialQueue.
     */
    void generateInitialQueue();

    /**
     * @brief Generates a single request with random IPs, service time, and job type.
     * @return A newly created Request struct.
     */
    Request makeRandomRequest();

    /**
     * @brief Randomly generates new incoming requests each cycle based on
     *        config->newRequestProbability.
     * @param cycle The current simulation clock cycle number.
     */
    void randomIncomingRequests(int cycle);

    /**
     * @brief Ticks all active servers forward by one clock cycle and logs
     *        any requests that were just completed.
     * @param cycle The current simulation clock cycle number.
     */
    void oneCyclePast(int cycle);

    /**
     * @brief Assigns queued requests to any available (idle) servers.
     * @param cycle The current simulation clock cycle number.
     */
    void dispatchRequests(int cycle);

    /**
     * @brief Checks the queue depth and adds or removes a server if thresholds
     *        are exceeded. Respects the cooldown timer between scaling actions.
     * @param cycle The current simulation clock cycle number.
     */
    void scaleIfNeeded(int cycle);

    /**
     * @brief Runs the full simulation loop from cycle 1 to config->totalCycles.
     *        Each cycle: ticks servers, dispatches requests, generates new traffic,
     *        checks scaling, and optionally prints a summary.
     */
    void run();
};

#endif