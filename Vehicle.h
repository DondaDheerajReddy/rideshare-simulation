// Vehicle.h
#pragma once
#include <string>

enum class VehicleType {
    CAR,
    BIKE,
    TRUCK
};

class Vehicle {
private:
    std::string licensePlate;
    VehicleType type;
    int capacity;      // max passengers or cargo units
    double speed;      // units per tick

public:
    Vehicle(const std::string& plate, VehicleType type, int capacity, double speed);

    // Getters
    std::string getLicensePlate() const;
    VehicleType getType()         const;
    int         getCapacity()     const;
    double      getSpeed()        const;

    // Copy constructor (you'll write this manually for practice)
    Vehicle(const Vehicle& other);
    Vehicle& operator=(const Vehicle& other);

    std::string typeToString() const;
};