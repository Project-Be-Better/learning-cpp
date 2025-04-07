# modules/logger/CMakeLists.txt

add_library(logger
    src/logger.cpp
)

target_include_directories(logger PUBLIC include)
