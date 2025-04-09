# modules/gnss/CMakeLists.txt

# 1. Create the GNSS simulator module library
add_library(gnss_simulator
    src/gnss_simulator.cpp
)

# 2. Set the include path so it can be found when linked elsewhere
target_include_directories(gnss_simulator PUBLIC include)

# 3. If testing is enabled, add test executable
if (BUILD_TESTING)
    # Find GoogleTest package (provided by Conan)
    find_package(GTest REQUIRED)

    # Define the test binary
    add_executable(test_gnss test/test_gnss_simulator.cpp)

    # Link simulator + gtest to test binary
    target_link_libraries(test_gnss
        gnss_simulator
        GTest::gtest_main
    )

    # Add test to CTest framework
    add_test(NAME GnssTests COMMAND test_gnss)
endif()
