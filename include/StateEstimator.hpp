#pragma once

#include "SensorReading.hpp"

class StateEstimator {
public:
    explicit StateEstimator(double alpha = 0.35);
    RobotState update(const SensorReading& reading);
    RobotState state() const;

private:
    double alpha_;
    bool initialized_;
    RobotState state_;
};
