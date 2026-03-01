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
    long long totalRequestsGenerated;
    long long totalRequestsAccepted;
    long long totalRequestsBlocked;
    long long totalRequestsCompleted;
    long long serverScaleUps;
    long long serverScaleDowns;
    long long maxQueueSize;

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