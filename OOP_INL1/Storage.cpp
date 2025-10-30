#include "Storage.h"
#include "Measurement.h"
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>  


void MeasurementStorage::addMeasurement(const Measurement& m) {
	data.push_back(m);
}

void MeasurementStorage::printAll() const {
	for (const auto& m : data) {
		std::cout << std::fixed << std::setprecision(2)
			<< m.timestamp << ", " << m.sensorName << ", "
			<< m.value << ", " << m.unit << std::endl;
	}
}

void MeasurementStorage::printStats(const std::string& sensorName) const {
    std::vector<double> values;

    for (const auto& m : data) {
        if (m.sensorName == sensorName) {
            values.push_back(m.value);
        }
    }

    if (values.empty()) {
        std::cout << "No measurements found for sensor: " << sensorName << std::endl;
        return;
    }

    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    double mean = sum / values.size();
    double min = *std::min_element(values.begin(), values.end());
    double max = *std::max_element(values.begin(), values.end());

    double variance = 0.0;
    for (double v : values) {
        variance += (v - mean) * (v - mean);
    }
    double stddev = std::sqrt(variance / values.size());

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Statistics for sensor: " << sensorName << std::endl;
    std::cout << "Count: " << values.size() << std::endl;
    std::cout << "Average: " << mean << std::endl;
    std::cout << "Min: " << min << std::endl;
    std::cout << "Max: " << max << std::endl;
    std::cout << "Standard deviation: " << stddev << std::endl;
}
void MeasurementStorage::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& m : data) {
        file << m.timestamp << "," << m.sensorName << "," << m.value << "," << m.unit << "\n";
    }

    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}

void MeasurementStorage::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string timestamp, name, valueStr, unit;

        if (std::getline(ss, timestamp, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, valueStr, ',') &&
            std::getline(ss, unit)) {

            try {
                double value = std::stod(valueStr);
                data.push_back({ timestamp, name, value, unit });
            }
            catch (...) {
                std::cerr << "Invalid line skipped: " << line << std::endl;
            }
        }
    }

    file.close();
    std::cout << "Data loaded from " << filename << std::endl;
}

void MeasurementStorage::searchBySensor(const std::string& sensorName) const {
    std::cout << "Filtered measurements for sensor: " << sensorName << std::endl;
    for (const auto& m : data) {
        if (m.sensorName == sensorName) {
            std::cout << std::fixed << std::setprecision(2)
                << m.timestamp << ", " << m.sensorName << ", "
                << m.value << ", " << m.unit << std::endl;
        }
    }
}