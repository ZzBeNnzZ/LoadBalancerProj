# CSCE 412 — Project 3: Load Balancer

A C++ simulation of a load-balancing system that dynamically manages web servers to handle incoming requests, with firewall/DoS protection and real-time statistics tracking.

## Features

- Dynamic web server scaling based on queue depth
- Request queue with random IP generation and job types (Processing / Streaming)
- IP range blocker and DoS prevention firewall
- Color-coded console output with ANSI escape codes
- File-based configuration (no need to recompile to adjust parameters)
- Persistent log file with per-cycle summaries
- Runtime statistics: requests generated, accepted, blocked, completed, and server scale events
- Configurable per-cycle delay to control simulation speed

## Project Structure

| File | Description |
|---|---|
| `Request.h` | Struct holding a single request (IP in/out, service time, job type) |
| `config.h / config.cpp` | Loads simulation parameters from a config file |
| `Logger.h / Logger.cpp` | Handles colored console output and log file writing |
| `IPBlocker.h / IPBlocker.cpp` | Firewall — blocks IP ranges and rate-limits repeat requesters |
| `Stats.h / Stats.cpp` | Tracks simulation-wide counters and scaling events |
| `WebServer.h / WebServer.cpp` | Models a single web server that processes one request at a time |
| `LoadBalancer.h / LoadBalancer.cpp` | Orchestrates the simulation: manages servers, queue, scaling, and logging |

## Configuration

Edit the config file (default: `config.txt`) to adjust simulation parameters without recompiling.
Each line is a key followed by a value separated by a space:

```
initialServers 10
totalCycles 10000
initialQueue 0
cooldownTime 20
newRequestProbability 0.2
streamingProbability 0.5
minServiceTime 5
maxServiceTime 50
ipBlockThreshold 100
logFileName log.txt
blockedRangeStart 192.168.0.0
blockedRangeEnd 192.168.0.255
summaryCycles 10
cycleDelayMs 100
```

| Parameter | Description |
|---|---|
| `initialServers` | Number of web servers to start with |
| `totalCycles` | Total clock cycles to simulate |
| `initialQueue` | Number of requests to pre-fill the queue at startup |
| `cooldownTime` | Cycles to wait between scaling actions |
| `newRequestProbability` | Probability (0.0–1.0) that new requests arrive each cycle |
| `streamingProbability` | Probability (0.0–1.0) that a request is type Streaming |
| `minServiceTime` | Minimum cycles a request takes to process |
| `maxServiceTime` | Maximum cycles a request takes to process |
| `ipBlockThreshold` | Max requests from one IP before auto-blocking it |
| `logFileName` | Output log file path |
| `blockedRangeStart` | Start of the IP range to block (firewall) |
| `blockedRangeEnd` | End of the IP range to block (firewall) |
| `summaryCycles` | Print a status summary every N cycles |
| `cycleDelayMs` | Milliseconds to sleep between cycles (0 = full speed) |

## Building

```bash
make
```

## Running

```bash
./loadbalancer
```

All parameters are read from `config.txt`. Edit that file to change the simulation behavior — no recompile needed.

## Dynamic Scaling Logic

| Condition | Action |
|---|---|
| Queue size < `50 * servers` | Remove 1 server, wait `cooldownTime` cycles before checking again |
| Queue size > `80 * servers` | Add 1 server, wait `cooldownTime` cycles before checking again |

## Output Colors

| Color | Meaning |
|---|---|
| Green | Request completed by a server |
| Red | Request blocked by firewall, or server scaled down |
| Yellow | Server scaled up |
| Cyan | Informational messages and cycle summaries |
| White | Request dispatched to a server |

The full log is written to the file specified by `logFileName` in the config (default: `log.txt`).

## Author

QUANG HUY LE - TAMU CSCE 412
