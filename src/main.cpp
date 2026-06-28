#include "SensorHealth.hpp"
#include "StateEstimator.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

SensorReading parseLine(const std::string& line) {
    std::stringstream ss(line);
    std::string item;
    std::vector<double> values;
    while (std::getline(ss, item, ',')) {
        values.push_back(std::stod(item));
    }
    if (values.size() != 7) {
        throw std::runtime_error("Expected 7 CSV columns");
    }
    return SensorReading{values[0], values[1], values[2], values[3], values[4], values[5], values[6]};
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: robot_state_estimator data/sample_sensor_data.csv\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Could not open input file: " << argv[1] << "\n";
        return 1;
    }

    StateEstimator estimator;
    std::string line;
    bool first = true;

    std::cout << "time,x,y,heading,velocity,confidence,health\n";
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (first) { first = false; continue; } // header

        try {
            SensorReading reading = parseLine(line);
            RobotState state = estimator.update(reading);
            std::cout << reading.timestamp_s << ","
                      << state.x_m << ","
                      << state.y_m << ","
                      << state.heading_deg << ","
                      << state.velocity_mps << ","
                      << state.confidence << ","
                      << SensorHealth::healthSummary(reading) << "\n";
        } catch (const std::exception& ex) {
            std::cerr << "Skipping bad line: " << ex.what() << "\n";
        }
    }

    return 0;
}
