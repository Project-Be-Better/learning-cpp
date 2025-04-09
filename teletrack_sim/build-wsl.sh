#!/bin/bash
set -e

# Optional clean flag
CLEAN_BUILD=false
if [[ "$1" == "--clean" ]]; then
  CLEAN_BUILD=true
  echo "🧹 Clean build requested. Will remove existing build folder..."
fi

# Ensure python venv support
if ! dpkg -s python3-venv &> /dev/null; then
    echo "🧱 Installing missing package: python3-venv"
    sudo apt update && sudo apt install -y python3-venv
fi

# Create venv if not present
if [ ! -d ".venv" ]; then
    echo "🌱 Creating Python virtual environment..."
    python3 -m venv .venv
fi

# Activate venv
echo "🔁 Activating .venv..."
source .venv/bin/activate

# Install Conan if not already
if ! command -v conan &> /dev/null; then
    echo "📦 Installing Conan into venv..."
    pip install conan
fi

# Detect Conan profile (safe to rerun)
conan profile detect --force

# Handle build directory
if $CLEAN_BUILD; then
  rm -rf build
fi

mkdir -p build

# Install dependencies
echo "📦 Installing project dependencies via Conan..."
conan install . -of=build --build=missing --conf tools.cmake.cmaketoolchain:generator=False

# Configure project
echo "🛠 Configuring with CMake..."
cmake -S. -Bbuild -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

# Build project
echo "🔨 Building project..."
cmake --build build -- -j$(nproc)

# Run app
echo "🚀 Running TeleTrackSim..."
./build/teletrack_sim