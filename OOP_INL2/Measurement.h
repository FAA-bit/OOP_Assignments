#pragma once
#include <string>


struct Measurement {  // Represents one recorded measurement with time, sensor name, numeric value, and unit.
    std::string timestamp;
    std::string sensorName;
    double value;
    std::string unit;
};
