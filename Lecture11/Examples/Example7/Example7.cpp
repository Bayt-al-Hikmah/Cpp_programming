// String Streams: Building a Report

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {

    string sensorId = "SENSOR_01";
    double temperature = 23.5;
    bool operational = true;

    // Create an output string stream
    ostringstream report;

    // Build the report
    report << "=== Sensor Report ===\n";
    report << "Sensor ID: " << sensorId << '\n';
    report << "Temperature: " << temperature << '\n';
    report << "Operational: " << boolalpha << operational << '\n';

    // Retrieve the completed string
    string result = report.str();

    cout << result;

    return 0;
}