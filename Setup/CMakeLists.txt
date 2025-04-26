################################################################################
# Root CMakeLists.txt for project-teletrack-sim
################################################################################

 cmake_minimum_required(VERSION 3.16..3.24)

 project(project_teletrack_sim
         VERSION 0.0.1
         DESCRIPTION "project-teletrack-sim"
         LANGUAGES CXX
 )


# Testing support
include(CTest)
enable_testing()       # ← turn on BUILD_TESTING so subdirs add their tests

find_package(GTest CONFIG REQUIRED)

# Add your modules
add_subdirectory(modules/gnss_simulator)

# Main executable
add_executable(project_teletrack_sim
     src/main.cpp
 )

 target_include_directories(project_teletrack_sim PRIVATE
     modules/gnss_simulator/include
 )

 target_link_libraries(project_teletrack_sim PRIVATE
     gnss_simulator
 )
