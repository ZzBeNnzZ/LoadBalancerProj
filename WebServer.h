/**
 * @file WebServer.h
 * @brief Defines the WebServer class that processes one request at a time.
 *
 * Each server has an ID, tracks whether it's busy, and counts down
 * the remaining cycles for the current request.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"
using namespace std;

/**
 * @class WebServer
 * @brief Simulates a single web server that processes requests one at a time.
 */
class WebServer
{
private:
    int serverId;
    bool busy;
    int remainingCycle;
    Request currentRequest;

public:
    /**
     * @brief Constructor. Creates a server with the given ID, initially not busy.
     * @param id The unique ID for this server.
     */
    WebServer(int id);

    /**
     * @brief Checks if the server is free to take a new request.
     * @return True if the server is NOT busy, false if it is busy.
     */
    bool isAvailable();

    /**
     * @brief Assigns a new request to this server and starts processing it.
     * @param req The Request to process.
     */
    void assign(Request req);

    /**
     * @brief Simulates one clock cycle of work. Decrements remaining time by 1.
     *        When time reaches 0, the server becomes free.
     */
    void oneCycle();

    /**
     * @brief Checks if the server just finished its current request this cycle.
     *        (i.e., it was busy and remaining time just hit 0.)
     * @return True if a job was just completed, false otherwise.
     */
    bool finishedJob();

    /**
     * @brief Gets the server's unique ID.
     * @return The server ID number.
     */
    int getId();

    /**
     * @brief Gets the request currently assigned to this server.
     * @return The current Request struct.
     */
    Request getCurrentRequest();
};

#endif