#!/bin/bash

set -e

BUILD_DIR="build"
VENV_DIR="venv"
DO_CLEAN=false
DO_TEST=false
BUILD_ONLY=false
RUN_DEMO=false

function print_help {
  echo ""
  echo "Usage: ./run.sh [--clean] [--test] [--build-only] [--run]"
  echo ""
  echo "  --clean        Remove build directory before building"
  echo "  --test         Run tests after building"
  echo "  --build-only   Skip tests after building"
  echo "  --run          Run the memory_demo executable after building"
  echo "  --help         Show this help message"
  echo ""
  exit 0
}

# === Parse Arguments ===
for arg in "$@"; do
  case $arg in
    --clean)
      DO_CLEAN=true
      ;;
    --test)
      DO_TEST=true
      ;;
    --build-only)
      BUILD_ONLY=true
      ;;
    --run)
      RUN_DEMO=true
      ;;
    --help)
      print_help
      ;;
    *)
      echo "❌  Unknown argument: $arg"
      print_help
      ;;
  esac
done

# === [1] Setup Virtualenv ===
if [ ! -d "$VENV_DIR" ]; then
  echo "🔧 Creating virtual environment..."
  python3 -m venv $VENV_DIR
fi

echo "💡 Activating virtual environment..."
source $VENV_DIR/bin/activate

# === [2] Conan Installation ===
if ! command -v conan &> /dev/null; then
  echo "📦 Installing Conan inside venv..."
  pip install --upgrade pip
  pip install conan
fi

# === [3] Conan Profile Detection ===
echo "🛠️ Detecting Conan profile..."
conan profile detect --force

# === [4] Clean Build if Requested ===
if [ "$DO_CLEAN" = true ]; then
  echo "🧹 Cleaning build directory..."
  rm -rf $BUILD_DIR
fi

# === [5] Create Build Dir ===
mkdir -p $BUILD_DIR
cd $BUILD_DIR

# === [6] Install Conan Deps ===
echo "📦 Installing dependencies with Conan..."
conan install .. --build=missing

# === [7] Run CMake ===
echo "⚙️ Running cmake..."
cmake .. -DCMAKE_TOOLCHAIN_FILE=Release/generators/conan_toolchain.cmake

# === [8] Build ===
echo "🔨  Building..."
cmake --build .

# === [9] Optionally Run Tests ===
if [ "$DO_TEST" = true ]; then
  echo "🧪 Running tests..."
  ctest --output-on-failure
elif [ "$BUILD_ONLY" = true ]; then
  echo "✅  Build completed. Tests skipped (--build-only)."
else
  echo "⚠️  Build completed. Tests not run. Use --test to run tests."
fi

# === [10] Optionally Run Demo ===
if [ "$RUN_DEMO" = true ]; then
  echo "🚀 Running memory demo..."
  ./bin/memory_demo
fi
