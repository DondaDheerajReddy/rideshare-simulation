// DispatchEngine.cpp
#include "DispatchEngine.h"
#include <iostream>
#include "RideshareExceptions.h"

DispatchEngine::DispatchEngine(Fleet& fleet, RequestQueue& queue, TripLog& tripLog)
    : fleet(fleet), queue(queue), tripLog(tripLog), currentTick(0) {}

// ── Private Helpers ────────────────────────────────────────────

std::shared_ptr<Driver> DispatchEngine::findBestDriver(const RideRequest& request) const {
    // Strategy: nearest available driver to pickup point
    return fleet.findNearestAvailable(request.getPickupLocation());
}

bool DispatchEngine::validateRequest(const RideRequest& request) const {
    // Reject if pickup and drop are the same location
    if (request.getDistance() == 0.0) {
        std::cout << "  [INVALID] Request #" << request.getRequestId()
                  << " has zero distance. Skipping.\n";
        return false;
    }
    // Reject if fare would be zero or negative
    if (request.calculateFare() <= 0.0) {
        std::cout << "  [INVALID] Request #" << request.getRequestId()
                  << " has invalid fare. Skipping.\n";
        return false;
    }
    return true;
}

// ── Public Methods ─────────────────────────────────────────────

bool DispatchEngine::dispatchNext() {
    if (queue.isEmpty()) {
        std::cout << "  [DISPATCH] Queue is empty.\n";
        return false;
    }

    auto request = queue.dequeue();

    std::cout << "\n  [DISPATCH] Processing "
              << request->getTypeString()
              << " Request #" << request->getRequestId() << "\n";

    try {
        // Validate fare
        if (request->calculateFare() <= 0.0)
            throw InvalidFareException(request->getRequestId(),
                                       request->calculateFare());

        // Find driver
        auto driver = findBestDriver(*request);
        if (!driver)
            throw NoDriverAvailableException(request->getRequestId());

        // State transitions
        request->setStatus(RequestStatus::ACCEPTED);
        std::cout << "  [ACCEPTED]  Driver " << driver->getName()
                  << " assigned to Request #" << request->getRequestId() << "\n";

        driver->setStatus(DriverStatus::BUSY);

        double dist = driver->getLocation()
                             .distanceTo(request->getPickupLocation());
        std::cout << "  [EN_ROUTE]  Driver travelling "
                  << dist << " units to pickup\n";

        double fare = request->calculateFare();
        request->setStatus(RequestStatus::COMPLETED);
        driver->setLocation(request->getDropLocation());

        tripLog.addTrip(driver, request, fare, currentTick);
        std::cout << "  [COMPLETED] Fare charged: $" << fare << "\n";
        return true;

    } catch (const InvalidFareException& e) {
        std::cerr << "  [ERROR] " << e.what() << "\n";
        request->setStatus(RequestStatus::CANCELLED);
        return false;

    } catch (const NoDriverAvailableException& e) {
        std::cerr << "  [WARN]  " << e.what() << " Re-queuing.\n";
        request->setStatus(RequestStatus::PENDING);
        queue.enqueue(request);
        return false;
    }
}

void DispatchEngine::dispatchAll() {
    std::cout << "\n===== Dispatch Engine Running =====\n";
    int dispatched = 0;
    int maxAttempts = queue.size() * 2;  // prevent infinite loop if no drivers
    int attempts    = 0;

    while (!queue.isEmpty() && attempts < maxAttempts) {
        bool success = dispatchNext();
        if (success) dispatched++;
        attempts++;
        currentTick++;
    }

    std::cout << "\n===== Dispatch Complete =====\n";
    std::cout << "Dispatched : " << dispatched   << " trips\n";
    std::cout << "Remaining  : " << queue.size() << " in queue\n";
}

void DispatchEngine::cancelRequest(int requestId) {
    std::cout << "  [CANCEL] Request #" << requestId
              << " cancellation noted (will be skipped when dequeued).\n";
}

void DispatchEngine::setTick(int tick)      { currentTick = tick; }
int  DispatchEngine::getCurrentTick() const { return currentTick; }

void DispatchEngine::displayStatus() const {
    std::cout << "\n=== Dispatch Engine Status ===\n"
              << "  Current tick    : " << currentTick          << "\n"
              << "  Queue size      : " << queue.size()         << "\n"
              << "  Total drivers   : " << fleet.getTotalDrivers()   << "\n"
              << "  Available drivers: " << fleet.getAvailableCount() << "\n";
}