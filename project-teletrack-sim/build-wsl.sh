#!/bin/bash 

# Exit immediately if anything fails
set -e 

# VARIABLES
# ---------
BUILD_DIR="build"                           # Directory where build artifacts will be placed 
EXE_PATH="app/Debug/project-teletrack-sim"  # Relative path to build once it is built 
VENV_PATH=".venv-conan"
ACTIVATE_VENV_SCRIPT="$VENV_PATH/Scripts/activate"

# HANDLE VENV
# -----------

if [ ! -d "$VENV_PATH" ];then                 # If no venv exists, create a new one
    echo "🤖 Creating Python venv for Conan at $VENV_PATH"
    python -m venv "$VENV_PATH"
else
    echo "🟢 venv already exists at $VENV_PATH"
fi 

echo "🤖 Activating venv"
source "$ACTIVATE_VENV_SCRIPT"

# HANDLE CONAN
# ----------------
if command -v conan > /dev/null; then
    echo "🟢 Conan exists at $VENV_PATH"
else 
    echo "🤖 Installing Conan inside venv..."
    pip install conan    
fi

# CREATE DIRECTORY
# ----------------
if [ ! -d "$BUILD_DIR" ];then 
    echo "🤖 Creating build folder..."
    mkdir -p "$BUILD_DIR"                   # Create build directory and enter it 
fi 

cd "$BUILD_DIR"                             # Change to the build directory

# RUN CONAN and HANDLE CONAN PROFILE
# ----------------------------------
CONAN_PROFILE_PATH="$HOME/.conan2/profiles/default"
if [ ! -f "$CONAN_PROFILE_PATH" ]; then
    echo "🤖 Conan profile not found — generating default profile..."
    conan profile detect --force
else
    echo "🟢 Conan default profile already exists"
fi


echo "🤖 Running Conan..."
conan install .. --output-folder=. --build=missing

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