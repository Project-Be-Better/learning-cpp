cmake_minimum_required(VERSION 3.10)
project(mqtt_publisher)

find_package(PahoMqttCpp REQUIRED)

add_library(mqtt_publisher
    src/MqttPublisher.cpp
)

target_include_directories(mqtt_publisher
    PUBLIC include
)

target_link_libraries(mqtt_publisher
    PUBLIC PahoMqttCpp::paho-mqttpp3
)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
