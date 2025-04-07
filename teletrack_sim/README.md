# 🚗 TeleTrack Sim

A modular C++ simulation of a vehicle telematics system built for educational and prototyping purposes.

## 🎯 Overview

**TeleTrack Sim** emulates a real-time vehicle telemetry pipeline with independent modules like GNSS, Engine, Logger, and Aggregator. It serves as a foundation for learning C++ architecture, state machines, sensor simulation, and future integration with systems like Redis and MQTT.

## 🧱 Project Structure

```
teletrack_sim/
├── main.cpp                   # Application entry point
├── CMakeLists.txt             # Root build config
├── modules/                   # Independent system modules
│   ├── gnss/                  # GNSS simulation
│   ├── engine/                # Engine simulation
│   ├── logger/                # Logging system
│   └── aggregator/            # Telemetry aggregator
```

Each module has:

```
modules/<module>/
├── include/    # Public interface (.h)
└── src/        # Implementation (.cpp)
```

## 🔧 Build Instructions

### ✅ One-Liner Build & Run (Linux/Mac/WSL)

```bash
./build_and_run.bash
```

### 🛠 Manual Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
./teletrack_sim
```

## 🧪 Testing Individual Modules

Each module may contain its own `test/` folder and local test runner script:

```bash
cd modules/gnss/test
./gnss_build_and_run.bash
```

## 🧠 Current Features

- ✅ Modular C++ architecture with per-module `CMakeLists.txt`
- ✅ GNSS and Engine "handshake" system for initialization verification
- ✅ Extensible design for FSM, logging, database, and communication layers

## 🛣️ Roadmap

| Feature          | Status     |
| ---------------- | ---------- |
| FSM Integration  | 🟡 Pending |
| Redis Support    | 🟡 Planned |
| MQTT Publishing  | 🟡 Planned |
| SQLite Storage   | 🔲 Later   |
| Python Dashboard | 🔲 Later   |
| WebSockets       | 🔲 Later   |

## 💡 Learning Focus

This project is built from the ground up without external C++ libraries (other than STL), to gain mastery over:

- C++ modular architecture
- CMake build systems
- Finite state machines
- Logging and simulation loops
- Future system integration (MQTT, Redis, WebSockets)

## 🧔 Author

**Sree**  
🚀 Learning C++ the real way — by building systems from scratch.
