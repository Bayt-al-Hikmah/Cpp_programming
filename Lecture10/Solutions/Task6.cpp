#include <iostream>
#include <string>
#include <variant>

using Setting = std::variant<int, double, std::string>;

void printSetting(const Setting& setting) {
    std::visit(
        [](const auto& value) {
            std::cout << "Value: " << value << '\n';
        },
        setting
    );
}

int main() {
    Setting setting = 42;

    std::cout << "=== Integer ===\n";

    if (std::holds_alternative<int>(setting)) {
        std::cout << "Active type: int\n";
    }

    printSetting(setting);

    std::cout << "\n=== Floating-point ===\n";

    setting = 3.14159;

    if (const double* value = std::get_if<double>(&setting)) {
        std::cout << "Active type: double\n";
        std::cout << "Value through get_if: "
                  << *value << '\n';
    }

    printSetting(setting);

    std::cout << "\n=== String ===\n";

    setting = std::string("Temperature sensor");

    if (std::holds_alternative<std::string>(setting)) {
        std::cout << "Active type: string\n";
    }

    printSetting(setting);

    std::cout << "\n=== Incorrect type request ===\n";

    try {
        int value = std::get<int>(setting);

        std::cout << "Integer: " << value << '\n';
    } catch (const std::bad_variant_access& error) {
        std::cout << "Type mismatch: "
                  << error.what() << '\n';
    }

    return 0;
}