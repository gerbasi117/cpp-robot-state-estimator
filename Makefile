CXX ?= g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude

APP := robot_state_estimator
TEST := estimator_tests
SRCS := src/StateEstimator.cpp src/SensorHealth.cpp src/RunSummary.cpp

.PHONY: all test clean demo

all: $(APP) $(TEST)

$(APP): src/main.cpp $(SRCS) include/*.hpp
	$(CXX) $(CXXFLAGS) src/main.cpp $(SRCS) -o $(APP)

$(TEST): tests/estimator_tests.cpp $(SRCS) include/*.hpp
	$(CXX) $(CXXFLAGS) tests/estimator_tests.cpp $(SRCS) -o $(TEST)

test: all
	./$(TEST)

demo: all
	mkdir -p demo reports
	./$(APP) data/sample_sensor_data.csv --output demo/sample_output.csv --summary reports/sample_summary.md --json reports/sample_summary.json
	./$(APP) data/gps_dropout.csv --output demo/gps_dropout_output.csv --summary reports/gps_dropout_summary.md --json reports/gps_dropout_summary.json
	./$(APP) data/noisy_imu.csv --output demo/noisy_imu_output.csv --summary reports/noisy_imu_summary.md --json reports/noisy_imu_summary.json

clean:
	rm -f $(APP) $(TEST)
	rm -rf build
