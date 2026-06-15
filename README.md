# Multi-Vehicle Ride-Sharing & Logistics Simulation Engine

A command-line simulation engine built in **C++17** that models a real-world ride-sharing and logistics platform. The project demonstrates all four pillars of Object-Oriented Programming across 20+ classes, a priority-based dispatch engine, discrete-time simulation loop, file persistence, and a severity-based logging system.

---

## Features

- **Multiple ride types** — Standard, Shared, Premium, and Delivery requests each with unique fare logic
- **Smart dispatch engine** — matches the nearest available driver to each request using a priority queue
- **Discrete-time simulation** — tick-based loop that spawns random requests and dispatches them each tick
- **Fleet management** — add, remove, and query drivers with real-time availability tracking
- **Trip state machine** — every trip transitions through `REQUESTED → ACCEPTED → EN_ROUTE → COMPLETED`
- **Analytics & reporting** — fare summaries, trip breakdowns, and a driver earnings leaderboard
- **File persistence** — fleet and trip log serialized to CSV, config loaded from a key-value file
- **Custom exception hierarchy** — typed exceptions for every failure mode
- **Severity-based logger** — `INFO`, `WARN`, `ERROR` entries written to a timestamped log file

---

## OOP Concepts Demonstrated

| Pillar | Where |
|---|---|
| **Encapsulation** | Every class exposes only what it needs to through a public interface |
| **Inheritance** | `Driver`/`Passenger` → `Person`; all ride types → `RideRequest`; all exceptions → `RideshareException` |
| **Polymorphism** | `vector<unique_ptr<RideRequest>>` calls the correct `calculateFare()` and `display()` at runtime |
| **Abstraction** | `Person` and `RideRequest` are abstract base classes — never instantiated directly |
| **Composition** | `Driver` has-a `Vehicle`; `Simulation` owns all subsystems |
| **Singleton** | `ConfigManager` — one global config instance throughout the program |
| **RAII** | `Logger` opens file in constructor, closes it in destructor |
| **Smart pointers** | `shared_ptr` for drivers shared across subsystems; `unique_ptr` for exclusive request ownership |
| **Operator overloading** | `operator<<` on `Trip` and `DriverReport`; `operator>` on `DriverReport` for sorting |
| **Copy semantics** | Manual copy constructor and assignment operator on `Vehicle` |
| **Exception hierarchy** | Custom exceptions inherit from `RideshareException` → `std::exception` |
| **STL containers** | `vector`, `priority_queue`, `deque`, `map` used across different subsystems |

---

## Project Structure

```
rideshare/
│
├── main.cpp
│
├── Location.h                  # Coordinate struct with distanceTo()
│
├── Vehicle.h / .cpp            # Vehicle type, capacity, speed
├── Person.h / .cpp             # Abstract base — Driver and Passenger
├── Driver.h / .cpp             # Inherits Person, owns a Vehicle
├── Passenger.h / .cpp          # Inherits Person, tracks ride history
│
├── RideRequest.h / .cpp        # Abstract base for all request types
├── StandardRide.h / .cpp       # Single passenger, distance-based fare
├── SharedRide.h / .cpp         # Pooled ride, discounted per-passenger fare
├── DeliveryRequest.h / .cpp    # Package delivery with weight and priority
├── PremiumRide.h / .cpp        # Luxury ride with surge multiplier
│
├── Fleet.h / .cpp              # Manages all Driver objects
├── RequestQueue.h / .cpp       # Priority queue of pending requests
├── Trip.h                      # Trip struct with state machine enum
├── TripLog.h / .cpp            # Deque of completed trips
│
├── DispatchEngine.h / .cpp     # Matches drivers to requests
├── SimulationClock.h / .cpp    # Tick counter and run control
├── Simulation.h / .cpp         # Owns all subsystems, runs the loop
│
├── AnalyticsEngine.h / .cpp    # Fare, trip, and driver reporting
├── DriverReport.h              # Per-driver stats struct
│
├── ConfigManager.h / .cpp      # Singleton config loaded from file
├── FileHandler.h / .cpp        # Static save/load/log utilities
├── Logger.h / .cpp             # Severity-based file logger
├── RideshareExceptions.h       # All custom exception classes
│
└── data/
    ├── config.txt              # Simulation parameters
    ├── fleet.csv               # Saved driver state
    ├── triplog.csv             # Completed trip records
    ├── simulation.log          # Runtime log with timestamps
    └── report.txt              # Analytics report
```

---

## Getting Started

