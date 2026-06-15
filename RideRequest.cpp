// RideRequest.cpp
#include "RideRequest.h"
#include <iostream>

RideRequest::RideRequest(int id, const Location& pickup,
                         const Location& drop, double baseFare)
    : requestId(id), pickupLocation(pickup),
      dropLocation(drop), status(RequestStatus::PENDING),
      baseFare(baseFare) {}

int           RideRequest::getRequestId()      const { return requestId; }
Location      RideRequest::getPickupLocation() const { return pickupLocation; }
Location      RideRequest::getDropLocation()   const { return dropLocation; }
RequestStatus RideRequest::getStatus()         const { return status; }
double        RideRequest::getBaseFare()       const { return baseFare; }

double RideRequest::getDistance() const {
    return pickupLocation.distanceTo(dropLocation);
}

void RideRequest::setStatus(RequestStatus newStatus) {
    status = newStatus;
}

void RideRequest::display() const {
    std::cout << "[" << getTypeString() << " Request #" << requestId << "]\n"
              << "  Pickup  : " << pickupLocation.toString() << "\n"
              << "  Drop    : " << dropLocation.toString()   << "\n"
              << "  Distance: " << getDistance()             << " units\n"
              << "  Fare    : $" << calculateFare()          << "\n"
              << "  Status  : "
              << (status == RequestStatus::PENDING   ? "Pending"   :
                  status == RequestStatus::ACCEPTED  ? "Accepted"  :
                  status == RequestStatus::COMPLETED ? "Completed" : "Cancelled")
              << "\n";
}