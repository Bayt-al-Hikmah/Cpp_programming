// Understanding C++ Value Categories

#include <iostream>
#include <string>
#include <utility>
using namespace std;

// Accept an lvalue through a read-only reference
void describe(const string& text) {
    cout << "Lvalue overload: " << text << '\n';
}

// Accept an rvalue through an rvalue reference
void describe(string&& text) {
    cout << "Rvalue overload: " << text << '\n';
}

int main() {

    // Named variable: lvalue expression
    string sensor = "Temperature";

    cout << "=== Lvalue ===\n";

    describe(sensor);

    cout << "\n=== Prvalue ===\n";

    // Temporary string: prvalue expression
    describe(string("Pressure"));

    cout << "\n=== Xvalue ===\n";

    // std::move(sensor) produces an xvalue
    describe(move(sensor));

    cout << "\n=== Named Rvalue Reference ===\n";

    string original = "Humidity";

    // Bind an rvalue reference
    string&& reference = move(original);

    // The name 'reference' is an lvalue expression
    describe(reference);

    // Explicitly produce an xvalue
    describe(move(reference));

    cout << "\n=== Integer Expressions ===\n";

    int number = 10;

    // number is an lvalue
    cout << "Number: " << number << '\n';

    // 42 is a prvalue
    cout << "Literal: " << 42 << '\n';

    // number + 5 is a prvalue
    cout << "Sum: " << number + 5 << '\n';

    return 0;
}