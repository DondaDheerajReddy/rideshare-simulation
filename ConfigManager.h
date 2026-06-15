// ConfigManager.h
#pragma once
#include <string>

class ConfigManager {
private:
    // Private constructor — prevents direct instantiation
    ConfigManager();

    // Config values
    int    maxTicks;
    int    mapSize;
    int    requestsPerTick;
    int    maxDrivers;
    double baseFareRate;
    double surgeMultiplier;
    double deliveryWeightRate;
    std::string fleetFile;
    std::string tripLogFile;
    std::string logFile;

public:
    // Delete copy constructor and assignment — singleton must not be copied
    ConfigManager(const ConfigManager&)            = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    // The one and only way to get the instance
    static ConfigManager& getInstance();

    // Load from file — falls back to defaults if file missing
    bool loadFromFile(const std::string& filepath);

    // Save current config to file
    bool saveToFile(const std::string& filepath) const;

    // Getters
    int         getMaxTicks()          const;
    int         getMapSize()           const;
    int         getRequestsPerTick()   const;
    int         getMaxDrivers()        const;
    double      getBaseFareRate()      const;
    double      getSurgeMultiplier()   const;
    double      getDeliveryWeightRate() const;
    std::string getFleetFile()         const;
    std::string getTripLogFile()       const;
    std::string getLogFile()           const;

    // Setters
    void setMaxTicks(int v);
    void setMapSize(int v);
    void setRequestsPerTick(int v);
    void setBaseFareRate(double v);

    void display() const;
};