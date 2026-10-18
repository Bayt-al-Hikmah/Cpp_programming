// String Streams: Parsing Structured Data

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {

    // Store a sensor record in a string
    string record = "SENSOR_01 23.5 NORMAL";

    // Create a string stream
    stringstream input(record);

    string sensorId;
    double temperature;
    string status;

    // Extract each field
    if (input >> sensorId >> temperature >> status) {

        cout << "Sensor ID: " << sensorId << '\n';
        cout << "Temperature: " << temperature << '\n';
        cout << "Status: " << status << '\n';

    } else {
        cerr << "Invalid sensor record.\n";
        return 1;
    }

    return 0;
}