#include "StateEstimator.hpp"
#include "SensorHealth.hpp"

StateEstimator::StateEstimator(double alpha) : alpha_(alpha), initialized_(false), state_{} {}

RobotState StateEstimator::update(const SensorReading& reading) {
    double confidence = SensorHealth::confidenceScore(reading);

    if (!initialized_) {
        state_.x_m = reading.gps_x_m;
        state_.y_m = reading.gps_y_m;
        state_.heading_deg = reading.imu_heading_deg;
        state_.velocity_mps = reading.velocity_mps;
        state_.confidence = confidence;
        initialized_ = true;
        return state_;
    }

    if (SensorHealth::gpsValid(reading)) {
        state_.x_m = alpha_ * reading.gps_x_m + (1.0 - alpha_) * state_.x_m;
        state_.y_m = alpha_ * reading.gps_y_m + (1.0 - alpha_) * state_.y_m;
    }

    if (SensorHealth::imuValid(reading)) {
        state_.heading_deg = alpha_ * reading.imu_heading_deg + (1.0 - alpha_) * state_.heading_deg;
    }

    state_.velocity_mps = alpha_ * reading.velocity_mps + (1.0 - alpha_) * state_.velocity_mps;
    state_.confidence = confidence;
    return state_;
}

RobotState StateEstimator::state() const {
    return state_;
}
