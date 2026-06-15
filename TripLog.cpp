// TripLog.cpp
#include "TripLog.h"
#include <iostream>
#include <stdexcept>
#include "RideshareExceptions.h" 

TripLog::TripLog() : nextTripId(1) {}

void TripLog::addTrip(std::shared_ptr<Driver> driver,
                      std::shared_ptr<RideRequest> request,
                      double fare, int tick) {
    Trip t(nextTripId++, driver, request, fare, tick);
    log.push_back(t);
    request->setStatus(RequestStatus::COMPLETED);
    driver->completeTrip(4.5);   // placeholder rating for now
    std::cout << "Logged: " << t << "\n";
}

const Trip& TripLog::getLatest()  const {
    if (log.empty()) throw TripLogEmptyException();
    return log.back();
}

const Trip& TripLog::getOldest()  const {
    if (log.empty()) throw TripLogEmptyException();
    return log.front();
}

int TripLog::getTotalTrips() const { return log.size(); }

double TripLog::getTotalRevenue() const {
    double total = 0;
    for (const auto& t : log)
        total += t.fareCharged;
    return total;
}

void TripLog::displayAll() const {
    std::cout << "=== Trip Log (" << log.size() << " trips) ===\n";
    for (const auto& t : log)
        std::cout << t << "\n";
}

void TripLog::displayLast(int n) const {
    std::cout << "=== Last " << n << " Trips ===\n";
    int start = std::max(0, (int)log.size() - n);
    for (int i = start; i < (int)log.size(); i++)
        std::cout << log[i] << "\n";
}

const std::deque<Trip>& TripLog::getLog() const { return log; }