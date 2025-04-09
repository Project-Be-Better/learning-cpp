#!/bin/bash
set -e

# Optional flags
CLEAN_BUILD=false
ENABLE_TESTING=false

# Parse input arguments
for arg in "$@"; do
  if [[ "$arg" == "--clean" ]]; then
    CLEAN_BUILD=true
    echo "🧹 Clean build requested."
  elif [[ "$arg" == "--test" ]]; then
    ENABLE_TESTING=true
    echo "🧪 Test build enabled."
  fi
done

# Ensure python venv support
if ! dpkg -s python3-venv &> /dev/null; then
    echo "🧱 Installing python3-venv..."
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
    echo "📦 Installing Conan..."
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
echo "🛠 Configuring CMake..."
cmake -S. -Bbuild \
  -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_TESTING=$ENABLE_TESTING

# Build project
echo "🔨 Building project..."
cmake --build build -- -j$(nproc)

# Run tests only if --test was passed
if $ENABLE_TESTING; then
  echo "🧪 Running unit tests..."
  cd build
  ctest --output-on-failure
  cd ..
fi

# Run main app
echo "🚀 Running TeleTrackSim..."
./build/teletrack_sim
