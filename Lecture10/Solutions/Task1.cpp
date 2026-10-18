#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Sensor {
private:
    std::string name_;
    double reading_;

public:
    Sensor(std::string name, double reading)
        : name_(std::move(name)), reading_(reading) {}

    void display() const {
        std::cout << "Sensor: " << name_
                  << ", Reading: " << reading_ << '\n';
    }
};

// Observes the sensor without taking ownership.
void observeSensor(const Sensor& sensor) {
    std::cout << "[Observation] ";
    sensor.display();
}

// Receives ownership of the sensor.
void processSensor(std::unique_ptr<Sensor> sensor) {
    if (sensor) {
        std::cout << "[Processing] ";
        sensor->display();
    }

    // The unique_ptr destroys its Sensor when this function
    // finishes, unless ownership has been transferred again.
}

int main() {
    std::cout << "=== Single sensor ===\n";

    auto sensor = std::make_unique<Sensor>("Temperature", 25.5);

    // Pass a reference: no ownership transfer.
    observeSensor(*sensor);

    // Transfer ownership to processSensor.
    processSensor(std::move(sensor));

    // The original unique_ptr is now empty.
    if (!sensor) {
        std::cout << "Original pointer is empty.\n";
    }

    // sensor->display(); // Invalid: sensor is null.

    std::cout << "\n=== Sensor collection ===\n";

    std::vector<std::unique_ptr<Sensor>> sensors;

    sensors.push_back(
        std::make_unique<Sensor>("Temperature", 25.5));

    sensors.push_back(
        std::make_unique<Sensor>("Pressure", 101.3));

    sensors.push_back(
        std::make_unique<Sensor>("Humidity", 60.0));

    for (const auto& currentSensor : sensors) {
        if (currentSensor) {
            currentSensor->display();
        }
    }

    return 0;
}