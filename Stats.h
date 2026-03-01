/**
 * @file Stats.h
 * @brief Defines the Stats class that tracks simulation statistics.
 *
 * Keeps running counts of requests generated, accepted, blocked,
 * completed, and server scaling events.
 */

#ifndef STATS_H
#define STATS_H

/**
 * @class Stats
 * @brief Tracks all statistics during the load balancer simulation.
 */
class Stats
{
public:
    long long totalRequestsGenerated;  ///< Total number of requests created during the simulation
    long long totalRequestsAccepted;   ///< Requests that passed the firewall and entered the queue
    long long totalRequestsBlocked;    ///< Requests rejected by the IPBlocker
    long long totalRequestsCompleted;  ///< Requests fully processed by a web server
    long long serverScaleUps;          ///< Number of times a server was added
    long long serverScaleDowns;        ///< Number of times a server was removed
    long long maxQueueSize;            ///< Peak queue depth recorded during the simulation

    /**
     * @brief Constructor. Initializes all counters to zero.
     */
    Stats();

    /**
     * @brief Updates the max queue size if the current size is larger.
     * @param currentQueueSize The current number of requests in the queue.
     */
    void updateQueueStats(int currentQueueSize);

    /**
     * @brief Increments the total requests generated counter.
     */
    void reqGenerated();

    /**
     * @brief Increments the total requests accepted counter.
     */
    void reqAccepted();

    /**
     * @brief Increments the total requests blocked counter.
     */
    void reqBlocked();

    /**
     * @brief Increments the total requests completed counter.
     */
    void reqCompleted();

    /**
     * @brief Increments the server scale-up counter.
     */
    void serverScaledUp();

    /**
     * @brief Increments the server scale-down counter.
     */
    void serverScaledDown();
};

#endif