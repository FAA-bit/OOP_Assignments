#include "SystemController.h"
#include "Sensor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <cmath>

void SystemController::addSensor(std::unique_ptr<Sensor> s) {
    sensors_.push_back(std::move(s));
}

void SystemController::sampleAllOnce() {
    for (auto& s : sensors_) {
		double val = s->read(); // Read() - is a polymorphic function that retrieves a measurement from the respective sensor.

		// Get current timestamp
        std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

        struct tm buf;
        localtime_s(&buf, &t);

        std::ostringstream oss;
        oss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");
        std::string ts = oss.str();

        /*auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        std::ostringstream oss;
        oss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
        std::string ts = oss.str();
        */

		data_.push_back({ ts, s->name(), val, s->unit() }); // Store measurement: Records the timestamp, sensor name, value, and unit.

		// Check thresholds: For matching sensor rules, evaluates the condition and logs an alert if broken.
        for (const auto& t : thresholds_) {
            if (t.sensorName == s->name()) {
                bool alarm = (t.over && val > t.limit) || (!t.over && val < t.limit);
                if (alarm) {
                    alerts_.push_back({ ts, s->name(), val,
                        t.over ? ">" + std::to_string(t.limit) : "<" + std::to_string(t.limit) });
                }
            }
        }
    }
}

void SystemController::showAllMeasurements() const {
    if (data_.empty()) {
        std::cout << "No measurements recorded yet.\n";
        return;
    }

    for (const auto& m : data_) {
        std::cout << m.timestamp << " | " << m.sensorName
            << " = " << m.value << " " << m.unit << "\n";
    }
}

// Configures a new threshold rule based on user input.
void SystemController::configureThreshold() {
    std::string sensor;
    double limit;
    char direction;

    std::cout << "Sensor name: ";
    std::cin >> sensor;
    std::cout << "Limit value: ";
    std::cin >> limit;
    std::cout << "Direction (o=over, u=under): ";
    std::cin >> direction;

    thresholds_.push_back({ sensor, limit, direction == 'o' });
}

// Prints all recorded alerts.
void SystemController::showAlerts() const {
    for (const auto& a : alerts_) {
        std::cout << a.timestamp << " | " << a.sensorName
            << " value=" << a.value << " broke rule " << a.rule << "\n";
    }
	// If no alerts.
    if (alerts_.empty()) {
		std::cout << "No alerts recorded.\n";
	}
}

void SystemController::showStatsFor(const std::string& sensorName) const {
	std::vector<double> values; 
	for (const auto& m : data_) { // Collects all values ​​that match the requested sensor name.
        if (m.sensorName == sensorName) values.push_back(m.value);
    }
    if (values.empty()) {
        std::cout << "No data for " << sensorName << "\n";
        return;
    }
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    double mean = sum / values.size();
    double min = *std::min_element(values.begin(), values.end());
    double max = *std::max_element(values.begin(), values.end());
    double variance = 0.0;
    for (double v : values) variance += (v - mean) * (v - mean);
    double stddev = std::sqrt(variance / values.size());

    std::cout << "Stats for " << sensorName << "\n";
    std::cout << "Count: " << values.size() << "\n";
    std::cout << "Average: " << mean << "\n";
    std::cout << "Min: " << min << "\n";
    std::cout << "Max: " << max << "\n";
    std::cout << "Stddev: " << stddev << "\n";
}

void SystemController::saveToFile(const std::string& path) const {
    std::ofstream file(path);
    for (const auto& m : data_) { 
        file << m.timestamp << "," << m.sensorName << "," << m.value << "," << m.unit << "\n";
    }
    std::cout << "Saved to " << path << "\n";
}

void SystemController::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string ts, name, valStr, unit;
        if (std::getline(ss, ts, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, valStr, ',') &&
            std::getline(ss, unit)) {
			double val = std::stod(valStr);
            data_.push_back({ ts, name, val, unit });
        }
    }
    std::cout << "Loaded from " << path << "\n";
}