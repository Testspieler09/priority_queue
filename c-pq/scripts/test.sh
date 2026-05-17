#!/usr/bin/env bash

set -euo pipefail

BIN_DIR="./build/bin"

TESTS=()
for f in "$BIN_DIR"/test_*; do
    if [ -f "$f" ] && [ -x "$f" ]; then
        TESTS+=("$(basename "$f")")
    fi
done

if [ ${#TESTS[@]} -eq 0 ]; then
    echo "[X] No test executables found in $BIN_DIR"
    exit 1
fi

echo "Running unit tests..."

for test in "${TESTS[@]}"; do
    EXEC="$BIN_DIR/$test"

    echo "Running $test..."
    "$EXEC"
    echo "$test passed"
    echo "---------------------------"
done

echo "All tests passed!"
