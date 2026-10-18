#include <iostream>
#include <memory>
#include <string>
#include <utility>

void process(const std::string& text) {
    std::cout << "Lvalue overload: " << text << '\n';
}

void process(std::string&& text) {
    std::cout << "Rvalue overload: " << text << '\n';
}

int main() {
    std::cout << "=== Overload resolution ===\n";

    std::string namedString = "Temperature";

    // A named variable is an lvalue.
    process(namedString);

    // A temporary string is an rvalue.
    process(std::string("Pressure"));

    // std::move converts the expression to an xvalue.
    process(std::move(namedString));

    std::cout << "\n=== Named rvalue reference ===\n";

    std::string original = "Humidity";

    std::string&& reference = std::move(original);

    // Although reference has type string&&,
    // the expression 'reference' is an lvalue.
    process(reference);

    // Explicitly produce an rvalue expression.
    process(std::move(reference));

    std::cout << "\n=== Moving unique_ptr ===\n";

    auto first = std::make_unique<int>(42);

    auto second = std::move(first);

    if (!first) {
        std::cout << "first is empty.\n";
    }

    if (second) {
        std::cout << "second owns: " << *second << '\n';
    }

    std::cout << "\n=== Moved-from string ===\n";

    std::string message = "Hello";

    std::string destination = std::move(message);

    std::cout << "Destination: " << destination << '\n';

    // message is valid but its value is unspecified.
    std::cout << "Source after move: " << message << '\n';

    // Assign a known value before using it for further work.
    message = "Ready";

    std::cout << "Source after reassignment: "
              << message << '\n';

    return 0;
}