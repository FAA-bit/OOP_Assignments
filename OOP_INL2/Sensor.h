#pragma once 
#include <string> 


class Sensor {  // Deklarerar en abstrakt basklass för alla sensorer.
	/*En abstrakt basklass är alltså en grundmall som definierar vilka funktioner som måste finnas, 
	men lämnar implementationen till subklasserna.
	Den används för att skapa gemensamma regler och möjliggöra polymorfism.
	*/
public:
	virtual ~Sensor() = default; // en virtuell destruktor att säkerställa korrekt minneshantering när jag använder pekare.
	// pure virtual function är en metod som deklareras i en basklass men inte har någon implementation där.
	virtual double read() = 0;  
	virtual std::string name() const = 0; 
	virtual std::string unit() const = 0; 
	// Måste implementeras i alla subklasser.
};

/* The abstract Sensor base class has three concrete subclasses:
			- TemperatureSensor
			- HumiditySensor
			- PressureSensor
*/