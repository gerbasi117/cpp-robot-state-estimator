# Robot State Estimator Run Summary

**Scenario:** `gps_dropout`
**Final status:** **UNSAFE**

## Summary

- Samples: 11
- Duration: 10.000 seconds
- Average confidence: 0.895
- Minimum confidence: 0.650
- Final position: (5.497, 2.042) m
- Final heading: 98.168 deg

## Sensor Issues

- GPS invalid/dropout samples: 3
- IMU invalid samples: 0
- Rangefinder invalid samples: 0
- Rangefinder too-close samples: 1
- Velocity invalid samples: 0
- Low-battery samples: 0

## Recommended Actions

- Review GPS receiver placement, antenna visibility, cabling, and sensor timestamping.
- Inspect rangefinder placement and obstacle-proximity thresholds.

## Portfolio Note

This project demonstrates C++ robotics-style sensor validation, simple filtering, confidence scoring, and run-summary reporting using simulated GPS, IMU, rangefinder, velocity, and battery data.
