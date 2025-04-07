# modules/gnss/CMakeLists.txt

add_library(gnss_simulator
    src/gnss_simulator.cpp
)

target_include_directories(gnss_simulator PUBLIC include)
