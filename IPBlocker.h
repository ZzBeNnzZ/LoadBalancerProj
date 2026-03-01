/**
 * @file IPBlocker.h
 * @brief Defines the IPBlocker class that acts as a simple firewall.
 *
 * Blocks IPs that fall within a configurable range, and also
 * blocks individual IPs that send too many requests (DOS prevention).
 */

#ifndef IPBLOCKER_H
#define IPBLOCKER_H

#include <string>
#include <vector>
#include <map>
using namespace std;

class IPBlocker
{
private:
    map<string, int> ipHitCount;
    int blockThreshold;
    long long rangeStart;
    long long rangeEnd;

    /**
     * @brief Converts an IP address string like "192.168.1.1" to a single long number.
     *        This makes it easy to check if an IP falls within a range.
     * @param ip The IP address string.
     * @return The IP as a long integer.
     */
    long long ipToNum(string ip);

public:
    /**
     * @brief Constructor. Sets up the blocker with a threshold and an IP range to block.
     * @param threshold Number of requests before an IP gets auto-blocked.
     * @param rangeStartIP Starting IP of the blocked range (e.g., "192.168.0.0").
     * @param rangeEndIP Ending IP of the blocked range (e.g., "192.168.0.255").
     */
    IPBlocker(int threshold, string rangeStartIP, string rangeEndIP);

    /**
     * @brief Checks if a given IP address should be blocked.
     *        An IP is blocked if:
     *        1) It falls within the blocked IP range, OR
     *        2) It has sent more requests than the threshold.
     *
     *        This method also increments the hit count for the IP.
     *
     * @param ip The IP address to check.
     * @return True if the IP is blocked, false if it is allowed.
     */
    bool isBlocked(string ip);
};

#endif