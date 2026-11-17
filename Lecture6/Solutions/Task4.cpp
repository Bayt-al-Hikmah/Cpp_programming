#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

class InvalidTemperatureError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Temperature must be between -40.0 and 125.0 C.";
    }
};

void validateTemperature(double temperature) {
    if (!std::isfinite(temperature) || temperature < -40.0 || temperature > 125.0) {
        throw InvalidTemperatureError{};
    }
}

int main() {
    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
        double temperature{};
        std::cout << "Enter a temperature in Celsius: ";

        if (!(std::cin >> temperature)) {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input: enter a numeric value.\n";
        } else {
            try {
                validateTemperature(temperature);
                std::cout << "Valid temperature: " << temperature << " C\n";
            } catch (const InvalidTemperatureError& error) {
                std::cout << "Error: " << error.what() << '\n';
            }
        }

        std::cout << "Enter another reading? (y/n): ";
        if (!(std::cin >> choice)) break;
    }
    std::cout << "Temperature monitoring stopped.\n";
}
