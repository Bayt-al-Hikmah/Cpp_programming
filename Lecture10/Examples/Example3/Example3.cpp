// Transferring Ownership with unique_ptr

#include <iostream>
#include <memory>
#include <string>
#include <utility>
using namespace std;

// Observe an object without taking ownership
void observe(const string& name) {
    cout << "Observing: " << name << '\n';
}

// Receive and take ownership
void takeOwnership(unique_ptr<string> name) {
    cout << "Ownership transferred: " << *name << '\n';
}

int main() {

    // Create a string with exclusive ownership
    auto source = make_unique<string>("Flow Sensor");

    cout << "=== Before Transfer ===\n";

    observe(*source);

    if (source) {
        cout << "Source owns the string.\n";
    }

    cout << "\n=== Transfer Ownership ===\n";

    takeOwnership(move(source));

    // The original pointer is now empty
    if (!source) {
        cout << "Source is now empty.\n";
    }

    cout << "\n=== Copying unique_ptr ===\n";

    auto first = make_unique<int>(100);

    // This would produce a compilation error:
    // auto second = first;

    // Correct: transfer ownership
    auto second = move(first);

    cout << "Second owns: " << *second << '\n';

    if (!first) {
        cout << "First is empty.\n";
    }

    return 0;
}