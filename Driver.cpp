// Driver.cpp
#include "Driver.h"
#include <iostream>

Driver::Driver(int id, const std::string& name, const Location& location,
               const Vehicle& vehicle, double rating)
    : Person(id, name, location),
      vehicle(vehicle),
      rating(rating),
      tripsCompleted(0),
      status(DriverStatus::AVAILABLE) {}

Vehicle      Driver::getVehicle()        const { return vehicle; }
double       Driver::getRating()         const { return rating; }
int          Driver::getTripsCompleted() const { return tripsCompleted; }
DriverStatus Driver::getStatus()         const { return status; }

void Driver::setStatus(DriverStatus newStatus) {
    status = newStatus;
}

void Driver::completeTrip(double newRating) {
    // Running average: blend old rating with new one
    rating = (rating * tripsCompleted + newRating) / (tripsCompleted + 1);
    tripsCompleted++;
    status = DriverStatus::AVAILABLE;
}

bool Driver::isAvailable() const {
    return status == DriverStatus::AVAILABLE;
}

std::string Driver::getRole() const { return "Driver"; }

void Driver::display() const {
    Person::display();    // reuse base class output
    std::cout << "  Vehicle : " << vehicle.typeToString()
              << " [" << vehicle.getLicensePlate() << "]"
              << " | Speed: " << vehicle.getSpeed() << "\n"
              << "  Rating  : " << rating
              << " | Trips: " << tripsCompleted
              << " | Status: "
              << (status == DriverStatus::AVAILABLE ? "Available" :
                  status == DriverStatus::BUSY      ? "Busy" : "Offline")
              << "\n";
}