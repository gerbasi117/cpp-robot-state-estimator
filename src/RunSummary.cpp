#include "RunSummary.hpp"
#include "SensorHealth.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

RunSummaryData RunSummary::analyze(const std::vector<EstimatedFrame>& frames) {
    RunSummaryData summary{};
    summary.samples = frames.size();
    summary.minimum_confidence = frames.empty() ? 0.0 : 1.0;

    if (frames.empty()) {
        summary.final_status = "NO_DATA";
        return summary;
    }

    const double start_time = frames.front().reading.timestamp_s;
    const double end_time = frames.back().reading.timestamp_s;
    summary.duration_s = std::max(0.0, end_time - start_time);

    double confidence_sum = 0.0;
    for (const auto& frame : frames) {
        confidence_sum += frame.state.confidence;
        summary.minimum_confidence = std::min(summary.minimum_confidence, frame.state.confidence);

        if (!SensorHealth::gpsValid(frame.reading)) summary.gps_invalid_samples++;
        if (!SensorHealth::imuValid(frame.reading)) summary.imu_invalid_samples++;
        if (!SensorHealth::rangefinderValid(frame.reading)) summary.rangefinder_invalid_samples++;
        if (SensorHealth::rangefinderTooClose(frame.reading)) summary.rangefinder_close_samples++;
        if (!SensorHealth::velocityValid(frame.reading)) summary.velocity_invalid_samples++;
        if (SensorHealth::batteryValid(frame.reading) && frame.reading.battery_percent < 20.0) summary.low_battery_samples++;
    }

    summary.average_confidence = confidence_sum / static_cast<double>(frames.size());
    const RobotState& final_state = frames.back().state;
    summary.final_x_m = final_state.x_m;
    summary.final_y_m = final_state.y_m;
    summary.final_heading_deg = final_state.heading_deg;

    const bool unsafe = summary.gps_invalid_samples > 0 ||
                        summary.imu_invalid_samples > 0 ||
                        summary.rangefinder_invalid_samples > 0 ||
                        summary.velocity_invalid_samples > 0 ||
                        summary.low_battery_samples > 0 ||
                        summary.minimum_confidence < 0.55;
    const bool caution = summary.rangefinder_close_samples > 0 || summary.minimum_confidence < 0.80;

    if (unsafe) summary.final_status = "UNSAFE";
    else if (caution) summary.final_status = "CAUTION";
    else summary.final_status = "NOMINAL";

    return summary;
}

std::string RunSummary::toMarkdown(const RunSummaryData& summary, const std::string& scenario_name) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "# Robot State Estimator Run Summary\n\n";
    oss << "**Scenario:** `" << scenario_name << "`\n";
    oss << "**Final status:** **" << summary.final_status << "**\n\n";
    oss << "## Summary\n\n";
    oss << "- Samples: " << summary.samples << "\n";
    oss << "- Duration: " << summary.duration_s << " seconds\n";
    oss << "- Average confidence: " << summary.average_confidence << "\n";
    oss << "- Minimum confidence: " << summary.minimum_confidence << "\n";
    oss << "- Final position: (" << summary.final_x_m << ", " << summary.final_y_m << ") m\n";
    oss << "- Final heading: " << summary.final_heading_deg << " deg\n\n";
    oss << "## Sensor Issues\n\n";
    oss << "- GPS invalid/dropout samples: " << summary.gps_invalid_samples << "\n";
    oss << "- IMU invalid samples: " << summary.imu_invalid_samples << "\n";
    oss << "- Rangefinder invalid samples: " << summary.rangefinder_invalid_samples << "\n";
    oss << "- Rangefinder too-close samples: " << summary.rangefinder_close_samples << "\n";
    oss << "- Velocity invalid samples: " << summary.velocity_invalid_samples << "\n";
    oss << "- Low-battery samples: " << summary.low_battery_samples << "\n\n";
    oss << "## Recommended Actions\n\n";
    if (summary.gps_invalid_samples > 0) oss << "- Review GPS receiver placement, antenna visibility, cabling, and sensor timestamping.\n";
    if (summary.imu_invalid_samples > 0) oss << "- Check IMU calibration and heading normalization.\n";
    if (summary.rangefinder_invalid_samples > 0 || summary.rangefinder_close_samples > 0) oss << "- Inspect rangefinder placement and obstacle-proximity thresholds.\n";
    if (summary.velocity_invalid_samples > 0) oss << "- Validate velocity source and input filtering.\n";
    if (summary.low_battery_samples > 0) oss << "- Review battery thresholds and power-system behavior under load.\n";
    if (summary.final_status == "NOMINAL") oss << "- No immediate corrective actions from this simulated run.\n";
    oss << "\n## Portfolio Note\n\n";
    oss << "This project demonstrates C++ robotics-style sensor validation, simple filtering, confidence scoring, and run-summary reporting using simulated GPS, IMU, rangefinder, velocity, and battery data.\n";
    return oss.str();
}

std::string RunSummary::toJson(const RunSummaryData& summary, const std::string& scenario_name) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "{\n";
    oss << "  \"scenario\": \"" << scenario_name << "\",\n";
    oss << "  \"final_status\": \"" << summary.final_status << "\",\n";
    oss << "  \"samples\": " << summary.samples << ",\n";
    oss << "  \"duration_s\": " << summary.duration_s << ",\n";
    oss << "  \"average_confidence\": " << summary.average_confidence << ",\n";
    oss << "  \"minimum_confidence\": " << summary.minimum_confidence << ",\n";
    oss << "  \"final_x_m\": " << summary.final_x_m << ",\n";
    oss << "  \"final_y_m\": " << summary.final_y_m << ",\n";
    oss << "  \"final_heading_deg\": " << summary.final_heading_deg << ",\n";
    oss << "  \"gps_invalid_samples\": " << summary.gps_invalid_samples << ",\n";
    oss << "  \"imu_invalid_samples\": " << summary.imu_invalid_samples << ",\n";
    oss << "  \"rangefinder_invalid_samples\": " << summary.rangefinder_invalid_samples << ",\n";
    oss << "  \"rangefinder_close_samples\": " << summary.rangefinder_close_samples << ",\n";
    oss << "  \"velocity_invalid_samples\": " << summary.velocity_invalid_samples << ",\n";
    oss << "  \"low_battery_samples\": " << summary.low_battery_samples << "\n";
    oss << "}\n";
    return oss.str();
}

void RunSummary::writeTextFile(const std::string& path, const std::string& text) {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("Could not write file: " + path);
    out << text;
}
