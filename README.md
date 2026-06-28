# C++ Robot State Estimator

A C++17 robotics software project that processes simulated GPS, IMU, rangefinder, velocity, and battery data to estimate robot state, validate sensor health, score confidence, and generate run-summary reports.

This project is designed as portfolio proof for robotics software, UAV/robotics systems integration, and autonomous systems test roles.

## What it demonstrates

- Modern C++ project structure with headers, source files, CMake, and Makefile fallback.
- Sensor validation for GPS, IMU, rangefinder, velocity, and battery data.
- Simple filtered state estimation for position, heading, and velocity.
- Confidence scoring when sensors become unreliable.
- Repeatable test scenarios for GPS dropout, noisy IMU, rangefinder proximity, and low battery.
- CSV output plus Markdown/JSON run summaries for debugging and review.

## Build and run

```bash
cmake -S . -B build
cmake --build build -j"$(nproc)"
./build/estimator_tests
./build/robot_state_estimator data/sample_sensor_data.csv
```

Generate demo artifacts:

```bash
bash scripts/generate_demo_artifacts.sh
```

Makefile fallback:

```bash
make clean
make
make test
make demo
```

## Example output

```text
time,x,y,heading,velocity,confidence,health
0,0,0,90,0,1,OK
1,0.28,0.035,90.35,0.28,1,OK
2,0.777,0.12775,90.9275,0.567,1,OK
```

When GPS drops out, the estimator preserves the last valid position estimate instead of allowing NaN values to corrupt the robot state.

## Scenarios

| Scenario | Purpose |
|---|---|
| `sample_sensor_data.csv` | Normal-ish movement with one close rangefinder event. |
| `gps_dropout.csv` | Simulated GPS loss/dropout while the estimator continues using last valid position. |
| `noisy_imu.csv` | Invalid/noisy heading values to test IMU validation. |
| `low_battery_fault.csv` | Battery values dropping below safe thresholds. |

## Resume bullets

- Developed a C++17 robot state-estimation demo using simulated GPS, IMU, rangefinder, velocity, and battery data, with sensor validation, simple filtering, confidence scoring, and run-summary reporting.
- Implemented test scenarios for GPS dropout, noisy IMU, low battery, and rangefinder proximity faults, preserving safe state estimates when sensor inputs become invalid.
- Structured the project with CMake, Makefile fallback, modular classes, unit-style tests, CSV input/output, and Markdown/JSON diagnostic reports.
