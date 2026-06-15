// Logger.h
#pragma once
#include <string>
#include <fstream>

enum class LogLevel {
    INFO,
    WARN,
    ERROR
};

class Logger {
private:
    std::string   logFilePath;
    bool          echoToConsole;   // if true, also prints to stdout
    std::ofstream fileStream;

    std::string levelToString(LogLevel level) const;
    std::string timestamp()                   const;

public:
    Logger(const std::string& filepath, bool echoToConsole = false);
    ~Logger();

    void log(const std::string& message, LogLevel level = LogLevel::INFO);
    void info (const std::string& message);
    void warn (const std::string& message);
    void error(const std::string& message);

    void setEchoToConsole(bool value);
};