// PremiumRide.cpp
#include "PremiumRide.h"
#include <iostream>

PremiumRide::PremiumRide(int id, const Location& pickup, const Location& drop,
                         int passengerId, double surgeMultiplier)
    : RideRequest(id, pickup, drop, 15.0),
      passengerId(passengerId),
      surgeMultiplier(surgeMultiplier),
      luxuryVehicleRequired(true) {}

double PremiumRide::calculateFare() const {
    double distanceCharge = getDistance() * 3.5;
    return (baseFare + distanceCharge) * surgeMultiplier;
}

RequestType PremiumRide::getType()        const { return RequestType::PREMIUM; }
std::string PremiumRide::getTypeString()  const { return "Premium"; }
double      PremiumRide::getSurgeMultiplier() const { return surgeMultiplier; }
bool        PremiumRide::isLuxuryRequired()   const { return luxuryVehicleRequired; }

void PremiumRide::display() const {
    RideRequest::display();
    std::cout << "  Passenger ID    : " << passengerId                        << "\n"
              << "  Surge multiplier: x" << surgeMultiplier                   << "\n"
              << "  Luxury required : " << (luxuryVehicleRequired ? "Yes" : "No") << "\n";
}