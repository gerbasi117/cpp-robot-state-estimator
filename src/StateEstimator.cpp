#include "StateEstimator.hpp"
#include "SensorHealth.hpp"

#include <cmath>

StateEstimator::StateEstimator(double alpha) : alpha_(alpha), initialized_(false), state_{} {}

double StateEstimator::normalizeHeading(double heading_deg) {
    while (heading_deg < 0.0) heading_deg += 360.0;
    while (heading_deg >= 360.0) heading_deg -= 360.0;
    return heading_deg;
}

RobotState StateEstimator::update(const SensorReading& reading) {
    const double confidence = SensorHealth::confidenceScore(reading);

    if (!initialized_) {
        state_.x_m = SensorHealth::gpsValid(reading) ? reading.gps_x_m : 0.0;
        state_.y_m = SensorHealth::gpsValid(reading) ? reading.gps_y_m : 0.0;
        state_.heading_deg = SensorHealth::imuValid(reading) ? normalizeHeading(reading.imu_heading_deg) : 0.0;
        state_.velocity_mps = SensorHealth::velocityValid(reading) ? reading.velocity_mps : 0.0;
        state_.confidence = confidence;
        initialized_ = true;
        return state_;
    }

    if (SensorHealth::gpsValid(reading)) {
        state_.x_m = alpha_ * reading.gps_x_m + (1.0 - alpha_) * state_.x_m;
        state_.y_m = alpha_ * reading.gps_y_m + (1.0 - alpha_) * state_.y_m;
    }

    if (SensorHealth::imuValid(reading)) {
        state_.heading_deg = normalizeHeading(alpha_ * reading.imu_heading_deg + (1.0 - alpha_) * state_.heading_deg);
    }

    if (SensorHealth::velocityValid(reading)) {
        state_.velocity_mps = alpha_ * reading.velocity_mps + (1.0 - alpha_) * state_.velocity_mps;
    }

    state_.confidence = confidence;
    return state_;
}

RobotState StateEstimator::state() const {
    return state_;
}
