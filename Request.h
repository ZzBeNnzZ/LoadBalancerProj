/**
 * @file Request.h
 * @brief Defines the Request struct that holds a single web request.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

/**
 * @struct Request
 * @brief Represents a single incoming web request to be processed by a server.
 */
struct Request
{
    string ipIn;      ///< Source IP address of the requester
    string ipOut;     ///< Destination IP address for the response
    int serviceTime;  ///< Number of clock cycles needed to process this request
    char jobType;     ///< Job type: 'P' for Processing, 'S' for Streaming
};

#endif
