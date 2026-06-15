// main.cpp
#include <iostream>
#include "Simulation.h"
#include "ConfigManager.h"
#include "FileHandler.h"
#include "Logger.h"
#include "RideshareExceptions.h"

int main() {
    // Logger is the first thing we create
    Logger logger("data/simulation.log", true);  // true = also print to console

    try {
        FileHandler::createFolder("data");

        ConfigManager& config = ConfigManager::getInstance();
        config.loadFromFile("data/config.txt");
        config.display();

        logger.info("Simulation starting.");

        Simulation sim(config.getMaxTicks(),
                       config.getMapSize(),
                       config.getRequestsPerTick());

        sim.addDriver("Ravi Kumar",
                      Location(2, 3),
                      Vehicle("KA-01-AB-1234", VehicleType::CAR, 4, 2.5), 4.8);
        sim.addDriver("Suresh Nair",
                      Location(7, 1),
                      Vehicle("MH-12-CD-5678", VehicleType::TRUCK, 2, 1.2), 4.5);
        sim.addDriver("Priya Singh",
                      Location(4, 6),
                      Vehicle("DL-05-EF-9999", VehicleType::BIKE, 1, 3.0), 4.9);
        sim.addDriver("Amit Desai",
                      Location(1, 9),
                      Vehicle("GJ-03-GH-7777", VehicleType::CAR, 4, 2.8), 4.7);

        sim.run();

        logger.info("Simulation complete. Trips: " +
                    std::to_string(sim.getTotalTrips()));

        sim.getAnalytics().saveReportToFile("data/report.txt");
        logger.info("Analytics report saved to data/report.txt");

        config.saveToFile("data/config.txt");

    } catch (const RideshareException& e) {
        // Catches any of our custom exceptions
        logger.error(e.what());
        std::cerr << "\n[FATAL] " << e.what() << "\n";
        return 1;

    } catch (const std::exception& e) {
        // Catches anything else (std::bad_alloc etc.)
        logger.error(std::string("Unexpected error: ") + e.what());
        std::cerr << "\n[FATAL] Unexpected error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}