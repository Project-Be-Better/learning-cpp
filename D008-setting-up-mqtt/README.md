# 🧭 Day 008 – MQTT Publisher Interface + Class Scaffolding in `TeleTrackSim`

## ✅ Objective  
Begin modular implementation of MQTT publishing for GNSS and other telemetry data using:
- Clean interface-based design (`IPublisher`)
- Concrete implementation (`MqttPublisher`) using Paho MQTT C++ Client
- Smart pointers and exception-safe design
- Prepare for unit test and message publishing in Day 009


## 📘 Summary of All Steps

| Step | Description |
|------|-------------|
| 1 | Created `IPublisher` interface with virtual methods: `connect()`, `publish()`, `disconnect()`, `isConnected()` |
| 2 | Declared and defined class `MqttPublisher` inheriting `IPublisher` |
| 3 | Set up `MqttPublisher` header to store server URI, client ID, and a `unique_ptr` to `mqtt::async_client` |
| 4 | Implemented `disconnect()` and `isConnected()` methods |
| 5 | Wrote skeletons for `connect()` and `publish()` (to be completed on Day 009) |
| 6 | Clarified where and how the TCP port is passed (via `serverUri`) |
| 7 | Verified that the interface works correctly and class structure compiles cleanly in CMake setup |


## 🐞 Issues and Fixes

| Issue | Cause | Fix |
|-------|-------|-----|
| Missing port config in code | Port is passed via `tcp://host:port` URI string, not as a separate int | Clarified in learning note and constructor usage |
| Unclear `connect()` & `publish()` state | These functions not yet implemented | Will complete them in Day 009 with proper `try/catch` and MQTT logic |
| MQTT headers squiggling in VSCode | Conan setup or path not complete yet | Will verify header resolution in Day 009 |


## 📁 Folder Structure (Essential View)

```
teletrack_sim/
└── modules/
    └── mqtt_publisher/
        ├── include/
        │   └── mqtt_publisher/
        │       ├── IPublisher.h
        │       └── MqttPublisher.h
        ├── src/
        │   └── MqttPublisher.cpp
        ├── test/
        │   └── MqttPublisherTest.cpp  (planned)
        └── CMakeLists.txt
```


## 🔌 MQTT URI Usage

```cpp
MqttPublisher pub("tcp://localhost:1883", "simClient");
```

> The port is specified as part of the `serverUri` string using standard URI syntax:  
> `tcp://<host>:<port>`


## 📘 Code: Interface and Class Implementation

**IPublisher.h**

```cpp
#pragma once
#include <string>

namespace teletrack_sim {
    class IPublisher {
    public:
        virtual ~IPublisher() = default;
        virtual bool connect() = 0;
        virtual bool publish(const std::string&, const std::string&, int qos = 0) = 0;
        virtual void disconnect() = 0;
        virtual bool isConnected() const = 0;
    };
}
```

**MqttPublisher.h**

```cpp
#pragma once
#include "mqtt_publisher/IPublisher.h"
#include <memory>
#include <string>

namespace mqtt { class async_client; }

namespace teletrack_sim {
    class MqttPublisher : public IPublisher {
    public:
        MqttPublisher(const std::string& serverUri, const std::string& clientId);
        ~MqttPublisher();
        bool connect() override;
        bool publish(const std::string&, const std::string&, int qos = 0) override;
        void disconnect() override;
        bool isConnected() const override;

    private:
        std::string serverUri_;
        std::string clientId_;
        std::unique_ptr<mqtt::async_client> client_;
        bool connected_;
    };
}
```

**MqttPublisher.cpp (Partial)**

```cpp
#include "mqtt_publisher/MqttPublisher.h"
#include <mqtt/async_client.h>
#include <iostream>

namespace teletrack_sim {

MqttPublisher::MqttPublisher(const std::string &serverUri, const std::string &clientId)
    : serverUri_(serverUri), clientId_(clientId), connected_(false) {
    client_ = std::make_unique<mqtt::async_client>(serverUri_, clientId_);
}

MqttPublisher::~MqttPublisher() {
    if (connected_) {
        disconnect();
    }
}

bool MqttPublisher::connect() {
    // TODO: implement in Day 009
    return false;
}

bool MqttPublisher::publish(const std::string &topic, const std::string &message, int qos) {
    // TODO: implement in Day 009
    return false;
}

void MqttPublisher::disconnect() {
    if (!connected_) return;

    try {
        client_->disconnect()->wait();
        connected_ = false;
        std::cout << "[MQTT] Disconnected from Broker \n";
    } catch (const std::exception &e) {
        std::cerr << "[MQTT] Disconnect failed: " << e.what() << std::endl;
    }
}

bool MqttPublisher::isConnected() const {
    return connected_;
}

}
```


## 🧠 Key Takeaways

| Topic | Learning |
|-------|----------|
| URI-based configuration | MQTT port is passed inside the URI string, not separately |
| Interface inheritance | Cleanly enables mocking and decoupled usage in other modules |
| Destructor safety | Using RAII + virtual destructor = clean shutdowns |
| Smart pointers | `unique_ptr` keeps client lifecycle safe without memory leaks |
| Structure-first approach | Scaffolding before implementation helps catch interface issues early |
