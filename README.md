# OOP_Inlämningsuppgifter

### OOP-Inlämningsuppgift 1.

## Filstruktur
projekt:
* Main.cpp - Huvudprogram och meny
* Sensor.h / sensor.cpp - Sensor-klassen: simulerar mätvärden
* Measurement.h - Measurement-struktur: lagrar enskilda mätningar
* Storage.h / .cpp - MeasurementStorage: lagrar och analyserar data

## Funktioner
✅ Sensorsimulering
- Varje sensor har namn, enhet och värdeintervall
- read() genererar ett slumpmässigt mätvärde
- Flera sensortyper stöds (t.ex. temperatur, luftfuktighet)
  
✅ Mätdatahantering
- Mätningar innehåller tidsstämpel, sensornamn, värde och enhet
- Lagring sker i en std::vector<Measurement> via MeasurementStorage
  
✅ Dataanalys
- Statistik per sensor:
- Antal mätningar
- Medelvärde
- Min-/maxvärde
- Standardavvikelse
- Utskrifter formateras med precision
  
✅ Filhantering
- Spara mätdata till CSV-fil
- Läs in mätdata från CSV-fil
- Hantera felaktiga rader robust
  
✅ Menygränssnitt
- Läs nya mätvärden från alla sensorer
- Visa all lagrad data
- Visa statistik per sensor
- Spara/läs data till/från fil

### OOP-Inlämningsuppgift 2.
## Förklaring:
- Sensor är en abstrakt basklass med rena virtuella metoder.
- TemperatureSensor, HumiditySensor och PressureSensor ärver från Sensor och åsidosätter dess metoder.
- Measurement innehåller rådata från sensorer.
- Threshold definierar larmregler.
- Alert registrerar utlösta larm.
- SystemController hanterar sensorer polymorfiskt, lagrar mätningar, tillämpar tröskelvärden och hanterar varningar.

## UML-klassdiagram.

                +-------------------+
                |   Sensor (abstract)|
                +-------------------+
                | +read(): double   |
                | +name(): string   |
                | +unit(): string   |
                +-------------------+
                        ▲
        -----------------------------------------
        |                   |                   |
+-------------------+ +-------------------+ +-------------------+
| TemperatureSensor | | HumiditySensor    | | PressureSensor    |
+-------------------+ +-------------------+ +-------------------+
| -id_: string      | | -id_: string      | | -id_: string      |
| -minV_: double    | | -minV_: double    | | -minV_: double    |
| -maxV_: double    | | -maxV_: double    | | -maxV_: double    |
+-------------------+ +-------------------+ +-------------------+
| +read(): double   | | +read(): double   | | +read(): double   |
| +name(): string   | | +name(): string   | | +name(): string   |
| +unit(): string   | | +unit(): string   | | +unit(): string   |
+-------------------+ +-------------------+ +-------------------+

+-------------------+
| Measurement       |
+-------------------+
| timestamp: string |
| sensorName: string|
| value: double     |
| unit: string      |
+-------------------+

+-------------------+
| Threshold         |
+-------------------+
| sensorName: string|
| limit: double     |
| over: bool        |
+-------------------+

+-------------------+
| Alert             |
+-------------------+
| timestamp: string |
| sensorName: string|
| value: double     |
| rule: string      |
+-------------------+

+-------------------+
| SystemController  |
+-------------------+
| -sensors_: vector |
| -data_: vector    |
| -thresholds_: vector|
| -alerts_: vector  |
+-------------------+
| +addSensor()      |
| +sampleAllOnce()  |
| +configureThreshold() |
| +showAlerts()     |
| +showStatsFor()   |
| +saveToFile()     |
| +loadFromFile()   |
+-------------------+


# FAID ABSHIR ABDILE #
