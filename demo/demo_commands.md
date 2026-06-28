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
