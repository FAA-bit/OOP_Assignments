#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Measurement.h"

class Sensor;

struct Threshold { // Threshold: Defines a rule: sensor name, a numeric limit, and direction (over/under).
    std::string sensorName;
    double limit; 
    bool over; // true = alarm if value > limit, false = alarm if value < limit
};

struct Alert { // Alert: Records when a rule is broken: time, sensor, value, and text about the rule.
    std::string timestamp;
    std::string sensorName;
    double value;
    std::string rule;
};

class SystemController { 
public:
    void addSensor(std::unique_ptr<Sensor> s);
    void sampleAllOnce();
    void showAllMeasurements() const;
    void configureThreshold();
    void showAlerts() const;
    void showStatsFor(const std::string& sensorName) const;
    void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);

private:
    std::vector<std::unique_ptr<Sensor>> sensors_; // En vektor av smarta pekare till Sensor‑objekt. unique_ptr - Säker minneshantering
    std::vector<Measurement> data_;  // En vektor som lagrar alla mätningar som gjorts.
    std::vector<Threshold> thresholds_; // En lista med tröskelvärden för olika sensorer.
    std::vector<Alert> alerts_; // En lista med larm som triggas när en mätning passerar ett tröskelvärde.
};
