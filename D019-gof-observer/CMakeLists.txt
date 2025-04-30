cmake_minimum_required(VERSION 3.16..3.24)

project(project_teletrack_sim
    VERSION 0.0.1
    DESCRIPTION "Simple Transport Simulation"
    LANGUAGES CXX
)

# Add the executable
add_executable(project_teletrack_sim
    src/main.cpp
    src/observer.cpp
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
