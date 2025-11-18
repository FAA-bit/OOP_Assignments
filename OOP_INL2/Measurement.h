#pragma once
#include <string>

// Represents a single measurement from a sensor.
struct Measurement { 
    std::string timestamp;
    std::string sensorName;
    double value;
    std::string unit;
};
