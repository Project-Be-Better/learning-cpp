# modules/engine/CMakeLists.txt

add_library(engine_simulator
    src/engine_simulator.cpp
)

target_include_directories(engine_simulator PUBLIC include)
