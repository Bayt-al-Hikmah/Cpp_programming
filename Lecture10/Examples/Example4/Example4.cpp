// Managing Multiple Sensors

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Sensor {
private:
    string name;
    double reading;

public:
    Sensor(string sensorName, double sensorReading)
        : name(std::move(sensorName)), reading(sensorReading) {}

    void display() const {
        cout << "Sensor: " << name
             << ", Reading: " << reading << '\n';
    }
};

int main() {

    // Create a dynamically sized collection
    vector<unique_ptr<Sensor>> sensors;

    // Add sensors to the collection
    sensors.push_back(
        make_unique<Sensor>("Temperature", 24.5));

    sensors.push_back(
        make_unique<Sensor>("Pressure", 101.3));

    sensors.push_back(
        make_unique<Sensor>("Humidity", 45.0));

    cout << "Number of sensors: "
         << sensors.size() << "\n\n";

    // Display every sensor
    for (const auto& sensor : sensors) {
        sensor->display();
    }

    // Add another sensor
    sensors.push_back(
        make_unique<Sensor>("Flow", 12.7));

    cout << "\nAfter adding another sensor:\n";
    cout << "Number of sensors: "
         << sensors.size() << '\n';

    // Removing an element destroys its sensor
    sensors.pop_back();

    cout << "\nAfter removing the last sensor:\n";
    cout << "Number of sensors: "
         << sensors.size() << '\n';

    return 0;
}