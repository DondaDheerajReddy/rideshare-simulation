// AnalyticsEngine.h
#pragma once
#include <vector>
#include <string>
#include "TripLog.h"
#include "Fleet.h"
#include "DriverReport.h"

class AnalyticsEngine {
private:
    const TripLog& tripLog;
    const Fleet&   fleet;

    // Internal helpers
    std::vector<DriverReport> buildDriverReports() const;

public:
    AnalyticsEngine(const TripLog& tripLog, const Fleet& fleet);

    // ── Fare metrics ───────────────────────────────────
    double averageFare()    const;
    double totalRevenue()   const;
    double highestFare()    const;
    double lowestFare()     const;

    // ── Trip metrics ───────────────────────────────────
    int totalTrips()        const;
    int tripsByType(const std::string& type) const;

    // ── Driver metrics ─────────────────────────────────
    DriverReport busiestDriver()    const;   // most trips
    DriverReport topEarnerDriver()  const;   // most earnings
    DriverReport highestRatedDriver() const; // best avg rating

    // ── Reports ────────────────────────────────────────
    void printFareSummary()     const;
    void printTripBreakdown()   const;
    void printDriverLeaderboard() const;
    void printFullReport()      const;

    // Save report to file
    bool saveReportToFile(const std::string& filepath) const;
};