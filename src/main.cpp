#include "RunSummary.hpp"
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

std::string basenameNoExtension(const std::string& path) {
    const auto slash = path.find_last_of("/");
    std::string name = (slash == std::string::npos) ? path : path.substr(slash + 1);
    const auto dot = name.find_last_of('.');
    if (dot != std::string::npos) name = name.substr(0, dot);
    return name;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: robot_state_estimator <input.csv> [--output output.csv] [--summary summary.md] [--json summary.json]\n";
        return 1;
    }

    const std::string input_path = argv[1];
    std::string output_path;
    std::string summary_path;
    std::string json_path;

    for (int i = 2; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--output" && i + 1 < argc) output_path = argv[++i];
        else if (arg == "--summary" && i + 1 < argc) summary_path = argv[++i];
        else if (arg == "--json" && i + 1 < argc) json_path = argv[++i];
        else {
            std::cerr << "Unknown or incomplete argument: " << arg << "\n";
            return 1;
        }
    }

    std::ifstream file(input_path);
    if (!file) {
        std::cerr << "Could not open input file: " << input_path << "\n";
        return 1;
    }

    std::ofstream output_file;
    if (!output_path.empty()) {
        output_file.open(output_path);
        if (!output_file) {
            std::cerr << "Could not open output file: " << output_path << "\n";
            return 1;
        }
    }

    auto write_row = [&](const std::string& row) {
        std::cout << row << "\n";
        if (output_file) output_file << row << "\n";
    };

    StateEstimator estimator;
    std::vector<EstimatedFrame> frames;
    std::string line;
    bool first = true;

    write_row("time,x,y,heading,velocity,confidence,health");
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (first) { first = false; continue; }

        try {
            SensorReading reading = parseLine(line);
            RobotState state = estimator.update(reading);
            const std::string health = SensorHealth::healthSummary(reading);
            frames.push_back(EstimatedFrame{reading, state, health});

            std::ostringstream row;
            row << reading.timestamp_s << ","
                << state.x_m << ","
                << state.y_m << ","
                << state.heading_deg << ","
                << state.velocity_mps << ","
                << state.confidence << ","
                << health;
            write_row(row.str());
        } catch (const std::exception& ex) {
            std::cerr << "Skipping bad line: " << ex.what() << "\n";
        }
    }

    const std::string scenario = basenameNoExtension(input_path);
    const RunSummaryData summary = RunSummary::analyze(frames);

    if (!summary_path.empty()) {
        RunSummary::writeTextFile(summary_path, RunSummary::toMarkdown(summary, scenario));
        std::cerr << "Markdown summary written: " << summary_path << "\n";
    }
    if (!json_path.empty()) {
        RunSummary::writeTextFile(json_path, RunSummary::toJson(summary, scenario));
        std::cerr << "JSON summary written: " << json_path << "\n";
    }

    return 0;
}
