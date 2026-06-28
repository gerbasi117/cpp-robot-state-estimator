# Robot State Estimator Run Summary

**Scenario:** `sample_sensor_data`
**Final status:** **CAUTION**

## Summary

- Samples: 15
- Duration: 14.000 seconds
- Average confidence: 0.993
- Minimum confidence: 0.900
- Final position: (8.043, 4.296) m
- Final heading: 102.147 deg

## Sensor Issues

- GPS invalid/dropout samples: 0
- IMU invalid samples: 0
- Rangefinder invalid samples: 0
- Rangefinder too-close samples: 1
- Velocity invalid samples: 0
- Low-battery samples: 0

## Recommended Actions

- Inspect rangefinder placement and obstacle-proximity thresholds.

## Portfolio Note

This project demonstrates C++ robotics-style sensor validation, simple filtering, confidence scoring, and run-summary reporting using simulated GPS, IMU, rangefinder, velocity, and battery data.
