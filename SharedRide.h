// SharedRide.h
#pragma once
#include "RideRequest.h"
#include <vector>

class SharedRide : public RideRequest {
private:
    std::vector<int> passengerIds;
    int              maxPassengers;
    double           discountRate;

public:
    SharedRide(int id, const Location& pickup, const Location& drop,
               int maxPassengers = 3, double discountRate = 0.2);

    void addPassenger(int passengerId);

    double      calculateFare()  const override;
    RequestType getType()        const override;
    std::string getTypeString()  const override;
    void        display()        const override;

    int getPassengerCount() const;
};