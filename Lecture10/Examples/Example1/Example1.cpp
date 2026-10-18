// RAII and Resource Management

#include <iostream>
#include <string>
using namespace std;

class Sensor {
private:
    string name;

public:
    // Constructor
    Sensor(string sensorName) : name(sensorName) {
        cout << "Sensor " << name << " initialized.\n";
    }

    // Destructor
    ~Sensor() {
        cout << "Sensor " << name << " destroyed.\n";
    }

    void read() const {
        cout << "Reading data from " << name << '\n';
    }
};

int main() {

    cout << "Program started.\n";

    {
        // Create a sensor object
        Sensor temperature("Temperature");

        temperature.read();

        cout << "Inside the scope.\n";
    }

    // The sensor has been destroyed automatically
    cout << "Outside the scope.\n";

    return 0;
}