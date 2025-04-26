################################################################################
# modules/gnss_simulator/CMakeLists.txt
################################################################################

# 1) Build the GNSS simulator library
add_library(gnss_simulator
  src/gnss.cpp
)

target_include_directories(gnss_simulator
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 2) Unit tests (only when BUILD_TESTING is ON)
if (BUILD_TESTING)
  # Locate the Conan‐installed GTest package
  find_package(GTest CONFIG REQUIRED)

  # Declare the test executable
  add_executable(test_gnss
    tests/test_gnss.cpp
  )

  # Link against the simulator library and GTest’s main()
  target_link_libraries(test_gnss
    PRIVATE
      gnss_simulator
      GTest::gtest_main
  )

  # Register with CTest
  include(GoogleTest)
  gtest_discover_tests(test_gnss
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTIES LABELS "unit;gnss"
  )
endif()
