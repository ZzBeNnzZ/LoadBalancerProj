#ifndef CONFIG_H
#define CONFIG_H

#include <string>
using namespace std;

class Config
{
public:
    int initialServers;
    int totalCycles;
    int summaryCycles;
    int initialQueue;
    int cooldownTime;
    float newRequestProbability;
    float streamingProbability;
    int minServiceTime;
    int maxServiceTime;
    int ipBlockThreshold;
    int cycleDelayMs;

    string logFileName;
    string blockedRangeStart;
    string blockedRangeEnd;

    Config();
    bool loadFromFile(string path);
};

#endif