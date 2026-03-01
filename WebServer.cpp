/**
 * @file WebServer.cpp
 * @brief Implements the WebServer class methods.
 */

#include "WebServer.h"

WebServer::WebServer(int id)
{
    serverId = id;
    busy = false;
    remainingCycle = 0;
}

bool WebServer::isAvailable()
{
    return !busy;
}

void WebServer::assign(Request req)
{
    currentRequest = req;
    remainingCycle = req.serviceTime;
    busy = true;
}

void WebServer::oneCycle()
{
    if (busy)
    {
        remainingCycle--;
        if (remainingCycle <= 0)
        {
            busy = false;
        }
    }
}

bool WebServer::finishedJob()
{
    return (!busy && remainingCycle <= 0 && currentRequest.serviceTime > 0);
}

int WebServer::getId()
{
    return serverId;
}

Request WebServer::getCurrentRequest()
{
    return currentRequest;
}
