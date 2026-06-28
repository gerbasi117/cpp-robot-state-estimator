#pragma once

#include <string>
#include <vector>
#include "SensorReading.hpp"

struct RunSummaryData {
    std::size_t samples{};
    double duration_s{};
    double average_confidence{};
    double minimum_confidence{};
    double final_x_m{};
    double final_y_m{};
    double final_heading_deg{};
    std::size_t gps_invalid_samples{};
    std::size_t imu_invalid_samples{};
    std::size_t rangefinder_invalid_samples{};
    std::size_t rangefinder_close_samples{};
    std::size_t velocity_invalid_samples{};
    std::size_t low_battery_samples{};
    std::string final_status{};
};

class RunSummary {
public:
    static RunSummaryData analyze(const std::vector<EstimatedFrame>& frames);
    static std::string toMarkdown(const RunSummaryData& summary, const std::string& scenario_name);
    static std::string toJson(const RunSummaryData& summary, const std::string& scenario_name);
    static void writeTextFile(const std::string& path, const std::string& text);
};
