// DeliveryRequest.cpp
#include "DeliveryRequest.h"
#include <iostream>

DeliveryRequest::DeliveryRequest(int id, const Location& pickup, const Location& drop,
                                 double weight, DeliveryPriority priority,
                                 const std::string& senderName)
    : RideRequest(id, pickup, drop, 8.0),
      packageWeight(weight),
      priority(priority),
      senderName(senderName) {}

double DeliveryRequest::calculateFare() const {
    double weightCharge    = packageWeight * 1.5;
    double distanceCharge  = getDistance() * 1.8;

    double priorityMultiplier = 1.0;
    if (priority == DeliveryPriority::EXPRESS) priorityMultiplier = 1.5;
    if (priority == DeliveryPriority::FRAGILE) priorityMultiplier = 1.8;

    return (baseFare + weightCharge + distanceCharge) * priorityMultiplier;
}

RequestType DeliveryRequest::getType()        const { return RequestType::DELIVERY; }
std::string DeliveryRequest::getTypeString()  const { return "Delivery"; }
double      DeliveryRequest::getWeight()      const { return packageWeight; }
DeliveryPriority DeliveryRequest::getPriority() const { return priority; }

std::string DeliveryRequest::priorityToString() const {
    switch (priority) {
        case DeliveryPriority::STANDARD: return "Standard";
        case DeliveryPriority::EXPRESS:  return "Express";
        case DeliveryPriority::FRAGILE:  return "Fragile";
        default:                         return "Unknown";
    }
}

void DeliveryRequest::display() const {
    RideRequest::display();
    std::cout << "  Sender   : " << senderName        << "\n"
              << "  Weight   : " << packageWeight      << " kg\n"
              << "  Priority : " << priorityToString() << "\n";
}