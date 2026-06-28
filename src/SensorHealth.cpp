#include "SensorHealth.hpp"

#include <algorithm>
#include <cmath>
#include <sstream>

bool SensorHealth::gpsValid(const SensorReading& reading) {
    return std::isfinite(reading.gps_x_m) && std::isfinite(reading.gps_y_m);
}

bool SensorHealth::imuValid(const SensorReading& reading) {
    return std::isfinite(reading.imu_heading_deg) && reading.imu_heading_deg >= 0.0 && reading.imu_heading_deg < 360.0;
}

bool SensorHealth::rangefinderValid(const SensorReading& reading) {
    return std::isfinite(reading.rangefinder_m) && reading.rangefinder_m >= 0.0 && reading.rangefinder_m < 50.0;
}

bool SensorHealth::rangefinderTooClose(const SensorReading& reading) {
    return rangefinderValid(reading) && reading.rangefinder_m < 0.75;
}

bool SensorHealth::velocityValid(const SensorReading& reading) {
    return std::isfinite(reading.velocity_mps) && reading.velocity_mps >= 0.0 && reading.velocity_mps < 100.0;
}

bool SensorHealth::batteryValid(const SensorReading& reading) {
    return std::isfinite(reading.battery_percent) && reading.battery_percent >= 0.0 && reading.battery_percent <= 100.0;
}

double SensorHealth::confidenceScore(const SensorReading& reading) {
    double score = 1.0;
    if (!gpsValid(reading)) score -= 0.35;
    if (!imuValid(reading)) score -= 0.25;
    if (!rangefinderValid(reading)) score -= 0.20;
    else if (rangefinderTooClose(reading)) score -= 0.10;
    if (!velocityValid(reading)) score -= 0.15;
    if (!batteryValid(reading)) score -= 0.20;
    else if (reading.battery_percent < 20.0) score -= 0.20;
    else if (reading.battery_percent < 35.0) score -= 0.10;
    return std::clamp(score, 0.0, 1.0);
}

std::vector<std::string> SensorHealth::warnings(const SensorReading& reading) {
    std::vector<std::string> warnings;
    if (!gpsValid(reading)) warnings.push_back("GPS_DROPOUT");
    if (!imuValid(reading)) warnings.push_back("IMU_INVALID");
    if (!rangefinderValid(reading)) warnings.push_back("RANGEFINDER_INVALID");
    else if (rangefinderTooClose(reading)) warnings.push_back("RANGEFINDER_TOO_CLOSE");
    if (!velocityValid(reading)) warnings.push_back("VELOCITY_INVALID");
    if (!batteryValid(reading)) warnings.push_back("BATTERY_INVALID");
    else if (reading.battery_percent < 20.0) warnings.push_back("LOW_BATTERY");
    return warnings;
}

std::string SensorHealth::healthSummary(const SensorReading& reading) {
    const auto warning_list = warnings(reading);
    if (warning_list.empty()) return "OK";

    std::ostringstream oss;
    for (std::size_t i = 0; i < warning_list.size(); ++i) {
        if (i > 0) oss << ";";
        oss << warning_list[i];
    }
    return oss.str();
}
