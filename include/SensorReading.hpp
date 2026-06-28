#pragma once

struct SensorReading {
    double timestamp_s{};
    double gps_x_m{};
    double gps_y_m{};
    double imu_heading_deg{};
    double rangefinder_m{};
    double velocity_mps{};
    double battery_percent{};
};

struct RobotState {
    double x_m{};
    double y_m{};
    double heading_deg{};
    double velocity_mps{};
    double confidence{};
};
