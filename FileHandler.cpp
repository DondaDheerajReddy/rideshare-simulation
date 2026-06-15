// FileHandler.cpp
#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <sys/stat.h>   // mkdir

// ── Fleet ──────────────────────────────────────────────────────

bool FileHandler::saveFleet(const Fleet& fleet, const std::string& filepath) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cout << "[FILE] Cannot open " << filepath << " for writing.\n";
        return false;
    }

    file << "# id,name,x,y,plate,vehicle_type,capacity,speed,rating,trips,status\n";

    for (const auto& d : fleet.getDrivers()) {
        std::string statusStr;
        switch (d->getStatus()) {
            case DriverStatus::AVAILABLE: statusStr = "AVAILABLE"; break;
            case DriverStatus::BUSY:      statusStr = "BUSY";      break;
            case DriverStatus::OFFLINE:   statusStr = "OFFLINE";   break;
        }

        std::string typeStr;
        switch (d->getVehicle().getType()) {
            case VehicleType::CAR:   typeStr = "CAR";   break;
            case VehicleType::BIKE:  typeStr = "BIKE";  break;
            case VehicleType::TRUCK: typeStr = "TRUCK"; break;
        }

        file << d->getId()                      << ","
             << d->getName()                    << ","
             << d->getLocation().x              << ","
             << d->getLocation().y              << ","
             << d->getVehicle().getLicensePlate() << ","
             << typeStr                         << ","
             << d->getVehicle().getCapacity()   << ","
             << d->getVehicle().getSpeed()      << ","
             << d->getRating()                  << ","
             << d->getTripsCompleted()          << ","
             << statusStr                       << "\n";
    }

    std::cout << "[FILE] Fleet saved to " << filepath << "\n";
    return true;
}

bool FileHandler::loadFleet(Fleet& fleet, const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "[FILE] Cannot open " << filepath << " for reading.\n";
        return false;
    }

    std::string line;
    int loaded = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream ss(line);
        std::string id, name, x, y, plate, typeStr,
                    capacity, speed, rating, trips, statusStr;

        // Parse CSV columns
        std::getline(ss, id,       ',');
        std::getline(ss, name,     ',');
        std::getline(ss, x,        ',');
        std::getline(ss, y,        ',');
        std::getline(ss, plate,    ',');
        std::getline(ss, typeStr,  ',');
        std::getline(ss, capacity, ',');
        std::getline(ss, speed,    ',');
        std::getline(ss, rating,   ',');
        std::getline(ss, trips,    ',');
        std::getline(ss, statusStr,',');

        VehicleType vtype = VehicleType::CAR;
        if (typeStr == "BIKE")  vtype = VehicleType::BIKE;
        if (typeStr == "TRUCK") vtype = VehicleType::TRUCK;

        Vehicle v(plate, vtype, std::stoi(capacity), std::stod(speed));
        fleet.addDriver(name,
                        Location(std::stod(x), std::stod(y)),
                        v,
                        std::stod(rating));
        loaded++;
    }

    std::cout << "[FILE] Loaded " << loaded << " drivers from " << filepath << "\n";
    return true;
}

// ── Trip Log ───────────────────────────────────────────────────

bool FileHandler::saveTripLog(const TripLog& tripLog, const std::string& filepath) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cout << "[FILE] Cannot open " << filepath << " for writing.\n";
        return false;
    }

    file << "# trip_id,driver_id,driver_name,request_id,type,fare,tick\n";

    for (const auto& t : tripLog.getLog()) {
        file << t.tripId                           << ","
             << t.driver->getId()                  << ","
             << t.driver->getName()                << ","
             << t.request->getRequestId()          << ","
             << t.request->getTypeString()         << ","
             << t.fareCharged                      << ","
             << t.startTick                        << "\n";
    }

    std::cout << "[FILE] Trip log saved to " << filepath << "\n";
    return true;
}

// ── Logger ─────────────────────────────────────────────────────

bool FileHandler::log(const std::string& message,
                      const std::string& filepath,
                      const std::string& level) {
    std::ofstream file(filepath, std::ios::app);   // append mode
    if (!file.is_open()) return false;

    file << "[" << timestamp() << "] "
         << "[" << level       << "] "
         << message            << "\n";
    return true;
}

// ── Utility ────────────────────────────────────────────────────

bool FileHandler::fileExists(const std::string& filepath) {
    std::ifstream f(filepath);
    return f.good();
}

bool FileHandler::createFolder(const std::string& path) {
    #ifdef _WIN32
        return _mkdir(path.c_str()) == 0;
    #else
        return mkdir(path.c_str(), 0755) == 0;
    #endif
}

std::string FileHandler::timestamp() {
    auto now     = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::string ts = std::ctime(&t);
    ts.erase(ts.find('\n'));   // remove trailing newline from ctime
    return ts;
}