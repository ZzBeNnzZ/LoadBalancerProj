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

class LoadBalancer
{
private:
    queue<Request> requestQueue;
    vector<WebServer *> servers;
    int cooldownTimer;

    Config *config;
    Logger *logger;
    Stats *stats;
    IPBlocker *ipBlocker;

    int nextServerId; // Unique ID for new servers

public:
    LoadBalancer(Config *cfg, Logger *log, Stats *st, IPBlocker *blocker);
    ~LoadBalancer();
    void init(int serverCount); // Create starting servers
    void generateInitialQueue();
    Request makeRandomRequest();
    void randomIncomingRequests(int cycle);
    void oneCyclePast(int cycle);
    void dispatchRequests(int cycle);
    void scaleIfNeeded(int cycle);
    void run();
};

#endif