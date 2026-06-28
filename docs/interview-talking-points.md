# Interview Talking Points

## What this project demonstrates

- C++17 project organization
- Header/source separation
- Sensor input modeling
- Basic robot-state estimation
- Sensor-health checks
- Confidence scoring
- Repeatable sample data
- CMake support plus Makefile fallback

## Honest scope

This is not a full production SLAM or localization stack. It is a focused C++ robotics software demo showing how simulated GPS, IMU, rangefinder, and velocity inputs can be parsed, validated, filtered, and converted into a simple robot-state estimate.

## Future improvements

- Add Kalman filter or complementary filter
- Add ROS2 topic input/output
- Add IMU drift simulation
- Add GPS dropout scenarios
- Add plotting or CSV output
- Integrate with UAV telemetry dashboard
