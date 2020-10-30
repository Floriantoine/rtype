#!/bin/bash

WORKDIR="$(dirname "$(readlink -f "$0")")"
CONAN_PROFILE="$WORKDIR/conanprofile"

rm -rf build && \
mkdir build && \
cd build && \
conan install "$WORKDIR" --build=missing --profile="$CONAN_PROFILE" && \
cmake .. -G "Unix Makefiles" && \
cmake --build .
