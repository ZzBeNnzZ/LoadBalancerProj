#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
using namespace std;

// ----- ANSI Color Codes -----
const string COLOR_RESET = "\033[0m";
const string COLOR_RED = "\033[31m";
const string COLOR_GREEN = "\033[32m";
const string COLOR_YELLOW = "\033[33m";
const string COLOR_CYAN = "\033[36m";
const string COLOR_WHITE = "\033[37m";

class Logger
{
private:
    ofstream logFile;

public:
    Logger(string fileName);
    ~Logger();
    void log(string msg, string color = COLOR_WHITE);
    void logCycleSummary(int cycle, int servers, int queueSize);
};

#endif
