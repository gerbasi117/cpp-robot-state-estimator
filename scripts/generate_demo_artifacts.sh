#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/.."
mkdir -p demo reports

if command -v cmake >/dev/null 2>&1; then
  cmake -S . -B build >/tmp/cpp_estimator_cmake_config.log
  cmake --build build -j"$(nproc)" >/tmp/cpp_estimator_cmake_build.log
  APP="./build/robot_state_estimator"
  TEST="./build/estimator_tests"
else
  make >/tmp/cpp_estimator_make_build.log
  APP="./robot_state_estimator"
  TEST="./estimator_tests"
fi

$TEST > demo/unit_test_output.txt

run_case() {
  local name="$1"
  local input="data/${name}.csv"
  echo "Generating C++ estimator demo: $name"
  $APP "$input" \
    --output "demo/${name}_state_output.csv" \
    --summary "reports/${name}_summary.md" \
    --json "reports/${name}_summary.json" \
    > "demo/${name}_terminal_output.txt"
}

run_case sample_sensor_data
run_case gps_dropout
run_case noisy_imu
run_case low_battery_fault

cat > demo/demo_commands.md <<'CMDS'
# C++ State Estimator Demo Commands

Build with CMake:

```bash
cmake -S . -B build
cmake --build build -j"$(nproc)"
./build/estimator_tests
```

Run the default scenario:

```bash
./build/robot_state_estimator data/sample_sensor_data.csv --output demo/sample_output.csv --summary reports/sample_summary.md --json reports/sample_summary.json
```

Run GPS dropout:

```bash
./build/robot_state_estimator data/gps_dropout.csv --output demo/gps_dropout_output.csv --summary reports/gps_dropout_summary.md --json reports/gps_dropout_summary.json
```

Run without CMake using Make:

```bash
make clean
make
make test
make demo
```
CMDS
