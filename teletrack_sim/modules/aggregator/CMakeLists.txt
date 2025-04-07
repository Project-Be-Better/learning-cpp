# modules/aggregator/CMakeLists.txt

add_library(aggregator
    src/aggregator.cpp
)

target_include_directories(aggregator PUBLIC include)
