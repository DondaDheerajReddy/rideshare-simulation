// AnalyticsEngine.cpp
#include "AnalyticsEngine.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iomanip>   // std::setw, std::fixed, std::setprecision
#include <map>

AnalyticsEngine::AnalyticsEngine(const TripLog& tripLog, const Fleet& fleet)
    : tripLog(tripLog), fleet(fleet) {}

// ── Internal Helper ────────────────────────────────────────────

std::vector<DriverReport> AnalyticsEngine::buildDriverReports() const {
    // Map from driverId to report
    std::map<int, DriverReport> reportMap;

    // Initialise a report for every driver in the fleet
    for (const auto& d : fleet.getDrivers()) {
        reportMap.emplace(d->getId(),
                          DriverReport(d->getId(), d->getName()));
        reportMap.at(d->getId()).averageRating = d->getRating();
    }

    // Walk the trip log and accumulate stats
    for (const auto& t : tripLog.getLog()) {
        int id = t.driver->getId();
        if (reportMap.find(id) == reportMap.end())
            reportMap.emplace(id, DriverReport(id, t.driver->getName()));

        DriverReport& r = reportMap.at(id);
        r.tripsCompleted++;
        r.totalEarnings += t.fareCharged;
    }

    // Calculate average fare per driver
    for (auto& [id, r] : reportMap) {
        if (r.tripsCompleted > 0)
            r.averageFare = r.totalEarnings / r.tripsCompleted;
    }

    // Convert map to vector for sorting
    std::vector<DriverReport> reports;
    for (const auto& [id, r] : reportMap)
        reports.push_back(r);

    return reports;
}

// ── Fare Metrics ───────────────────────────────────────────────

double AnalyticsEngine::averageFare() const {
    const auto& log = tripLog.getLog();
    if (log.empty()) return 0.0;

    double total = 0.0;
    for (const auto& t : log)
        total += t.fareCharged;
    return total / log.size();
}

double AnalyticsEngine::totalRevenue() const {
    return tripLog.getTotalRevenue();
}

double AnalyticsEngine::highestFare() const {
    const auto& log = tripLog.getLog();
    if (log.empty()) return 0.0;

    double highest = std::numeric_limits<double>::lowest();
    for (const auto& t : log)
        if (t.fareCharged > highest)
            highest = t.fareCharged;
    return highest;
}

double AnalyticsEngine::lowestFare() const {
    const auto& log = tripLog.getLog();
    if (log.empty()) return 0.0;

    double lowest = std::numeric_limits<double>::max();
    for (const auto& t : log)
        if (t.fareCharged < lowest)
            lowest = t.fareCharged;
    return lowest;
}

// ── Trip Metrics ───────────────────────────────────────────────

int AnalyticsEngine::totalTrips() const {
    return tripLog.getTotalTrips();
}

int AnalyticsEngine::tripsByType(const std::string& type) const {
    int count = 0;
    for (const auto& t : tripLog.getLog())
        if (t.request->getTypeString() == type)
            count++;
    return count;
}

// ── Driver Metrics ─────────────────────────────────────────────

DriverReport AnalyticsEngine::busiestDriver() const {
    auto reports = buildDriverReports();
    if (reports.empty())
        return DriverReport(-1, "None");

    return *std::max_element(reports.begin(), reports.end(),
        [](const DriverReport& a, const DriverReport& b) {
            return a.tripsCompleted < b.tripsCompleted;
        });
}

DriverReport AnalyticsEngine::topEarnerDriver() const {
    auto reports = buildDriverReports();
    if (reports.empty())
        return DriverReport(-1, "None");

    // operator> defined on DriverReport — sort descending by earnings
    std::sort(reports.begin(), reports.end(),
        [](const DriverReport& a, const DriverReport& b) {
            return a > b;
        });
    return reports.front();
}

DriverReport AnalyticsEngine::highestRatedDriver() const {
    auto reports = buildDriverReports();
    if (reports.empty())
        return DriverReport(-1, "None");

    return *std::max_element(reports.begin(), reports.end(),
        [](const DriverReport& a, const DriverReport& b) {
            return a.averageRating < b.averageRating;
        });
}

// ── Reports ────────────────────────────────────────────────────

void AnalyticsEngine::printFareSummary() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n=== Fare Summary ===\n"
              << "  Total revenue  : $" << totalRevenue() << "\n"
              << "  Average fare   : $" << averageFare()  << "\n"
              << "  Highest fare   : $" << highestFare()  << "\n"
              << "  Lowest fare    : $" << lowestFare()   << "\n";
}

void AnalyticsEngine::printTripBreakdown() const {
    std::cout << "\n=== Trip Breakdown ===\n"
              << "  Total trips    : " << totalTrips()                  << "\n"
              << "  Standard rides : " << tripsByType("Standard")       << "\n"
              << "  Shared rides   : " << tripsByType("Shared")         << "\n"
              << "  Deliveries     : " << tripsByType("Delivery")       << "\n"
              << "  Premium rides  : " << tripsByType("Premium")        << "\n";
}

void AnalyticsEngine::printDriverLeaderboard() const {
    auto reports = buildDriverReports();

    // Sort descending by earnings using operator>
    std::sort(reports.begin(), reports.end(),
        [](const DriverReport& a, const DriverReport& b) {
            return a > b;
        });

    std::cout << "\n=== Driver Leaderboard ===\n";
    std::cout << std::fixed << std::setprecision(2);

    int rank = 1;
    for (const auto& r : reports) {
        std::cout << "  #" << rank++ << " " << r << "\n";
    }

    std::cout << "\n  Busiest driver      : "
              << busiestDriver().driverName    << "\n"
              << "  Top earner          : "
              << topEarnerDriver().driverName  << "\n"
              << "  Highest rated       : "
              << highestRatedDriver().driverName << "\n";
}

void AnalyticsEngine::printFullReport() const {
    std::cout << "\n"
              << "========================================\n"
              << "         SIMULATION ANALYTICS REPORT    \n"
              << "========================================\n";
    printFareSummary();
    printTripBreakdown();
    printDriverLeaderboard();
    std::cout << "========================================\n";
}

bool AnalyticsEngine::saveReportToFile(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cout << "[ANALYTICS] Could not write report to " << filepath << "\n";
        return false;
    }

    file << std::fixed << std::setprecision(2);
    file << "========================================\n"
         << "       SIMULATION ANALYTICS REPORT      \n"
         << "========================================\n"
         << "Total Revenue  : $" << totalRevenue() << "\n"
         << "Average Fare   : $" << averageFare()  << "\n"
         << "Highest Fare   : $" << highestFare()  << "\n"
         << "Lowest Fare    : $" << lowestFare()   << "\n"
         << "Total Trips    : "  << totalTrips()   << "\n"
         << "Standard rides : "  << tripsByType("Standard") << "\n"
         << "Shared rides   : "  << tripsByType("Shared")   << "\n"
         << "Deliveries     : "  << tripsByType("Delivery") << "\n"
         << "Premium rides  : "  << tripsByType("Premium")  << "\n"
         << "\n--- Driver Leaderboard ---\n";

    auto reports = buildDriverReports();
    std::sort(reports.begin(), reports.end(),
        [](const DriverReport& a, const DriverReport& b) {
            return a > b;
        });

    int rank = 1;
    for (const auto& r : reports)
        file << "#" << rank++ << " " << r << "\n";

    file << "========================================\n";
    std::cout << "[ANALYTICS] Report saved to " << filepath << "\n";
    return true;
}