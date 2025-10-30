#include "sensor.h"
#include <random>

 
Sensor::Sensor(const std::string& name, const std::string& unit, double minValue, double maxValue)
    : name(name), unit(unit), minValue(minValue), maxValue(maxValue) {
}
// Simulate reading a sensor value
double Sensor::read() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(minValue, maxValue);
    return dist(gen);
}
// Getters
std::string Sensor::getName() const { return name; }
std::string Sensor::getUnit() const { return unit; }
