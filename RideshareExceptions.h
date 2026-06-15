// RideshareExceptions.h
#pragma once
#include <exception>
#include <string>

// ── Base exception for all rideshare errors ────────────────────
class RideshareException : public std::exception {
protected:
    std::string message;
public:
    explicit RideshareException(const std::string& msg)
        : message("[RideshareError] " + msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// ── No driver available when dispatching ──────────────────────
class NoDriverAvailableException : public RideshareException {
public:
    explicit NoDriverAvailableException(int requestId)
        : RideshareException(
            "No driver available for request #" +
            std::to_string(requestId)) {}
};

// ── Fare calculated is zero or negative ───────────────────────
class InvalidFareException : public RideshareException {
public:
    explicit InvalidFareException(int requestId, double fare)
        : RideshareException(
            "Invalid fare $" + std::to_string(fare) +
            " for request #" + std::to_string(requestId)) {}
};

// ── Dequeue or peek on empty queue ────────────────────────────
class QueueEmptyException : public RideshareException {
public:
    QueueEmptyException()
        : RideshareException("Cannot operate on an empty request queue.") {}
};

// ── Invalid constructor arguments ─────────────────────────────
class InvalidArgumentException : public RideshareException {
public:
    explicit InvalidArgumentException(const std::string& context,
                                      const std::string& reason)
        : RideshareException("Invalid argument in " + context +
                             ": " + reason) {}
};

// ── File could not be opened ──────────────────────────────────
class FileIOException : public RideshareException {
public:
    explicit FileIOException(const std::string& filepath)
        : RideshareException("Could not open file: " + filepath) {}
};

// ── TripLog accessed while empty ──────────────────────────────
class TripLogEmptyException : public RideshareException {
public:
    TripLogEmptyException()
        : RideshareException("TripLog is empty — no trips recorded yet.") {}
};