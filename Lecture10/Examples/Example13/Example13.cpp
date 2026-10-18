// Working with any

#include <any>
#include <iostream>
#include <string>
using namespace std;

int main() {

    // Create an any containing an integer
    any metadata = 12345;

    cout << "=== Integer Metadata ===\n";

    if (const int* id = any_cast<int>(&metadata)) {
        cout << "Sensor ID: " << *id << '\n';
    }

    cout << "\n=== Replace with String ===\n";

    // Store a string instead
    metadata = string("TemperatureSensor");

    if (const string* label = any_cast<string>(&metadata)) {
        cout << "Sensor label: " << *label << '\n';
    }

    cout << "\n=== Request the Wrong Type ===\n";

    // Safely test whether the value is an integer
    if (const int* id = any_cast<int>(&metadata)) {
        cout << "Sensor ID: " << *id << '\n';
    } else {
        cout << "Metadata does not contain an integer.\n";
    }

    cout << "\n=== Check Stored Value ===\n";

    if (metadata.has_value()) {
        cout << "Metadata contains a value.\n";
    }

    cout << "\n=== Reset Metadata ===\n";

    metadata.reset();

    if (!metadata.has_value()) {
        cout << "Metadata is empty.\n";
    }

    return 0;
}