#pragma once
#include "Sensor.h"
#include <string>
#include <random>

// Här finns både deklaration och implementation av HumiditySensor-klassen.
class HumiditySensor : public Sensor {
public:
    HumiditySensor(std::string id, double minV, double maxV)
        : id_(std::move(id)), minV_(minV), maxV_(maxV) {
    }
	// Implementering av den rena virtuella funktionen read
    double read() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(minV_, maxV_);
        return dist(gen);
    }
	// Implementering av den rena virtuella funktionen name
    std::string name() const override { return id_; }
    std::string unit() const override { return "%"; }

private:
    std::string id_;
    double minV_, maxV_;
};
