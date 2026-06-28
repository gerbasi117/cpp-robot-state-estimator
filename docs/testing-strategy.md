# Testing Strategy

## Current tests

`tests/estimator_tests.cpp` validates:

- Normal sensor readings.
- Low-battery confidence reduction.
- GPS dropout detection.
- Rangefinder too-close detection.
- State estimator update behavior.
- State preservation during invalid GPS input.
- Run-summary classification.

## Scenario tests

The `data/` folder includes:

- `sample_sensor_data.csv`
- `gps_dropout.csv`
- `noisy_imu.csv`
- `low_battery_fault.csv`

Generate demo outputs with:

```bash
bash scripts/generate_demo_artifacts.sh
```
