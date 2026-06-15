// DriverReport.h
#pragma once
#include <string>
#include <ostream>

struct DriverReport {
    int         driverId;
    std::string driverName;
    int         tripsCompleted;
    double      totalEarnings;
    double      averageRating;
    double      averageFare;

    DriverReport(int id, const std::string& name)
        : driverId(id),
          driverName(name),
          tripsCompleted(0),
          totalEarnings(0.0),
          averageRating(0.0),
          averageFare(0.0) {}

    // Sort by earnings — used with std::sort
    bool operator>(const DriverReport& other) const {
        return totalEarnings > other.totalEarnings;
    }

    bool operator<(const DriverReport& other) const {
        return totalEarnings < other.totalEarnings;
    }

    friend std::ostream& operator<<(std::ostream& os, const DriverReport& r) {
        os << "Driver #" << r.driverId
           << " | "      << r.driverName
           << " | Trips: "    << r.tripsCompleted
           << " | Earnings: $" << r.totalEarnings
           << " | Avg Fare: $" << r.averageFare
           << " | Avg Rating: " << r.averageRating;
        return os;
    }
};