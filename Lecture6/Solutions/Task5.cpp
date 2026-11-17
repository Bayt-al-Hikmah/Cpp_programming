#include <cassert>
#include <cmath>
#include <expected>
#include <iostream>
#include <optional>
#include <string>

std::expected<double, std::string> convertToNumber(const std::string& input) {
    if (input.empty()) {
        return std::unexpected("Input cannot be empty.");
    }

    try {
        std::size_t processed = 0;
        const double number = std::stod(input, &processed);
        if (processed != input.size() || !std::isfinite(number)) {
            return std::unexpected("Enter one complete, finite number.");
        }
        return number;
    } catch (const std::invalid_argument&) {
        return std::unexpected("Input does not contain a valid number.");
    } catch (const std::out_of_range&) {
        return std::unexpected("The number is outside the supported range.");
    }
}

std::optional<double> validateRange(double number) {
    if (number < 0.0 || number > 100.0) {
        return std::nullopt;
    }
    return number;
}

int main() {
    std::string input;
    std::cout << "Enter a number between 0 and 100: ";
    if (!(std::cin >> input)) {
        std::cerr << "No input was provided.\n";
        return 1;
    }

    const auto converted = convertToNumber(input);
    if (!converted) {
        std::cerr << "Conversion error: " << converted.error() << '\n';
        return 1;
    }

    const auto validated = validateRange(*converted);
    if (!validated) {
        std::cerr << "The number must be between 0 and 100.\n";
        return 1;
    }

    assert(*validated >= 0.0 && *validated <= 100.0);
    static_assert(100 >= 0, "The upper bound must be non-negative.");
    std::cout << "Converted number: " << *validated << '\n';
}