### Prerequisites

- A C++17 compatible compiler (`g++` 7 or later recommended)

### Build

Clone the repository and compile all source files:

```bash
git clone https://github.com/DondaDheerajReddy/rideshare-simulation.git
cd rideshare-simulation
```

```bash
g++ -std=c++17 main.cpp Vehicle.cpp Person.cpp Driver.cpp Passenger.cpp \
    RideRequest.cpp StandardRide.cpp SharedRide.cpp DeliveryRequest.cpp \
    PremiumRide.cpp Fleet.cpp RequestQueue.cpp TripLog.cpp \
    DispatchEngine.cpp Simulation.cpp SimulationClock.cpp \
    ConfigManager.cpp FileHandler.cpp AnalyticsEngine.cpp Logger.cpp \
    -o rideshare
```

### Run

```bash
./rideshare
```

---

## Configuration

Edit `data/config.txt` before running to adjust simulation parameters:

```
# Rideshare Simulation Config
max_ticks            = 15
map_size             = 10
requests_per_tick    = 2
max_drivers          = 10
base_fare_rate       = 2.0
surge_multiplier     = 1.5
delivery_weight_rate = 1.5
fleet_file           = data/fleet.csv
trip_log_file        = data/triplog.csv
log_file             = data/simulation.log
```

| Parameter | Description |
|---|---|
| `max_ticks` | How many time steps the simulation runs |
| `map_size` | Grid dimensions (map is `map_size x map_size`) |
| `requests_per_tick` | New ride/delivery requests spawned each tick |
| `base_fare_rate` | Base multiplier used in fare calculations |
| `surge_multiplier` | Default surge for Premium rides |
| `delivery_weight_rate` | Cost per kg for Delivery requests |

---

## Sample Output

```
========================================
   Simulation Started
   Max ticks      : 15
   Map size       : 10x10
   Requests/tick  : 2
   Drivers        : 4
========================================

────────────────────────────────
  Tick 0/15
────────────────────────────────
  [DISPATCH] Processing Standard Request #1
  [ACCEPTED]  Driver Ravi Kumar assigned to Request #1
  [EN_ROUTE]  Driver travelling 2.82 units to pickup
  [COMPLETED] Fare charged: $18.31

========================================
         SIMULATION ANALYTICS REPORT
========================================
=== Fare Summary ===
  Total revenue  : $312.45
  Average fare   : $22.31
  Highest fare   : $67.80
  Lowest fare    : $9.20

=== Trip Breakdown ===
  Total trips    : 14
  Standard rides : 5
  Shared rides   : 3
  Deliveries     : 4
  Premium rides  : 2

=== Driver Leaderboard ===
  #1 Driver #1 | Ravi Kumar  | Trips: 5 | Earnings: $98.20 | Avg Rating: 4.80
  #2 Driver #4 | Amit Desai  | Trips: 4 | Earnings: $87.15 | Avg Rating: 4.70
  #3 Driver #2 | Suresh Nair | Trips: 3 | Earnings: $74.60 | Avg Rating: 4.50
  #4 Driver #3 | Priya Singh | Trips: 2 | Earnings: $52.50 | Avg Rating: 4.90
```

---

## Output Files

After running, the `data/` folder contains:

| File | Contents |
|---|---|
| `simulation.log` | Timestamped INFO/WARN/ERROR entries from the entire run |
| `report.txt` | Full analytics report — fares, trip counts, leaderboard |
| `fleet.csv` | Final driver state — location, rating, trips completed |
| `triplog.csv` | Every completed trip — driver, type, fare, tick |
| `config.txt` | Config saved back after run (reflects any runtime changes) |

---

## Key Design Decisions

**Why is `RideRequest` abstract?**
Each ride type has fundamentally different fare logic. Making `calculateFare()` pure virtual forces every subclass to implement its own version, and allows the dispatch engine to work with any request type through a single base pointer.

**Why does `ConfigManager` use a private constructor?**
The Singleton pattern ensures there is exactly one config instance shared across all subsystems. A private constructor prevents anyone from creating a second instance accidentally.

**Why `shared_ptr` for drivers?**
A driver object is referenced by both `Fleet` (for management) and `TripLog` (for trip records). `shared_ptr` lets both subsystems hold a reference safely without either owning it exclusively.

**Why does `AnalyticsEngine` hold const references?**
It reads data from `TripLog` and `Fleet` without owning or copying them. Const references make the read-only relationship explicit and avoid expensive copies of large containers.

---

## License

ISC
