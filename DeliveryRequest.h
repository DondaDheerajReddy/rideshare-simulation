// DeliveryRequest.h
#pragma once
#include "RideRequest.h"
#include <string>

enum class DeliveryPriority {
    STANDARD,
    EXPRESS,
    FRAGILE
};

class DeliveryRequest : public RideRequest {
private:
    double          packageWeight;   // in kg
    DeliveryPriority priority;
    std::string     senderName;

public:
    DeliveryRequest(int id, const Location& pickup, const Location& drop,
                    double weight, DeliveryPriority priority,
                    const std::string& senderName);

    double      calculateFare()  const override;
    RequestType getType()        const override;
    std::string getTypeString()  const override;
    void        display()        const override;

    double          getWeight()   const;
    DeliveryPriority getPriority() const;
    std::string     priorityToString() const;
};