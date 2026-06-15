// DispatchEngine.h
#pragma once
#include <memory>
#include <vector>
#include "Fleet.h"
#include "RequestQueue.h"
#include "TripLog.h"
#include "Trip.h"

class DispatchEngine {
private:
    Fleet&        fleet;
    RequestQueue& queue;
    TripLog&      tripLog;
    int           currentTick;

    // Internal helpers
    std::shared_ptr<Driver> findBestDriver(const RideRequest& request) const;
    bool validateRequest(const RideRequest& request)                   const;

public:
    DispatchEngine(Fleet& fleet, RequestQueue& queue, TripLog& tripLog);

    // Try to match one request from the queue to a driver
    bool dispatchNext();

    // Dispatch all pending requests in the queue
    void dispatchAll();

    // Manually cancel a pending request
    void cancelRequest(int requestId);

    void setTick(int tick);
    int  getCurrentTick() const;

    void displayStatus() const;
};