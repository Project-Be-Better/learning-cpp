# ── Stage 1: build & test ─────────────────────────────────────────────
FROM conanio/gcc11:latest AS builder

USER root
RUN apt-get update && apt-get install -y cmake ninja-build \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

ARG BUILD_TYPE=Release

COPY . .

RUN conan install . \
      -s build_type=${BUILD_TYPE} \
      -s compiler.cppstd=20 \
      -s compiler.libcxx=libstdc++11 \
      --output-folder=build \
      --build=missing \
    && cmake -S . -B build -G Ninja \
         -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
         -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
         -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
         -DBUILD_TESTING=ON \
    && cmake --build build \
    && ctest --test-dir build --output-on-failure -C ${BUILD_TYPE}


# ── Stage 2: runtime ───────────────────────────────────────────────────
FROM debian:stable-slim AS runtime

WORKDIR /app
COPY --from=builder /app/build/project_teletrack_sim /app/project_teletrack_sim

ENTRYPOINT ["./project_teletrack_sim"]
