// Fleet.h
#pragma once
#include <vector>
#include <memory>
#include "Driver.h"

class Fleet {
private:
    std::vector<std::shared_ptr<Driver>> drivers;
    int nextId;

public:
    Fleet();
    // Add to Fleet.h public section
    const std::vector<std::shared_ptr<Driver>>& getDrivers() const;
    void addDriver(const std::string& name, const Location& loc, const Vehicle& vehicle, double rating = 5.0);
    void removeDriver(int driverId);

    std::shared_ptr<Driver> findById(int driverId) const;
    std::shared_ptr<Driver> findNearestAvailable(const Location& pickup) const;

    std::vector<std::shared_ptr<Driver>> getAvailableDrivers() const;

    int  getTotalDrivers()    const;
    int  getAvailableCount()  const;
    void displayAll()         const;
};