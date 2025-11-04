// OOP_INL1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Main.cpp

#include <iostream>
#include <vector>
#include <ctime>
#include "sensor.h"
#include "measurement.h"
#include "storage.h"

using namespace std;

string getTimestamp() {  // Get current timestamp as string
    time_t now = time(0);
    struct tm tid;
    localtime_s(&tid, &now);
	char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tid);
	return string(buf);
}

int main() {
    Sensor temperatur("TemperaturSensor", "°C", 18.0, 25.0);
    Sensor humidity("HumiditySensor", "%", 30.0, 60.0);
    Sensor pressure("PressureSensor", "hPa", 950.0, 1050.0);
	Sensor light("LightSensor", "Lux", 100.0, 1000.0);
    Sensor sound("SoundSensor", "dB", 30.0, 90.0);
    vector<Sensor> sensors = { temperatur, humidity, pressure, light, sound };

    MeasurementStorage storage;
    int choice;

    do {
        cout << "\n--- Menu:---\n";
        cout << "1. Read new measurements\n";
        cout << "2. Show all measurements\n";
        cout << "3. Show statistics per sensor\n";
        cout << "4. Save to file\n";
        cout << "5. Load from file\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
        case 1:
            for (const auto& s : sensors) {
                double val = s.read();
                storage.addMeasurement({ getTimestamp(), s.getName(), val, s.getUnit() });
            }
            cout << "Measurements recorded.\n";
            break;
        case 2:
            storage.printAll();
            break;
        case 3: {
            string name;
            cout << "Enter sensor name: ";
            cin.ignore(); getline(cin, name);
            storage.printStats(name);
            break;
        }
        case 4: {
            string filename;
            cout << "Enter filename to save: ";
            cin >> filename;
            storage.saveToFile(filename);
            break;
        }
        case 5: {
            string filename;
            cout << "Enter filename to load: ";
            cin >> filename;
            storage.loadFromFile(filename);
            break;
        }
        case 0:
            cout << "Exiting...\n";
			break;
        default:
			cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 0);
	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
