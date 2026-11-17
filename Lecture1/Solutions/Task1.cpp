#include <iostream>

int main() {
    constexpr double pi = 3.14159265358979323846;
    double radius{};

    std::cout << "Enter the circle radius: ";
    if (!(std::cin >> radius) || radius < 0.0) {
        std::cerr << "Please enter a non-negative number.\n";
        return 1;
    }

    const double area = pi * radius * radius;
    std::cout << "Circle area: " << area << '\n';
}
