#include <iostream>
#include <limits>
#include <string>

std::string toBinary(unsigned int value) {
    if (value < 2) {
        return std::to_string(value);
    }
    return toBinary(value / 2) + std::to_string(value % 2);
}

int main() {
    long long input{};
    std::cout << "Enter a non-negative integer: ";
    if (!(std::cin >> input) || input < 0) {
        std::cerr << "Please enter a non-negative integer.\n";
        return 1;
    }
    if (static_cast<unsigned long long>(input) >
        static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max())) {
        std::cerr << "The value is too large for this example.\n";
        return 1;
    }

    std::cout << "Binary: " << toBinary(static_cast<unsigned int>(input)) << '\n';
}
