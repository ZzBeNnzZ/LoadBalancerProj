#include "config.h"
#include <fstream>
#include <iostream>
using namespace std;

Config::Config()
{
    initialServers = 10;
    totalCycles = 10000;
    summaryCycles = 1000;
    initialQueue = 0;
    cooldownTime = 20;
    newRequestProbability = 0.2;
    streamingProbability = 0.5;
    minServiceTime = 5;
    maxServiceTime = 50;
    ipBlockThreshold = 100;
    cycleDelayMs = 0;
    logFileName = "log.txt";
    blockedRangeStart = "192.168.0.0";
    blockedRangeEnd = "192.168.0.255";
}

bool Config::loadFromFile(string path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        return false;
    }

    string key;
    while (file >> key)
    {
        string val;
        file >> val;
        if (key == "initialServers")
        {
            initialServers = stoi(val);
        }
        else if (key == "summaryCycles")
        {
            summaryCycles = stoi(val);
        }
        else if (key == "totalCycles")
        {
            totalCycles = stoi(val);
        }
        else if (key == "initialQueue")
        {
            initialQueue = stoi(val);
        }
        else if (key == "cooldownTime")
        {
            cooldownTime = stoi(val);
        }
        else if (key == "newRequestProbability")
        {
            newRequestProbability = stof(val);
        }
        else if (key == "streamingProbability")
        {
            streamingProbability = stof(val);
        }
        else if (key == "minServiceTime")
        {
            minServiceTime = stoi(val);
        }
        else if (key == "maxServiceTime")
        {
            maxServiceTime = stoi(val);
        }
        else if (key == "ipBlockThreshold")
        {
            ipBlockThreshold = stoi(val);
        }
        else if (key == "cycleDelayMs")
        {
            cycleDelayMs = stoi(val);
        }
        else if (key == "logFileName")
        {
            logFileName = val;
        }
        else if (key == "blockedRangeStart")
        {
            blockedRangeStart = val;
        }
        else if (key == "blockedRangeEnd")
        {
            blockedRangeEnd = val;
        }
    }

    file.close();
    return true;
}