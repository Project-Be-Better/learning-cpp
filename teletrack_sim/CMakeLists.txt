cmake_minimum_required(VERSION 3.15)
project(TeleTrackSim)

set(CMAKE_CXX_STANDARD 17)

# Conan 2.x integration via CMakeDeps
find_package(PahoMqttCpp REQUIRED)

# Add module subdirectories
add_subdirectory(modules/gnss)
add_subdirectory(modules/engine)
add_subdirectory(modules/logger)
add_subdirectory(modules/aggregator)

# Create the main executable
add_executable(teletrack_sim main.cpp)

# Link module libs + MQTT
target_link_libraries(teletrack_sim
    gnss_simulator
    engine_simulator
    logger
    aggregator
    PahoMqttCpp::paho-mqttpp3-static
)
