/**
 * @file Stats.cpp
 * @brief Implements the Stats class methods.
 */

#include "Stats.h"
using namespace std;

/**
 * @brief Constructor. Sets all counters to zero.
 */
Stats::Stats()
{
    totalRequestsGenerated = 0;
    totalRequestsAccepted = 0;
    totalRequestsBlocked = 0;
    totalRequestsCompleted = 0;
    serverScaleUps = 0;
    serverScaleDowns = 0;
    maxQueueSize = 0;
}

/**
 * @brief Checks if the current queue size is the new maximum.
 * @param currentQueueSize The queue size right now.
 */
void Stats::updateQueueStats(int currentQueueSize)
{
    if (currentQueueSize > maxQueueSize)
    {
        maxQueueSize = currentQueueSize;
    }
}

/**
 * @brief Adds 1 to requests generated.
 */
void Stats::reqGenerated()
{
    totalRequestsGenerated++;
}

/**
 * @brief Adds 1 to requests accepted (passed firewall).
 */
void Stats::reqAccepted()
{
    totalRequestsAccepted++;
}

/**
 * @brief Adds 1 to requests blocked by the IP blocker.
 */
void Stats::reqBlocked()
{
    totalRequestsBlocked++;
}

/**
 * @brief Adds 1 to requests fully completed by a server.
 */
void Stats::reqCompleted()
{
    totalRequestsCompleted++;
}

/**
 * @brief Adds 1 to the server scale-up counter.
 */
void Stats::serverScaledUp()
{
    serverScaleUps++;
}

/**
 * @brief Adds 1 to the server scale-down counter.
 */
void Stats::serverScaledDown()
{
    serverScaleDowns++;
}
