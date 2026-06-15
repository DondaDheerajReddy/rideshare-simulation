// TripLog.h
#pragma once
#include <deque>
#include <memory>
#include <ostream>
#include "Trip.h"

class TripLog {
private:
    std::deque<Trip> log;
    int              nextTripId;

public:
    TripLog();

    void addTrip(std::shared_ptr<Driver>      driver,
                 std::shared_ptr<RideRequest> request,
                 double fare, int tick);

    const Trip& getLatest()       const;
    const Trip& getOldest()       const;
    int         getTotalTrips()   const;
    double      getTotalRevenue() const;

    void displayAll()        const;
    void displayLast(int n)  const;

    const std::deque<Trip>& getLog() const;
};