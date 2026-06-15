// Driver.h
#pragma once
#include "Person.h"
#include "Vehicle.h"

enum class DriverStatus {
    AVAILABLE,
    BUSY,
    OFFLINE
};

class Driver : public Person {
private:
    Vehicle      vehicle;
    double       rating;       // 1.0 to 5.0
    int          tripsCompleted;
    DriverStatus status;

public:
    Driver(int id, const std::string& name, const Location& location,
           const Vehicle& vehicle, double rating = 5.0);

    // Getters
    Vehicle      getVehicle()        const;
    double       getRating()         const;
    int          getTripsCompleted() const;
    DriverStatus getStatus()         const;

    // Setters
    void setStatus(DriverStatus newStatus);
    void completeTrip(double newRating);    // increments trips, updates rating

    // Overrides
    std::string getRole()    const override;
    void        display()    const override;

    bool isAvailable() const;
};