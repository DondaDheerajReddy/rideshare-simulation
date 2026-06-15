// Fleet.cpp
#include "Fleet.h"
#include <iostream>
#include <limits>
#include <algorithm>

Fleet::Fleet() : nextId(1) {}

// Add to Fleet.cpp
const std::vector<std::shared_ptr<Driver>>& Fleet::getDrivers() const {
    return drivers;
}

void Fleet::addDriver(const std::string& name, const Location& loc,
                      const Vehicle& vehicle, double rating) {
    auto driver = std::make_shared<Driver>(nextId++, name, loc, vehicle, rating);
    drivers.push_back(driver);
    std::cout << "Driver added: " << name << " (ID: " << driver->getId() << ")\n";
}

void Fleet::removeDriver(int driverId) {
    auto it = std::remove_if(drivers.begin(), drivers.end(),
        [driverId](const std::shared_ptr<Driver>& d) {
            return d->getId() == driverId;
        });

    if (it != drivers.end()) {
        std::cout << "Driver ID " << driverId << " removed from fleet.\n";
        drivers.erase(it, drivers.end());
    } else {
        std::cout << "Driver ID " << driverId << " not found.\n";
    }
}

std::shared_ptr<Driver> Fleet::findById(int driverId) const {
    for (const auto& d : drivers)
        if (d->getId() == driverId)
            return d;
    return nullptr;
}

std::shared_ptr<Driver> Fleet::findNearestAvailable(const Location& pickup) const {
    std::shared_ptr<Driver> nearest = nullptr;
    double minDist = std::numeric_limits<double>::max();

    for (const auto& d : drivers) {
        if (!d->isAvailable()) continue;
        double dist = d->getLocation().distanceTo(pickup);
        if (dist < minDist) {
            minDist = dist;
            nearest = d;
        }
    }
    return nearest;
}

std::vector<std::shared_ptr<Driver>> Fleet::getAvailableDrivers() const {
    std::vector<std::shared_ptr<Driver>> available;
    for (const auto& d : drivers)
        if (d->isAvailable())
            available.push_back(d);
    return available;
}

int Fleet::getTotalDrivers()   const { return drivers.size(); }
int Fleet::getAvailableCount() const { return getAvailableDrivers().size(); }

void Fleet::displayAll() const {
    std::cout << "=== Fleet (" << drivers.size() << " drivers) ===\n";
    for (const auto& d : drivers)
        d->display();
}