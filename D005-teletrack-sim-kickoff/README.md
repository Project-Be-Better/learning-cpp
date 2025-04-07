# Day 005: 2025_04_08

**🚀 Theme:** Project Kickoff – Modular Architecture & Handshake Validation

## ✅ Topics Covered

### 1. **Project Setup: TeleTrack Sim**

- Decided to build a modular, real-world telematics simulation system.
- Core idea: multiple independent modules (GNSS, Engine, Aggregator, Logger) simulate and coordinate system behavior.
- Each module is treated as a mini-application (just like in embedded systems or production microservices).

### 2. **Modular Folder Structure**

```
teletrack_sim/
├── main.cpp
├── CMakeLists.txt
├── modules/
│   ├── gnss/
│   ├── engine/
│   ├── logger/
│   └── aggregator/
```

- Each module has its own `include/` (headers) and `src/` (implementation).
- Helps enforce clean boundaries, testability, and reusability.

### 3. **Hello Handshake Pattern**

- Each module exposes a `sayHello()` function to simulate a startup handshake.
- Ensures the module is properly wired and responsive during boot-up.

```cpp
void GNSSSimulator::sayHello() {
    std::cout << "[GNSSSimulator] Hello from GNSS module!" << std::endl;
}
```

## 📁 Files Created

```
teletrack_sim/
├── main.cpp
├── CMakeLists.txt
└── modules/
    ├── gnss/
    │   ├── include/gnss_simulator.h
    │   └── src/gnss_simulator.cpp
    ├── engine/
    │   ├── include/engine_simulator.h
    │   └── src/engine_simulator.cpp
    ├── logger/
    │   ├── include/logger.h
    │   └── src/logger.cpp
    └── aggregator/
        ├── include/aggregator.h
        └── src/aggregator.cpp
```

## 🧠 Concepts Learned

| Concept                   | Notes                                                          |
| ------------------------- | -------------------------------------------------------------- |
| **Modular C++ Design**    | Every system has its own folder, header, source, and namespace |
| **Header Files (`.h`)**   | Declare class interfaces for each module                       |
| **Source Files (`.cpp`)** | Implement actual logic behind declared classes                 |
| **CMake Basics**          | Used to wire together all modules for compilation              |
| **Encapsulation**         | Clean separation allows isolated testing and replacement       |

## 📝 Reflections

- Loved seeing all modules shake hands independently — it felt like orchestrating real subsystems!
- Starting to understand why project structure and modularity matters so much.
- Beginning to visualize how this will evolve with FSM, Redis, MQTT, and SQL.

## 🔜 Next Goals (Day 006 Plan)

- Add telemetry data simulation logic to `GNSS` and `Engine` modules.
- Add a simple `Logger` to write logs to file.
- Begin defining finite state machine logic and transitions (e.g., `OFF → IGNITION → DRIVING`).
