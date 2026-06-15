// SimulationClock.cpp
#include "SimulationClock.h"
#include <string>

SimulationClock::SimulationClock(int maxTicks)
    : tick(0), maxTicks(maxTicks), running(true) {}

void SimulationClock::advance() {
    if (running && !hasExpired())
        tick++;
}

void SimulationClock::reset() {
    tick    = 0;
    running = true;
}

void SimulationClock::stop() {
    running = false;
}

int  SimulationClock::getTick()     const { return tick; }
int  SimulationClock::getMaxTicks() const { return maxTicks; }
bool SimulationClock::isRunning()   const { return running; }
bool SimulationClock::hasExpired()  const { return tick >= maxTicks; }

std::string SimulationClock::toString() const {
    return "Tick " + std::to_string(tick) + "/" + std::to_string(maxTicks);
}