// Simulation.h
#pragma once
#include <memory>
#include <vector>
#include "SimulationClock.h"
#include "Fleet.h"
#include "RequestQueue.h"
#include "TripLog.h"
#include "DispatchEngine.h"
#include "AnalyticsEngine.h"        // ← make sure this is here
#include "StandardRide.h"
#include "SharedRide.h"
#include "DeliveryRequest.h"
#include "PremiumRide.h"

class Simulation {
private:
    SimulationClock clock;
    Fleet           fleet;
    RequestQueue    queue;
    TripLog         tripLog;
    DispatchEngine  engine;
    AnalyticsEngine analytics;       // ← make sure this is here

    int nextRequestId;

    int    mapSize;
    int    requestsPerTick;
    double baseFareRate;

    void        spawnRequests();
    Location    randomLocation() const;
    std::string randomName()     const;

public:
    Simulation(int maxTicks        = 20,
               int mapSize         = 10,
               int requestsPerTick = 1);

    void addDriver(const std::string& name,
                   const Location&    loc,
                   const Vehicle&     vehicle,
                   double             rating = 5.0);

    void run();
    void stepOnce();
    void printSummary() const;

    int getTick()       const;
    int getTotalTrips() const;

    const AnalyticsEngine& getAnalytics() const;   // ← make sure this is here
};