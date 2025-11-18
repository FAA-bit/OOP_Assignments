// OOP_INL2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// main.cpp

#include <iostream>
#include <memory>
#include "SystemController.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "PressureSensor.h"

int main() {
    SystemController controller;

    controller.addSensor(std::make_unique<TemperatureSensor>("TempSensor1", -10, 40));
    controller.addSensor(std::make_unique<HumiditySensor>("HumiditySensor1", 0, 100));
    controller.addSensor(std::make_unique<PressureSensor>("PressureSensor1", 950, 1050));

    bool running = true;
    while (running) {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Read new measurements\n";
        std::cout << "2. Show statistics for a sensor\n";
        std::cout << "3. Show all alerts\n";
        std::cout << "4. Configure threshold rule\n";
        std::cout << "5. Save measurement data to file\n";
        std::cout << "6. Load measurement data from file\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            controller.sampleAllOnce();
            break;
        case 2: {
            std::string sensorName;
            std::cout << "Enter sensor name: ";
            std::cin >> sensorName;
            controller.showStatsFor(sensorName);
            break;
        }
        case 3:
            controller.showAlerts();
            break;
        case 4:
            controller.configureThreshold();
            break;
        case 5: {
            std::string filename;
            std::cout << "Filename to save to: ";
            std::cin >> filename;
            controller.saveToFile(filename);
            break;
        }
        case 6: {
            std::string filename;
            std::cout << "Filename to load from: ";
            std::cin >> filename;
            controller.loadFromFile(filename);
            break;
        }
        case 0:
            running = false;
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "Program terminated.\n";
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
