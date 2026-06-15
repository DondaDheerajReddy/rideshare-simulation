// Simulation.cpp
#include "Simulation.h"
#include <iostream>
#include <cstdlib>   // rand()
#include <ctime>     // time()

Simulation::Simulation(int maxTicks, int mapSize, int requestsPerTick)
    : clock(maxTicks),
      fleet(),
      queue(),
      tripLog(),
      engine(fleet, queue, tripLog),
      analytics(tripLog, fleet), 
      nextRequestId(1),
      mapSize(mapSize),
      requestsPerTick(requestsPerTick),
      baseFareRate(2.0)
{
    std::srand(std::time(nullptr));   // seed random number generator once
}

// ── Setup ──────────────────────────────────────────────────────

void Simulation::addDriver(const std::string& name, const Location& loc,
                           const Vehicle& vehicle, double rating) {
    fleet.addDriver(name, loc, vehicle, rating);
}

// ── Random Helpers ─────────────────────────────────────────────

Location Simulation::randomLocation() const {
    double x = std::rand() % (mapSize + 1);
    double y = std::rand() % (mapSize + 1);
    return Location(x, y);
}

std::string Simulation::randomName() const {
    static const std::vector<std::string> names = {
        "Aarav", "Priya", "Rohan", "Sneha",
        "Karan", "Meera", "Arjun", "Nisha",
        "Vikram", "Pooja"
    };
    return names[std::rand() % names.size()];
}

// ── Request Spawner ────────────────────────────────────────────

void Simulation::spawnRequests() {
    for (int i = 0; i < requestsPerTick; i++) {
        Location pickup = randomLocation();
        Location drop   = randomLocation();

        // Make sure pickup and drop are not identical
        while (pickup.distanceTo(drop) == 0.0)
            drop = randomLocation();

        int type = std::rand() % 4;   // 0-3 maps to 4 request types

        std::shared_ptr<RideRequest> request;

        switch (type) {
            case 0:
                request = std::make_shared<StandardRide>(
                    nextRequestId, pickup, drop, std::rand() % 200 + 100);
                break;
            case 1: {
                auto shared = std::make_shared<SharedRide>(
                    nextRequestId, pickup, drop, 3);
                int passengerCount = std::rand() % 3 + 1;
                for (int p = 0; p < passengerCount; p++)
                    shared->addPassenger(std::rand() % 100 + 100);
                request = shared;
                break;
            }
            case 2: {
                double weight = (std::rand() % 20) + 1;
                DeliveryPriority priority = static_cast<DeliveryPriority>(
                    std::rand() % 3);
                request = std::make_shared<DeliveryRequest>(
                    nextRequestId, pickup, drop,
                    weight, priority, randomName());
                break;
            }
            case 3:
                request = std::make_shared<PremiumRide>(
                    nextRequestId, pickup, drop,
                    std::rand() % 200 + 100,
                    1.0 + (std::rand() % 10) / 10.0);
                break;
        }

        queue.enqueue(request);
        nextRequestId++;
    }
}

// ── Core Loop ──────────────────────────────────────────────────

void Simulation::stepOnce() {
    std::cout << "\n────────────────────────────────\n";
    std::cout << "  " << clock.toString() << "\n";
    std::cout << "────────────────────────────────\n";

    // 1. Spawn new requests this tick
    spawnRequests();

    // 2. Sync engine tick
    engine.setTick(clock.getTick());

    // 3. Dispatch one request per tick
    engine.dispatchNext();

    // 4. Advance clock
    clock.advance();
}

void Simulation::run() {
    std::cout << "\n========================================\n";
    std::cout << "   Simulation Started\n";
    std::cout << "   Max ticks      : " << clock.getMaxTicks()  << "\n";
    std::cout << "   Map size       : " << mapSize              << "x" << mapSize << "\n";
    std::cout << "   Requests/tick  : " << requestsPerTick      << "\n";
    std::cout << "   Drivers        : " << fleet.getTotalDrivers() << "\n";
    std::cout << "========================================\n";

    while (clock.isRunning() && !clock.hasExpired()) {
        stepOnce();

        // Stop early if queue is empty and all trips done
        if (queue.isEmpty() && fleet.getAvailableCount() == fleet.getTotalDrivers()) {
            std::cout << "\n  [SIM] All requests handled. Stopping early at tick "
                      << clock.getTick() << ".\n";
            clock.stop();
        }
    }

    printSummary();
}

// ── Summary ────────────────────────────────────────────────────

void Simulation::printSummary() const {
    std::cout << "\n========================================\n";
    std::cout << "   Simulation Complete\n";
    std::cout << "========================================\n";
    std::cout << "  Ticks run       : " << clock.getTick()          << "\n";
    std::cout << "  Total trips     : " << tripLog.getTotalTrips()   << "\n";
    std::cout << "  Total revenue   : $" << tripLog.getTotalRevenue() << "\n";
    std::cout << "  Remaining queue : " << queue.size()              << "\n";
    std::cout << "\n";
    tripLog.displayAll();
    std::cout << "\n";
    analytics.printFullReport();
    fleet.displayAll();
}

int Simulation::getTick()       const { return clock.getTick(); }
int Simulation::getTotalTrips() const { return tripLog.getTotalTrips(); }

const AnalyticsEngine& Simulation::getAnalytics() const {
    return analytics;
}