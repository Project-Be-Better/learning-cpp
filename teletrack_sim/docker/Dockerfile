FROM ubuntu:22.04

RUN apt update && apt install -y \
    build-essential \
    cmake \
    git \
    python3-pip

RUN pip3 install conan

WORKDIR /app
