// SimulationClock.h
#pragma once
#include <string>

class SimulationClock {
private:
    int  tick;
    int  maxTicks;
    bool running;

public:
    SimulationClock(int maxTicks = 100);

    void advance();       // increment tick by 1
    void reset();
    void stop();

    int  getTick()      const;
    int  getMaxTicks()  const;
    bool isRunning()    const;
    bool hasExpired()   const;  // true when tick >= maxTicks

    std::string toString() const;
};