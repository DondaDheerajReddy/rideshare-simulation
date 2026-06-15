#pragma once
#include <cmath>
#include <string>

struct Location {
    double x;
    double y;

    Location(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    double distanceTo(const Location& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    std::string toString() const {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};