cmake_minimum_required(VERSION 3.16..3.24)

project(project_teletrack_sim
    VERSION 0.0.1
    DESCRIPTION "Simple Transport Simulation"
    LANGUAGES CXX
)

# Add the executable
add_executable(project_teletrack_sim
    src/main.cpp
    src/traffic_light.cpp
)

# Tell the compiler where to find headers
target_include_directories(project_teletrack_sim PRIVATE
    include
)

# Set C++ standard
set_target_properties(project_teletrack_sim PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# --- Unit Testing Setup ---
include(CTest)
enable_testing()

if (BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    add_executable(test_traffic_light tests/test_traffic_light.cpp src/traffic_light.cpp)
    target_include_directories(test_traffic_light PRIVATE include)
    target_link_libraries(test_traffic_light PRIVATE GTest::gtest_main)
    add_test(NAME TrafficLightTest COMMAND test_traffic_light)
endif()
