// StandardRide.h
#pragma once
#include "RideRequest.h"

class StandardRide : public RideRequest {
private:
    int    passengerId;
    double ratePerUnit;   // fare per distance unit

public:
    StandardRide(int id, const Location& pickup, const Location& drop,
                 int passengerId, double ratePerUnit = 2.0);

    double      calculateFare()  const override;
    RequestType getType()        const override;
    std::string getTypeString()  const override;
    void        display()        const override;

    int getPassengerId() const;
};