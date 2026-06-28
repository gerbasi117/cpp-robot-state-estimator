#include "RunSummary.hpp"
#include "SensorHealth.hpp"
#include "StateEstimator.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    SensorReading good{0.0, 1.0, 2.0, 90.0, 3.0, 1.2, 80.0};
    assert(SensorHealth::gpsValid(good));
    assert(SensorHealth::imuValid(good));
    assert(SensorHealth::rangefinderValid(good));
    assert(SensorHealth::velocityValid(good));
    assert(SensorHealth::batteryValid(good));
    assert(SensorHealth::confidenceScore(good) > 0.9);
    assert(SensorHealth::healthSummary(good) == "OK");

    SensorReading low_battery = good;
    low_battery.battery_percent = 10.0;
    assert(SensorHealth::confidenceScore(low_battery) < 1.0);
    assert(SensorHealth::healthSummary(low_battery).find("LOW_BATTERY") != std::string::npos);

    SensorReading gps_dropout = good;
    gps_dropout.gps_x_m = NAN;
    gps_dropout.gps_y_m = NAN;
    assert(!SensorHealth::gpsValid(gps_dropout));
    assert(SensorHealth::healthSummary(gps_dropout).find("GPS_DROPOUT") != std::string::npos);

    SensorReading too_close = good;
    too_close.rangefinder_m = 0.25;
    assert(SensorHealth::rangefinderTooClose(too_close));
    assert(SensorHealth::healthSummary(too_close).find("RANGEFINDER_TOO_CLOSE") != std::string::npos);

    StateEstimator estimator;
    RobotState s1 = estimator.update(good);
    SensorReading next{1.0, 2.0, 4.0, 100.0, 2.5, 2.0, 79.0};
    RobotState s2 = estimator.update(next);
    assert(s2.x_m > s1.x_m);
    assert(s2.y_m > s1.y_m);
    assert(s2.heading_deg > s1.heading_deg);

    RobotState before_dropout = estimator.state();
    RobotState after_dropout = estimator.update(gps_dropout);
    assert(std::isfinite(after_dropout.x_m));
    assert(std::isfinite(after_dropout.y_m));
    assert(after_dropout.x_m == before_dropout.x_m);
    assert(after_dropout.y_m == before_dropout.y_m);
    assert(after_dropout.confidence < 1.0);

    std::vector<EstimatedFrame> frames;
    frames.push_back(EstimatedFrame{good, estimator.update(good), SensorHealth::healthSummary(good)});
    frames.push_back(EstimatedFrame{gps_dropout, estimator.update(gps_dropout), SensorHealth::healthSummary(gps_dropout)});
    RunSummaryData summary = RunSummary::analyze(frames);
    assert(summary.samples == 2);
    assert(summary.gps_invalid_samples == 1);
    assert(summary.final_status == "UNSAFE");

    std::cout << "All estimator tests passed.\n";
    return 0;
}
