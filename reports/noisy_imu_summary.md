# Robot State Estimator Run Summary

**Scenario:** `noisy_imu`
**Final status:** **UNSAFE**

## Summary

- Samples: 11
- Duration: 10.000 seconds
- Average confidence: 0.945
- Minimum confidence: 0.750
- Final position: (5.913, 2.207) m
- Final heading: 116.516 deg

## Sensor Issues

- GPS invalid/dropout samples: 0
- IMU invalid samples: 2
- Rangefinder invalid samples: 0
- Rangefinder too-close samples: 1
- Velocity invalid samples: 0
- Low-battery samples: 0

## Recommended Actions

- Check IMU calibration and heading normalization.
- Inspect rangefinder placement and obstacle-proximity thresholds.

## Portfolio Note

This project demonstrates C++ robotics-style sensor validation, simple filtering, confidence scoring, and run-summary reporting using simulated GPS, IMU, rangefinder, velocity, and battery data.
