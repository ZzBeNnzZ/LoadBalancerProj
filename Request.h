#ifndef REQUEST_H
#define REQUEST_H

#include <string>
using namespace std;

struct Request
{
    string ipIn;
    string ipOut;
    int serviceTime;
    char jobType; // P for processing, S for streaming
};

#endif
