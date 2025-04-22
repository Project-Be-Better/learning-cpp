#!/bin/bash 

# Exit immediately if anything fails
set -e 

# VARIABLES
# ---------

BUILD_DIR="build"                           # Directory where build artifacts will be placed 
EXE_PATH="app/Debug/project-teletrack-sim"  # Relative path to build once it is built 


# CREATE DIRECTORY
# ----------------
mkdir -p "$BUILD_DIR"                       # Create build directory and enter it 
cd "$BUILD_DIR"                             # Change to the build directory

# RUN CMAKE TO CONFIGURE THE PROJECT 
# ----------------------------------
cmake .. -G "Visual Studio 17 2022" -A x64  # Go to the root of the prject, out of the build folder and 
                                            # Use VS as a generator
cmake --build . --config Debug              # Build using the debug configuration

# Run Executables
echo ""
echo ""
echo "----------------------------------"
echo "🚀 Running Teletrack Sim.."
echo "----------------------------------"
"./$EXE_PATH"