# Interview Walkthrough: C++ Robot State Estimator

## 30-second explanation

I built a C++17 robot state-estimation project that reads simulated sensor logs, validates GPS/IMU/rangefinder/velocity/battery inputs, produces a filtered robot state estimate, and generates run-summary reports. The focus was not advanced math; it was clean robotics software structure, fault handling, and testable C++.

## Why I built it

Many robotics roles ask for C++ and sensor-driven systems. I wanted a focused project that demonstrates how I think about sensor health, safe handling of bad inputs, and repeatable test scenarios.

## Key design choices

- Simple exponential smoothing instead of overclaiming a full Kalman filter.
- Sensor-health validation before using readings.
- Confidence score to summarize reliability of each frame.
- CSV input/output so scenarios are easy to inspect and replay.
- Markdown/JSON reports for debugging and portfolio review.

## What I would improve next

- Add a Kalman filter or complementary filter.
- Add Eigen for vector/matrix math.
- Add GoogleTest.
- Add ROS2 message input/output.
- Feed this estimator from the ROS2 perception/safety demo.
