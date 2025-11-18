#pragma once 
#include <string> 

// Abstract base class for sensors.
class Sensor { 
public:
	virtual ~Sensor() = default; // virtual destructor
	virtual double read() = 0;  // pure virtual function
	virtual std::string name() const = 0; // pure virtual function
	virtual std::string unit() const = 0; // pure virtual function
};