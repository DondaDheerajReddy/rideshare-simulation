// FileHandler.h
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Fleet.h"
#include "TripLog.h"

class FileHandler {
public:
    // No constructor needed — all methods are static
    FileHandler() = delete;

    // Fleet
    static bool saveFleet(const Fleet&       fleet,
                          const std::string& filepath);
    static bool loadFleet(Fleet&             fleet,
                          const std::string& filepath);

    // Trip log
    static bool saveTripLog(const TripLog&     tripLog,
                            const std::string& filepath);

    // Logger — append a line to the simulation log
    static bool log(const std::string& message,
                    const std::string& filepath,
                    const std::string& level = "INFO");

    // Utility
    static bool        fileExists(const std::string& filepath);
    static bool        createFolder(const std::string& path);
    static std::string timestamp();
};