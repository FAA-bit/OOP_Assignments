#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Measurement.h"

class Sensor;

struct Threshold { // Threshold generates an alert when crossed.
    std::string sensorName;
    double limit;
    bool over; // true = alarm if value > limit, false = alarm if value < limit
};

struct Alert {
    std::string timestamp;
    std::string sensorName;
    double value;
    std::string rule;
};

class SystemController { 
public:
    void addSensor(std::unique_ptr<Sensor> s);
    void sampleAllOnce();
    void configureThreshold();
    void showAlerts() const;
    void showStatsFor(const std::string& sensorName) const;
    void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);

private:
    std::vector<std::unique_ptr<Sensor>> sensors_;
    std::vector<Measurement> data_;
    std::vector<Threshold> thresholds_;
    std::vector<Alert> alerts_;
};
