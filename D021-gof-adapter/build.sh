#!/usr/bin/env bash
set -euo pipefail

# On Git-Bash / MSYS, disable automatic path conversion for docker run
export MSYS_NO_PATHCONV=1

show_help() {
  cat <<EOF
Usage: ./build.sh [options]

Script to build the TeleTrack Simulator via Docker, extract compile_commands.json,
run tests, and optionally run the simulator.

Options:
  -h, --help        Display this help message
  -c, --clean       Force a fresh rebuild (no Docker cache)
  -t, --test        Run tests inside container (default)
  --skip-test       Skip tests
  -d, --debug       Build in Debug mode (default Release)
  -r, --run         After building, run the simulator in a container
EOF
}

# Defaults
BUILD_TYPE="Release"
RUN_TESTS="true"
NO_CACHE=""
RUN_APP=false

# Parse flags
while [[ $# -gt 0 ]]; do
  case $1 in
    -h|--help)    show_help; exit 0 ;;
    -c|--clean)   NO_CACHE="--no-cache"; shift ;;
    -t|--test)    RUN_TESTS="true"; shift ;;
    --skip-test)  RUN_TESTS="false"; shift ;;
    -d|--debug)   BUILD_TYPE="Debug"; shift ;;
    -r|--run)     RUN_APP=true; shift ;;
    *) echo "Unknown option: $1"; show_help; exit 1 ;;
  esac
done

BUILDER_IMAGE=telematics-app-builder:latest
RUNTIME_IMAGE=telematics-app:latest

echo "🔧 Building builder stage (${BUILDER_IMAGE})"
docker build $NO_CACHE \
  --target builder \
  --build-arg BUILD_TYPE=${BUILD_TYPE} \
  -t ${BUILDER_IMAGE} .

echo "📂 Extracting compile_commands.json to ./build/"
mkdir -p build
CID=$(docker create ${BUILDER_IMAGE})
docker cp ${CID}:/app/build/compile_commands.json build/compile_commands.json
docker rm ${CID}

if [ "${RUN_TESTS}" = "true" ]; then
  echo "🧪 Running tests in builder container…"
  docker run --rm \
    --workdir=/app/build \
    ${BUILDER_IMAGE} \
    ctest --output-on-failure -C ${BUILD_TYPE}
fi

echo "🔧 Building runtime stage (${RUNTIME_IMAGE})"
docker build $NO_CACHE \
  --target runtime \
  -t ${RUNTIME_IMAGE} .

if [ "${RUN_APP}" = true ]; then
  echo "▶️  Running simulator in container..."
  docker run --rm -it ${RUNTIME_IMAGE}
fi
