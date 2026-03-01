# Makefile for Load Balancer Simulation
# Usage: make        (builds the project)
#        make clean  (removes compiled files)

CXX = g++
CXXFLAGS = -Wall -std=c++11

# All object files needed
OBJS = main.o Config.o Logger.o Stats.o IPBlocker.o WebServer.o LoadBalancer.o

# Final executable name
TARGET = loadbalancer

# Default target: build everything
all: $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each .cpp into a .o
main.o: main.cpp LoadBalancer.h Config.h Logger.h Stats.h IPBlocker.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Config.o: config.cpp config.h
	$(CXX) $(CXXFLAGS) -c Config.cpp

Logger.o: Logger.cpp Logger.h
	$(CXX) $(CXXFLAGS) -c Logger.cpp

Stats.o: Stats.cpp Stats.h
	$(CXX) $(CXXFLAGS) -c Stats.cpp

IPBlocker.o: IPBlocker.cpp IPBlocker.h
	$(CXX) $(CXXFLAGS) -c IPBlocker.cpp

WebServer.o: WebServer.cpp WebServer.h Request.h
	$(CXX) $(CXXFLAGS) -c WebServer.cpp

LoadBalancer.o: LoadBalancer.cpp LoadBalancer.h WebServer.h Request.h IPBlocker.h Logger.h Stats.h Config.h
	$(CXX) $(CXXFLAGS) -c LoadBalancer.cpp

# Remove all compiled files
clean:
	rm -f $(OBJS) $(TARGET)