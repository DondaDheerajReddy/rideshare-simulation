// StandardRide.cpp
#include "StandardRide.h"
#include <iostream>

StandardRide::StandardRide(int id, const Location& pickup, const Location& drop,
                           int passengerId, double ratePerUnit)
    : RideRequest(id, pickup, drop, 5.0),
      passengerId(passengerId),
      ratePerUnit(ratePerUnit) {}

double StandardRide::calculateFare() const {
    return baseFare + (getDistance() * ratePerUnit);
}

RequestType StandardRide::getType()       const { return RequestType::STANDARD; }
std::string StandardRide::getTypeString() const { return "Standard"; }
int         StandardRide::getPassengerId() const { return passengerId; }

void StandardRide::display() const {
    RideRequest::display();
    std::cout << "  Passenger ID : " << passengerId << "\n"
              << "  Rate/unit    : $" << ratePerUnit << "\n";
}