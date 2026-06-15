// PremiumRide.h
#pragma once
#include "RideRequest.h"

class PremiumRide : public RideRequest {
private:
    int    passengerId;
    double surgeMultiplier;   // e.g. 1.5 = 50% surge
    bool   luxuryVehicleRequired;

public:
    PremiumRide(int id, const Location& pickup, const Location& drop,
                int passengerId, double surgeMultiplier = 1.5);

    double      calculateFare()  const override;
    RequestType getType()        const override;
    std::string getTypeString()  const override;
    void        display()        const override;

    double getSurgeMultiplier()     const;
    bool   isLuxuryRequired()       const;
};