#!/usr/bin/env sh
set -eu
task_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
cmake -S "$task_root" -B "$task_root/build" -DCMAKE_BUILD_TYPE=Debug
cmake --build "$task_root/build"
ctest --test-dir "$task_root/build" --output-on-failure
