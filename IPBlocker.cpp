#include "IPBlocker.h"

/**
 * @brief Constructor. Stores the block threshold and converts the IP range to numbers.
 * @param threshold Max requests before an IP is auto-blocked.
 * @param rangeStartIP Start of blocked range as a string.
 * @param rangeEndIP End of blocked range as a string.
 */
IPBlocker::IPBlocker(int threshold, string rangeStartIP, string rangeEndIP)
{
    blockThreshold = threshold;
    rangeStart = ipToNum(rangeStartIP);
    rangeEnd = ipToNum(rangeEndIP);
}

/**
 * @brief Converts an IP string "a.b.c.d" into a single long long number.
 *        For example, "192.168.1.1" becomes 192168001001.
 * @param ip The IP address string.
 * @return A long long integer representing the IP.
 */
long long IPBlocker::ipToNum(string ip)
{
    long long ipNum = 0;
    long long octet = 0;
    for (char c : ip)
    {
        if (c == '.')
        {
            ipNum = ipNum * 1000 + octet;
            octet = 0;
        }
        else
        {
            octet = octet * 10 + (c - '0');
        }
    }
    ipNum = ipNum * 1000 + octet;

    return ipNum;
}

/**
 * @brief Checks if an IP should be blocked. Also tracks how many times each IP is seen.
 *
 *        Blocking happens if:
 *        1) The IP falls within the configured blocked range, OR
 *        2) The IP has been seen more times than the threshold.
 *
 * @param ip The IP address to check.
 * @return True if blocked, false if allowed through.
 */
bool IPBlocker::isBlocked(string ip)
{
    long long ipNum = ipToNum(ip);

    if (ipNum >= rangeStart && ipNum <= rangeEnd)
    {
        return true;
    }

    if (++ipHitCount[ip] > blockThreshold)
    {
        return true;
    }

    return false;
}