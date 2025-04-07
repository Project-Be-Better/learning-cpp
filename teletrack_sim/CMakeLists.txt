cmake_minimum_required(VERSION 3.10)  # Specifies the minimum CMake version needed
project(TeleTrackSim)  # Defines the project name

set(CMAKE_CXX_STANDARD 17)  # Sets C++17 as the language standard for all targets

# Add subdirectories for each module
# Each add_subdirectory command:
# 1. Tells CMake to process the CMakeLists.txt file in that subdirectory
# 2. Allows each module to be compiled independently
# 3. Makes libraries defined in those subdirectories available to the main project
add_subdirectory(modules/gnss)        # Processes GNSS module's CMakeLists.txt
add_subdirectory(modules/engine)      # Processes engine module's CMakeLists.txt
add_subdirectory(modules/logger)      # Processes logger module's CMakeLists.txt
add_subdirectory(modules/aggregator)  # Processes aggregator module's CMakeLists.txt

# Create the executable and link module libs
add_executable(teletrack_sim  # Creates the main executable target named "teletrack_sim"
    main.cpp                  # Only main.cpp is directly compiled into the executable
)

# Links the independently compiled module libraries to the main executable
# Each of these libraries should be defined in their respective subdirectory's CMakeLists.txt
# This approach allows modules to be compiled separately and then linked together
target_link_libraries(teletrack_sim
    gnss_simulator    # Links the GNSS module library
    engine_simulator  # Links the engine module library
    logger            # Links the logger module library
    aggregator        # Links the aggregator module library
)
