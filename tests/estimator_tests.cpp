#include "SensorHealth.hpp"
#include "StateEstimator.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    SensorReading good{0.0, 1.0, 2.0, 90.0, 3.0, 1.2, 80.0};
    assert(SensorHealth::gpsValid(good));
    assert(SensorHealth::imuValid(good));
    assert(SensorHealth::rangefinderValid(good));
    assert(SensorHealth::batteryValid(good));
    assert(SensorHealth::confidenceScore(good) > 0.9);

    SensorReading low_battery = good;
    low_battery.battery_percent = 10.0;
    assert(SensorHealth::confidenceScore(low_battery) < 1.0);
    assert(SensorHealth::healthSummary(low_battery).find("LOW_BATTERY") != std::string::npos);

    StateEstimator estimator;
    RobotState s1 = estimator.update(good);
    SensorReading next{1.0, 2.0, 4.0, 100.0, 2.5, 2.0, 79.0};
    RobotState s2 = estimator.update(next);
    assert(s2.x_m > s1.x_m);
    assert(s2.y_m > s1.y_m);
    assert(s2.heading_deg > s1.heading_deg);

    std::cout << "All estimator tests passed.\n";
    return 0;
}
