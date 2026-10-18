#include <iostream>
#include <exception>
#include <string>

using namespace std;

// Custom exception class
class InvalidTemperatureError : public exception {
public:
    const char* what() const noexcept override {
        return "Temperature is outside the allowed range (-40.0 to 125.0 C).";
    }
};

// Function to validate the temperature
void validateTemperature(double temperature) {
    if (temperature < -40.0 || temperature > 125.0) {
        throw InvalidTemperatureError();
    }
}

int main() {
    double temperature;
    char choice;

    do {
        cout << "\nEnter temperature reading (Celsius): ";

        if (!(cin >> temperature)) {
            cout << "Error: Invalid input. Please enter a numeric value.\n";
            cout << "Do you want to try again? (y/n): ";
            cin >> choice;
            continue;
        }

        try {
            validateTemperature(temperature);

            cout << "Valid temperature: " << temperature << " C\n";
        }
        catch (const InvalidTemperatureError& e) {
            cout << "Error: " << e.what() << '\n';
        }

        cout << "\nDo you want to enter another reading? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Temperature monitoring stopped.\n";

    return 0;
}