// ConfigManager.cpp
#include "ConfigManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Private constructor — sets all defaults
ConfigManager::ConfigManager()
    : maxTicks(20),
      mapSize(10),
      requestsPerTick(2),
      maxDrivers(10),
      baseFareRate(2.0),
      surgeMultiplier(1.5),
      deliveryWeightRate(1.5),
      fleetFile("data/fleet.csv"),
      tripLogFile("data/triplog.csv"),
      logFile("data/simulation.log") {}

// Static method returns the single instance
ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;   // created once, lives forever
    return instance;
}

bool ConfigManager::loadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "[CONFIG] File not found: " << filepath
                  << ". Using defaults.\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;

        std::istringstream ss(line);
        std::string key, value;

        if (std::getline(ss, key, '=') && std::getline(ss, value)) {
            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            if      (key == "max_ticks")           maxTicks           = std::stoi(value);
            else if (key == "map_size")            mapSize            = std::stoi(value);
            else if (key == "requests_per_tick")   requestsPerTick    = std::stoi(value);
            else if (key == "max_drivers")         maxDrivers         = std::stoi(value);
            else if (key == "base_fare_rate")      baseFareRate       = std::stod(value);
            else if (key == "surge_multiplier")    surgeMultiplier    = std::stod(value);
            else if (key == "delivery_weight_rate") deliveryWeightRate = std::stod(value);
            else if (key == "fleet_file")          fleetFile          = value;
            else if (key == "trip_log_file")       tripLogFile        = value;
            else if (key == "log_file")            logFile            = value;
        }
    }

    std::cout << "[CONFIG] Loaded from " << filepath << "\n";
    return true;
}

bool ConfigManager::saveToFile(const std::string& filepath) const {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cout << "[CONFIG] Could not write to " << filepath << "\n";
        return false;
    }

    file << "# Rideshare Simulation Config\n"
         << "max_ticks           = " << maxTicks           << "\n"
         << "map_size            = " << mapSize            << "\n"
         << "requests_per_tick   = " << requestsPerTick    << "\n"
         << "max_drivers         = " << maxDrivers         << "\n"
         << "base_fare_rate      = " << baseFareRate       << "\n"
         << "surge_multiplier    = " << surgeMultiplier    << "\n"
         << "delivery_weight_rate= " << deliveryWeightRate << "\n"
         << "fleet_file          = " << fleetFile          << "\n"
         << "trip_log_file       = " << tripLogFile        << "\n"
         << "log_file            = " << logFile            << "\n";

    std::cout << "[CONFIG] Saved to " << filepath << "\n";
    return true;
}

// Getters
int         ConfigManager::getMaxTicks()           const { return maxTicks; }
int         ConfigManager::getMapSize()            const { return mapSize; }
int         ConfigManager::getRequestsPerTick()    const { return requestsPerTick; }
int         ConfigManager::getMaxDrivers()         const { return maxDrivers; }
double      ConfigManager::getBaseFareRate()       const { return baseFareRate; }
double      ConfigManager::getSurgeMultiplier()    const { return surgeMultiplier; }
double      ConfigManager::getDeliveryWeightRate() const { return deliveryWeightRate; }
std::string ConfigManager::getFleetFile()          const { return fleetFile; }
std::string ConfigManager::getTripLogFile()        const { return tripLogFile; }
std::string ConfigManager::getLogFile()            const { return logFile; }

// Setters
void ConfigManager::setMaxTicks(int v)        { maxTicks = v; }
void ConfigManager::setMapSize(int v)         { mapSize = v; }
void ConfigManager::setRequestsPerTick(int v) { requestsPerTick = v; }
void ConfigManager::setBaseFareRate(double v) { baseFareRate = v; }

void ConfigManager::display() const {
    std::cout << "\n=== Config ===\n"
              << "  max_ticks          : " << maxTicks           << "\n"
              << "  map_size           : " << mapSize            << "\n"
              << "  requests_per_tick  : " << requestsPerTick    << "\n"
              << "  max_drivers        : " << maxDrivers         << "\n"
              << "  base_fare_rate     : " << baseFareRate       << "\n"
              << "  surge_multiplier   : " << surgeMultiplier    << "\n"
              << "  delivery_weight_rate: " << deliveryWeightRate << "\n"
              << "  fleet_file         : " << fleetFile          << "\n"
              << "  trip_log_file      : " << tripLogFile        << "\n"
              << "  log_file           : " << logFile            << "\n";
}