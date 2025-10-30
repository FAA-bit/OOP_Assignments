#pragma once
#include <string>

struct Measurement {
    std::string timestamp;
    std::string sensorName;
    double value;
    std::string unit;
};

