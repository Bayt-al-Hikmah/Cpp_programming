// Working with custom exceptions
#include <exception>
#include <iostream>
using namespace std;

class InvalidTemperatureError : public exception {
public:
    const char* what() const noexcept override {
        return "Temperature must be between -40 and 125 degrees.";
    }
};

void checkTemperature(double temperature) {
    if (temperature < -40.0 || temperature > 125.0) {
        throw InvalidTemperatureError();
    }

    cout << "Valid temperature: " << temperature << " C\n";
}

int main() {
    double temperature;

    cout << "Enter temperature: ";
    cin >> temperature;

    try {
        checkTemperature(temperature);
    }
    catch (const InvalidTemperatureError& e) {
        cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}