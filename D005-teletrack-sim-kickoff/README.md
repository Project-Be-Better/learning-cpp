# **Day 005: 2025_04_08**

**🚀 Theme:** Project Kickoff – Modular Architecture, Handshake Pattern & Tooling

## ✅ Topics Covered

### 1. **Project Setup: TeleTrack Sim**

- Decided to build a modular, realistic telematics simulation system in C++.
- Each component is treated as an independent sub-application (e.g., GNSS, Engine, Logger).
- Structured to mimic real embedded and automotive systems.
- Will be extended later with Redis and MQTT integration.

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

- Every module has:
  - `include/` for `.h` interface declarations
  - `src/` for `.cpp` implementations
- Clean separation = easier debugging, testability, reuse

### 3. **Hello Handshake Pattern**

- Each module has a `sayHello()` method to simulate a startup handshake.
- Verifies that module wiring and CMake integration are successful.

```cpp
void GNSSSimulator::sayHello() {
    std::cout << "[GNSSSimulator] Hello from GNSS module!" << std::endl;
}
```

### 4. **Submodule CMake Integration**

- Each module can now have its own `CMakeLists.txt`.
- The root `CMakeLists.txt` uses `add_subdirectory()` to include and link them.
- This structure supports isolated builds and unit tests per module.

```cmake
# Inside modules/gnss/CMakeLists.txt
add_library(gnss_simulator src/gnss_simulator.cpp)
target_include_directories(gnss_simulator PUBLIC include)
```

### 5. **Build Automation Scripts**

- Created a universal `build_and_run.bash` for root project compilation.
- Verified and debugged executable naming (`teletrack_sim` not `main`).
- Drafted per-module build scripts to compile and run individual module tests.

```bash
# Example snippet
g++ -std=c++17 -I include src/gnss_simulator.cpp test/gnss_test.cpp -o gnss_test
```

## 📁 Files & Folders Created

```
teletrack_sim/
├── main.cpp
├── CMakeLists.txt
└── modules/
    ├── gnss/
    │   ├── include/gnss_simulator.h
    │   └── src/gnss_simulator.cpp
    │   └── CMakeLists.txt
    ├── engine/
    │   ├── include/engine_simulator.h
    │   └── src/engine_simulator.cpp
    │   └── CMakeLists.txt
    ├── logger/
    │   ├── include/logger.h
    │   └── src/logger.cpp
    │   └── CMakeLists.txt
    └── aggregator/
        ├── include/aggregator.h
        └── src/aggregator.cpp
        └── CMakeLists.txt
```

## 🧠 Concepts Learned

| Concept                        | Notes                                                |
| ------------------------------ | ---------------------------------------------------- |
| **Modular C++ Design**         | Each component is treated like a mini-library        |
| **CMake Subdirectory Pattern** | Build each module with its own `CMakeLists.txt`      |
| **Header-Source Separation**   | `.h` for interface, `.cpp` for logic                 |
| **Build Automation**           | Shell scripts for project & module-level compilation |
| **Encapsulation**              | Clear boundaries between simulation layers           |
| **Redis + MQTT (Planned)**     | Will be integrated as `tools/` modules later         |

## 📝 Reflections

- The modularity now feels natural and clean — like real-world software design.
- I feel more confident navigating a multi-component system in C++.
- I’m now comfortable enough to begin simulating real vehicle data and FSM states.
- Redis and MQTT no longer feel scary — I see how they’ll plug in down the line.

## 🔜 Next Goals (Day 006 Plan)

- Begin injecting data into `GNSSSimulator` and `EngineSimulator`:
  - Simulate changing lat/lon
  - Random RPM and temperature
- Implement the first version of a Finite State Machine (FSM) loop.
- Begin writing basic logs to file via `Logger`.
