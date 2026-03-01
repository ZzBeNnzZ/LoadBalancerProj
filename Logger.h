/**
 * @file Logger.h
 * @brief Defines the Logger class and ANSI color code constants.
 *
 * The Logger writes color-coded messages to stdout and simultaneously
 * writes plain text to a log file for persistent records.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
using namespace std;

/** @brief Resets terminal color back to default. */
const string COLOR_RESET = "\033[0m";
/** @brief ANSI red — used for blocked requests and scale-down events. */
const string COLOR_RED = "\033[31m";
/** @brief ANSI green — used for completed requests. */
const string COLOR_GREEN = "\033[32m";
/** @brief ANSI yellow — used for scale-up events. */
const string COLOR_YELLOW = "\033[33m";
/** @brief ANSI cyan — used for informational messages and cycle summaries. */
const string COLOR_CYAN = "\033[36m";
/** @brief ANSI white — used for general request dispatch messages. */
const string COLOR_WHITE = "\033[37m";

/**
 * @class Logger
 * @brief Handles all output for the simulation: colored console printing
 *        and plain-text file logging.
 */
class Logger
{
private:
    ofstream logFile; ///< Output file stream for the persistent log

public:
    /**
     * @brief Constructor. Opens the log file for writing.
     * @param fileName Path to the log file (from config).
     */
    Logger(string fileName);

    /**
     * @brief Destructor. Closes the log file if it is still open.
     */
    ~Logger();

    /**
     * @brief Prints a message to the console in the given color and writes
     *        the plain-text version to the log file.
     * @param msg   The message string to output.
     * @param color ANSI color code string (defaults to COLOR_WHITE).
     */
    void log(string msg, string color = COLOR_WHITE);

    /**
     * @brief Prints and logs a periodic cycle summary line showing the
     *        current cycle number, active server count, and queue depth.
     * @param cycle     The current simulation clock cycle.
     * @param servers   Number of currently active web servers.
     * @param queueSize Number of requests currently in the queue.
     */
    void logCycleSummary(int cycle, int servers, int queueSize);
};

#endif
