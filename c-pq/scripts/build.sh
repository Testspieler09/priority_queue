#!/usr/bin/env bash
set -euo pipefail

rm -rf build
cmake -G "Ninja" -B build .
cmake --build build
