CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude

SRC := src/StateEstimator.cpp src/SensorHealth.cpp

all: robot_state_estimator estimator_tests

robot_state_estimator: src/main.cpp $(SRC)
	$(CXX) $(CXXFLAGS) src/main.cpp $(SRC) -o robot_state_estimator

estimator_tests: tests/estimator_tests.cpp $(SRC)
	$(CXX) $(CXXFLAGS) tests/estimator_tests.cpp $(SRC) -o estimator_tests

run: robot_state_estimator
	./robot_state_estimator data/sample_sensor_data.csv

test: estimator_tests
	./estimator_tests

clean:
	rm -f robot_state_estimator estimator_tests
	rm -rf build
