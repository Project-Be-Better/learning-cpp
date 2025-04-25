# CMakeList.txt : CMake project for project-teletrack-sim, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("project-teletrack-sim")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)





# Add source to this project's executable.
# add_executable (project-teletrack-sim "src/project-teletrack-sim.cpp" "include/project-teletrack-sim.h")

add_subdirectory(app)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET project-teletrack-sim PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
