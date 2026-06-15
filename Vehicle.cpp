// Vehicle.cpp
#include "Vehicle.h"
#include "RideshareExceptions.h"

Vehicle::Vehicle(const std::string& plate, VehicleType type,
                 int capacity, double speed)
    : licensePlate(plate), type(type), capacity(capacity), speed(speed)
{
    if (plate.empty())
        throw InvalidArgumentException("Vehicle", "license plate cannot be empty");
    if (capacity <= 0)
        throw InvalidArgumentException("Vehicle", "capacity must be greater than 0");
    if (speed <= 0.0)
        throw InvalidArgumentException("Vehicle", "speed must be greater than 0");
}

// Manual copy constructor
Vehicle::Vehicle(const Vehicle& other)
    : licensePlate(other.licensePlate),
      type(other.type),
      capacity(other.capacity),
      speed(other.speed) {}

// Assignment operator
Vehicle& Vehicle::operator=(const Vehicle& other) {
    if (this != &other) {          // self-assignment guard
        licensePlate = other.licensePlate;
        type         = other.type;
        capacity     = other.capacity;
        speed        = other.speed;
    }
    return *this;
}

std::string Vehicle::getLicensePlate() const { return licensePlate; }
VehicleType Vehicle::getType()         const { return type; }
int         Vehicle::getCapacity()     const { return capacity; }
double      Vehicle::getSpeed()        const { return speed; }

std::string Vehicle::typeToString() const {
    switch (type) {
        case VehicleType::CAR:   return "Car";
        case VehicleType::BIKE:  return "Bike";
        case VehicleType::TRUCK: return "Truck";
        default:                 return "Unknown";
    }
}