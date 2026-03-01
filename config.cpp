#include "config.h"
#include <fstream>
#include <iostream>
using namespace std;

Config::Config()
{
    initialServers = 10;
    totalCycles = 10000;
    initialQueue = 0;
    cooldownTime = 20;
    newRequestProbability = 0.2;
    streamingProbability = 0.5;
    minServiceTime = 5;
    maxServiceTime = 50;
    ipBlockThreshold = 100;
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
        int val;
        file >> val;
        if (key == "initialServers")
        {
            initialServers = val;
        }
        else if (key == "totalCycles")
        {
            totalCycles = val;
        }
        else if (key == "initialQueue")
        {
            initialQueue = val;
        }
        else if (key == "cooldownTime")
        {
            cooldownTime = val;
        }
        else if (key == "newRequestProbability")
        {
            newRequestProbability = val;
        }
        else if (key == "streamingProbability")
        {
            streamingProbability = val;
        }
        else if (key == "minServiceTime")
        {
            minServiceTime = val;
        }
        else if (key == "maxServiceTime")
        {
            maxServiceTime = val;
        }
        else if (key == "ipBlockThreshold")
        {
            ipBlockThreshold = val;
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