// Working with variant

#include <iostream>
#include <string>
#include <variant>
using namespace std;

int main() {

    // Define the possible types
    using Setting = variant<int, double, string>;

    cout << "=== Integer Setting ===\n";

    Setting setting = 100;

    if (holds_alternative<int>(setting)) {
        cout << "Integer: " << get<int>(setting) << '\n';
    }

    cout << "\n=== Double Setting ===\n";

    // Replace the integer with a double
    setting = 25.5;

    if (const double* value = get_if<double>(&setting)) {
        cout << "Double: " << *value << '\n';
    }

    cout << "\n=== String Setting ===\n";

    // Replace the double with a string
    setting = string("Automatic");

    if (holds_alternative<string>(setting)) {
        cout << "String: "
             << get<string>(setting) << '\n';
    }

    cout << "\n=== Visit the Active Value ===\n";

    visit([](const auto& value) {
        cout << "Active value: " << value << '\n';
    }, setting);

    cout << "\n=== Request the Wrong Type ===\n";

    try {
        // The active alternative is string, not int
        cout << get<int>(setting) << '\n';
    } catch (const bad_variant_access&) {
        cout << "Error: The active type is not int.\n";
    }

    return 0;
}