// Working with optional

#include <iostream>
#include <optional>
using namespace std;

// Read temperature from a sensor
optional<double> readTemperature(bool sensorAvailable) {

    if (!sensorAvailable) {
        return nullopt;
    }

    // Simulated measurement
    return 24.7;
}

int main() {

    cout << "=== Available Sensor ===\n";

    optional<double> temperature = readTemperature(true);

    // Check whether a value exists
    if (temperature.has_value()) {
        cout << "Temperature: "
             << temperature.value() << " C\n";
    }

    cout << "\n=== Unavailable Sensor ===\n";

    optional<double> missingTemperature =
        readTemperature(false);

    // Check before accessing the value
    if (missingTemperature) {
        cout << "Temperature: "
             << *missingTemperature << " C\n";
    } else {
        cout << "Temperature is unavailable.\n";
    }

    cout << "\n=== Default Value ===\n";

    double reportedTemperature =
        missingTemperature.value_or(-999.0);

    cout << "Reported temperature: "
         << reportedTemperature << " C\n";

    cout << "\n=== Reset Optional ===\n";

    temperature.reset();

    if (!temperature) {
        cout << "Temperature value removed.\n";
    }

    return 0;
}