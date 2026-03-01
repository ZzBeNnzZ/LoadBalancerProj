/**
 * @file config.h
 * @brief Defines the Config class that holds all simulation parameters.
 *
 * Parameters are loaded from a plain-text config file at startup,
 * allowing the simulation to be tuned without recompiling.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
using namespace std;

/**
 * @class Config
 * @brief Stores all tunable parameters for the load balancer simulation.
 *
 * Default values are set in the constructor. Calling loadFromFile()
 * overrides them with values from the config file.
 */
class Config
{
public:
    int initialServers;           ///< Number of web servers to start with
    int totalCycles;              ///< Total number of clock cycles to simulate
    int summaryCycles;            ///< Print a summary log every N cycles
    int initialQueue;             ///< Number of requests to pre-fill the queue with at startup
    int cooldownTime;             ///< Cycles to wait between consecutive scaling actions
    float newRequestProbability;  ///< Probability (0.0–1.0) that new requests arrive each cycle
    float streamingProbability;   ///< Probability (0.0–1.0) that a new request is type 'S' (streaming)
    int minServiceTime;           ///< Minimum clock cycles a request takes to process
    int maxServiceTime;           ///< Maximum clock cycles a request takes to process
    int ipBlockThreshold;         ///< Max requests from one IP before it is auto-blocked
    int cycleDelayMs;             ///< Milliseconds to sleep between cycles (0 = full speed)

    string logFileName;           ///< Path to the output log file
    string blockedRangeStart;     ///< Start of the IP range to block (e.g., "192.168.0.0")
    string blockedRangeEnd;       ///< End of the IP range to block (e.g., "192.168.0.255")

    /**
     * @brief Constructor. Sets all fields to sensible default values.
     */
    Config();

    /**
     * @brief Loads configuration values from a key-value text file.
     *        Any key found in the file overrides the corresponding default.
     * @param path Path to the config file (e.g., "config.txt").
     * @return True if the file was opened successfully, false otherwise.
     */
    bool loadFromFile(string path);
};

#endif