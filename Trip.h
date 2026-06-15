// Trip.h
#pragma once
#include <memory>
#include <ostream>
#include "RideRequest.h"
#include "Driver.h"

enum class TripStatus {
    REQUESTED,
    ACCEPTED,
    EN_ROUTE,
    COMPLETED,
    CANCELLED
};

struct Trip {
    int                          tripId;
    std::shared_ptr<Driver>      driver;
    std::shared_ptr<RideRequest> request;
    double                       fareCharged;
    int                          startTick;
    TripStatus                   status;

    Trip(int tripId,
         std::shared_ptr<Driver>      driver,
         std::shared_ptr<RideRequest> request,
         double fare,
         int    tick)
        : tripId(tripId),
          driver(driver),
          request(request),
          fareCharged(fare),
          startTick(tick),
          status(TripStatus::REQUESTED) {}

    std::string statusToString() const {
        switch (status) {
            case TripStatus::REQUESTED:  return "Requested";
            case TripStatus::ACCEPTED:   return "Accepted";
            case TripStatus::EN_ROUTE:   return "En Route";
            case TripStatus::COMPLETED:  return "Completed";
            case TripStatus::CANCELLED:  return "Cancelled";
            default:                     return "Unknown";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Trip& t) {
        os << "Trip #"     << t.tripId
           << " | Driver: "  << t.driver->getName()
           << " | Type: "    << t.request->getTypeString()
           << " | Fare: $"   << t.fareCharged
           << " | Status: "  << t.statusToString()
           << " | Tick: "    << t.startTick;
        return os;
    }
};