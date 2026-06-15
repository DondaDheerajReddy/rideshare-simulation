// SharedRide.cpp
#include "SharedRide.h"
#include <iostream>

SharedRide::SharedRide(int id, const Location& pickup, const Location& drop,
                       int maxPassengers, double discountRate)
    : RideRequest(id, pickup, drop, 5.0),
      maxPassengers(maxPassengers),
      discountRate(discountRate) {}

void SharedRide::addPassenger(int passengerId) {
    if ((int)passengerIds.size() < maxPassengers)
        passengerIds.push_back(passengerId);
    else
        std::cout << "Shared ride is full. Cannot add passenger " << passengerId << "\n";
}

double SharedRide::calculateFare() const {
    int count = passengerIds.size();
    if (count == 0) return 0.0;

    double fullFare    = baseFare + (getDistance() * 2.0);
    double discount    = 1.0 - (discountRate * (count - 1));
    double perPerson   = (fullFare * discount) / count;
    return perPerson;   // fare per passenger
}

RequestType SharedRide::getType()        const { return RequestType::SHARED; }
std::string SharedRide::getTypeString()  const { return "Shared"; }
int         SharedRide::getPassengerCount() const { return passengerIds.size(); }

void SharedRide::display() const {
    RideRequest::display();
    std::cout << "  Passengers   : " << passengerIds.size()
              << "/" << maxPassengers << "\n"
              << "  Discount rate: " << (discountRate * 100) << "%\n"
              << "  Fare shown is per passenger\n";
}