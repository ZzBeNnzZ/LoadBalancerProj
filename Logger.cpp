/**
 * @file Logger.cpp
 * @brief Implements the Logger class methods.
 */

#include "Logger.h"
#include <iostream>
using namespace std;

/**
 * @brief Constructor. Opens the specified log file for writing.
 * @param fileName Path to the log file.
 */
Logger::Logger(string fileName)
{
    logFile.open(fileName);

    if (!logFile.is_open())
    {
        cout << COLOR_RED << "ERROR: Cannot open log file: " << fileName << COLOR_RESET << endl;
    }
}

/**
 * @brief Destructor. Closes the log file if it is open.
 */
Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

/**
 * @brief Outputs a message in color to the console and plain to the log file.
 * @param msg   The message to print.
 * @param color ANSI color escape code to use on the console.
 */
void Logger::log(string msg, string color)
{
    cout << color << msg << COLOR_RESET << endl;
    if (logFile.is_open())
    {
        logFile << msg << endl;
    }
}

/**
 * @brief Prints a periodic summary of the simulation state.
 * @param cycle     Current clock cycle number.
 * @param servers   Number of active web servers.
 * @param queueSize Number of requests waiting in the queue.
 */
void Logger::logCycleSummary(int cycle, int servers, int queueSize)
{
    string msg = "[CYCLE " + to_string(cycle) + "] SERVERS=" + to_string(servers) + " QUEUE_SIZE=" + to_string(queueSize);
    log(msg, COLOR_CYAN);
}
