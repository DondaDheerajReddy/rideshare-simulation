// RideRequest.h
#pragma once
#include <string>
#include "Location.h"

enum class RequestStatus {
    PENDING,
    ACCEPTED,
    COMPLETED,
    CANCELLED
};

enum class RequestType {
    STANDARD,
    SHARED,
    DELIVERY,
    PREMIUM
};

class RideRequest {
protected:
    int           requestId;
    Location      pickupLocation;
    Location      dropLocation;
    RequestStatus status;
    double        baseFare;

public:
    RideRequest(int id, const Location& pickup,
                const Location& drop, double baseFare);

    virtual ~RideRequest() = default;

    // Pure virtual — every subclass MUST implement these
    virtual double      calculateFare()  const = 0;
    virtual RequestType getType()        const = 0;
    virtual std::string getTypeString()  const = 0;
    virtual void        display()        const;

    // Common getters
    int           getRequestId()      const;
    Location      getPickupLocation() const;
    Location      getDropLocation()   const;
    RequestStatus getStatus()         const;
    double        getBaseFare()       const;
    double        getDistance()       const;  // auto-calculated from locations

    void setStatus(RequestStatus newStatus);
};