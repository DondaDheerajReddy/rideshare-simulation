// Logger.cpp
#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

Logger::Logger(const std::string& filepath, bool echoToConsole)
    : logFilePath(filepath),
      echoToConsole(echoToConsole),
      fileStream(filepath, std::ios::app)
{
    if (!fileStream.is_open())
        std::cerr << "[LOGGER] Warning: could not open log file: "
                  << filepath << "\n";
    else
        log("Logger initialized.", LogLevel::INFO);
}

Logger::~Logger() {
    if (fileStream.is_open()) {
        log("Logger closing.", LogLevel::INFO);
        fileStream.close();
    }
}

std::string Logger::levelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::INFO:  return "INFO ";
        case LogLevel::WARN:  return "WARN ";
        case LogLevel::ERROR: return "ERROR";
        default:              return "INFO ";
    }
}

std::string Logger::timestamp() const {
    auto now     = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::string ts = std::ctime(&t);
    ts.erase(ts.find('\n'));
    return ts;
}

void Logger::log(const std::string& message, LogLevel level) {
    std::string entry = "[" + timestamp() + "] "
                      + "[" + levelToString(level) + "] "
                      + message;

    if (fileStream.is_open())
        fileStream << entry << "\n" << std::flush;

    if (echoToConsole)
        std::cout << entry << "\n";
}

void Logger::info (const std::string& msg) { log(msg, LogLevel::INFO);  }
void Logger::warn (const std::string& msg) { log(msg, LogLevel::WARN);  }
void Logger::error(const std::string& msg) { log(msg, LogLevel::ERROR); }

void Logger::setEchoToConsole(bool value) { echoToConsole = value; }