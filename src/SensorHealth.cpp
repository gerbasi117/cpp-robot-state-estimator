#include "SensorHealth.hpp"

#include <cmath>
#include <sstream>
#include <vector>

bool SensorHealth::gpsValid(const SensorReading& reading) {
    return std::isfinite(reading.gps_x_m) && std::isfinite(reading.gps_y_m);
}

bool SensorHealth::imuValid(const SensorReading& reading) {
    return std::isfinite(reading.imu_heading_deg) && reading.imu_heading_deg >= 0.0 && reading.imu_heading_deg < 360.0;
}

bool SensorHealth::rangefinderValid(const SensorReading& reading) {
    return std::isfinite(reading.rangefinder_m) && reading.rangefinder_m >= 0.0 && reading.rangefinder_m < 50.0;
}

bool SensorHealth::batteryValid(const SensorReading& reading) {
    return std::isfinite(reading.battery_percent) && reading.battery_percent >= 0.0 && reading.battery_percent <= 100.0;
}

double SensorHealth::confidenceScore(const SensorReading& reading) {
    double score = 1.0;
    if (!gpsValid(reading)) score -= 0.35;
    if (!imuValid(reading)) score -= 0.25;
    if (!rangefinderValid(reading)) score -= 0.20;
    if (!batteryValid(reading) || reading.battery_percent < 20.0) score -= 0.20;
    if (score < 0.0) score = 0.0;
    return score;
}

std::string SensorHealth::healthSummary(const SensorReading& reading) {
    std::vector<std::string> warnings;
    if (!gpsValid(reading)) warnings.push_back("GPS_INVALID");
    if (!imuValid(reading)) warnings.push_back("IMU_INVALID");
    if (!rangefinderValid(reading)) warnings.push_back("RANGEFINDER_INVALID");
    if (!batteryValid(reading)) warnings.push_back("BATTERY_INVALID");
    else if (reading.battery_percent < 20.0) warnings.push_back("LOW_BATTERY");

    if (warnings.empty()) return "OK";

    std::ostringstream oss;
    for (std::size_t i = 0; i < warnings.size(); ++i) {
        if (i > 0) oss << ",";
        oss << warnings[i];
    }
    return oss.str();
}
