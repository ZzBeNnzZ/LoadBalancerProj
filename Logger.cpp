#include "Logger.h"
#include <iostream>
using namespace std;

Logger::Logger(string fileName)
{
    logFile.open(fileName);

    if (!logFile.is_open())
    {
        cout << COLOR_RED << "ERROR: Cannot open log file: " << fileName << COLOR_RESET << endl;
    }
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

void Logger::log(string msg, string color)
{
    cout << color << msg << COLOR_RESET << endl;
    if (logFile.is_open())
    {
        logFile << msg << endl;
    }
}

void Logger::logCycleSummary(int cycle, int servers, int queueSize)
{
    string msg = "[CYCLE " + to_string(cycle) + "] SERVERS=" + to_string(servers) + " QUEUE_SIZE=" + to_string(queueSize);
    log(msg, COLOR_CYAN);
}
