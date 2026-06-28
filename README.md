# C++ Robot State Estimator

A small C++/CMake robotics software project that processes simulated GPS, IMU, rangefinder, and velocity data to estimate robot state and sensor health.

## Purpose

This project demonstrates C++ structure for robotics-adjacent code: classes, headers, CMake, CSV parsing, simple filtering, confidence scoring, and testable state-estimation logic.

## Build

```bash
cmake -S . -B build
cmake --build build
./build/robot_state_estimator data/sample_sensor_data.csv
./build/estimator_tests
```

## Resume bullets

- Developed a C++ robot state-estimation demo using simulated GPS, IMU, rangefinder, and velocity data.
- Implemented sensor validation, simple filtering, sensor-health checks, and confidence scoring for noisy robotics inputs.
- Structured the project with CMake, modular classes, headers, CSV input, and repeatable test cases.
