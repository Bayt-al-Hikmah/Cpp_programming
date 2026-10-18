#include <any>
#include <iostream>
#include <string>

int main() {
    std::any metadata;

    std::cout << "=== Store integer identifier ===\n";

    metadata = 12345;

    if (const int* id = std::any_cast<int>(&metadata)) {
        std::cout << "Identifier: " << *id << '\n';
    }

    std::cout << "\n=== Replace with string label ===\n";

    metadata = std::string("TemperatureSensor");

    if (const std::string* label =
            std::any_cast<std::string>(&metadata)) {
        std::cout << "Label: " << *label << '\n';
    }

    std::cout << "\n=== Safe type mismatch ===\n";

    if (const int* id = std::any_cast<int>(&metadata)) {
        std::cout << "Identifier: " << *id << '\n';
    } else {
        std::cout << "Metadata does not contain an integer.\n";
    }

    std::cout << "\n=== Check stored value ===\n";

    if (metadata.has_value()) {
        std::cout << "Metadata contains a value.\n";
    }

    std::cout << "\n=== Reset metadata ===\n";

    metadata.reset();

    if (!metadata.has_value()) {
        std::cout << "Metadata is empty.\n";
    }

    return 0;
}