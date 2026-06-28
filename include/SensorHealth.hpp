#pragma once

#include <string>
#include "SensorReading.hpp"

class SensorHealth {
public:
    static bool gpsValid(const SensorReading& reading);
    static bool imuValid(const SensorReading& reading);
    static bool rangefinderValid(const SensorReading& reading);
    static bool batteryValid(const SensorReading& reading);
    static double confidenceScore(const SensorReading& reading);
    static std::string healthSummary(const SensorReading& reading);
};
