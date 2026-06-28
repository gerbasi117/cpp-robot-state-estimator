# Robot State Estimator Run Summary

**Scenario:** `low_battery_fault`
**Final status:** **UNSAFE**

## Summary

- Samples: 7
- Duration: 6.000 seconds
- Average confidence: 0.871
- Minimum confidence: 0.800
- Final position: (3.504, 0.775) m
- Final heading: 94.283 deg

## Sensor Issues

- GPS invalid/dropout samples: 0
- IMU invalid samples: 0
- Rangefinder invalid samples: 0
- Rangefinder too-close samples: 0
- Velocity invalid samples: 0
- Low-battery samples: 3

## Recommended Actions

- Review battery thresholds and power-system behavior under load.

## Portfolio Note

This project demonstrates C++ robotics-style sensor validation, simple filtering, confidence scoring, and run-summary reporting using simulated GPS, IMU, rangefinder, velocity, and battery data.
