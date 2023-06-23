#!/bin/bash

# Go to repository root
cd "$(dirname "$0")/.." || exit 2

make -C build -j$(nproc) config=debug_x86 clean
make -C build -j$(nproc) config=release_x86 clean

