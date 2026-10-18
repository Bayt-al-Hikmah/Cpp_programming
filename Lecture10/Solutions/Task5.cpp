#include <iostream>
#include <optional>

std::optional<double> readTemperature(bool sensorAvailable) {
    if (!sensorAvailable) {
        return std::nullopt;
    }

    // Simulated sensor reading.
    return 24.7;
}

int main() {
    std::cout << "=== Available sensor ===\n";

    std::optional<double> temperature = readTemperature(true);

    if (temperature.has_value()) {
        std::cout << "Temperature: "
                  << temperature.value() << " C\n";
    } else {
        std::cout << "Temperature unavailable.\n";
    }

    std::cout << "\n=== Unavailable sensor ===\n";

    std::optional<double> unavailable = readTemperature(false);

    if (unavailable) {
        std::cout << "Temperature: "
                  << *unavailable << " C\n";
    } else {
        std::cout << "Temperature unavailable.\n";
    }

    // Separate reporting path with a fallback.
    double reportedTemperature = unavailable.value_or(-999.0);

    std::cout << "Reported temperature: "
              << reportedTemperature << " C\n";

    return 0;
}