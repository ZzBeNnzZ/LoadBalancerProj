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

## Project Structure

| File | Description |
|---|---|
| `Request.h` | Struct holding a single request (IP in/out, service time, job type) |
| `config.h / config.cpp` | Loads simulation parameters from a config file |
| `Logger.h / Logger.cpp` | Handles colored console output and log file writing |
| `IPBlocker.h / IPBlocker.cpp` | Firewall — blocks IP ranges and rate-limits repeat requesters |
| `Stats.h / Stats.cpp` | Tracks simulation-wide counters and scaling events |

## Configuration

Edit the config file (default: `config.txt`) to adjust simulation parameters without recompiling:

```
initialServers       = 10
totalCycles          = 10000
initialQueue         = 1000
cooldownTime         = 100
newRequestProbability = 0.7
streamingProbability  = 0.3
minServiceTime        = 1
maxServiceTime        = 10
ipBlockThreshold      = 100
logFileName           = simulation.log
blockedRangeStart     = 192.168.1.0
blockedRangeEnd       = 192.168.1.255
```

## Building

```bash
make
```

## Running

```bash
./loadbalancer
```

You will be prompted to enter the number of servers and total clock cycles, or these can be set via the config file.

## Dynamic Scaling Logic

| Condition | Action |
|---|---|
| Queue size < `50 * servers` | Remove 1 server, wait cooldown cycles |
| Queue size > `80 * servers` | Add 1 server, wait cooldown cycles |

## Output

- Color-coded events printed to stdout (green = accepted, red = blocked, yellow = scaling)
- Full log written to the file specified in config (`simulation.log` by default)
- Summary printed at end of simulation including total requests, blocked IPs, and scale events

## Author

TAMU CSCE 412 — Individual Project
