#pragma once
#include "Sensor.h"
#include <string>
#include <random>

// Här finns både deklaration och implementation av PressureSensor-klassen.
class PressureSensor : public Sensor {
public:
    PressureSensor(std::string id, double minV, double maxV)
        : id_(std::move(id)), minV_(minV), maxV_(maxV) {
    }

    double read() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(minV_, maxV_);
        return dist(gen);
    }

    std::string name() const override { return id_; }
    std::string unit() const override { return "hPa"; }

private:
    std::string id_;
    double minV_, maxV_;
};
