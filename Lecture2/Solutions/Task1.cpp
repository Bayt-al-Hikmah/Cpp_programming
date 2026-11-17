#include <cmath>
#include <iostream>

int main() {
    double a{}, b{}, c{};
    std::cout << "Solve ax^2 + bx + c = 0\n";
    std::cout << "Enter a, b, and c: ";
    if (!(std::cin >> a >> b >> c)) {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    if (a == 0.0) {
        if (b == 0.0) {
            std::cout << (c == 0.0
                ? "Every real number is a solution.\n"
                : "There is no solution.\n");
        } else {
            std::cout << "Linear solution: x = " << -c / b << '\n';
        }
        return 0;
    }

    const double discriminant = b * b - 4.0 * a * c;
    const double tolerance = 1e-12 * (b * b + std::abs(4.0 * a * c) + 1.0);

    if (discriminant > tolerance) {
        const double root = std::sqrt(discriminant);
        const double x1 = (-b + root) / (2.0 * a);
        const double x2 = (-b - root) / (2.0 * a);
        std::cout << "Two real roots: " << x1 << " and " << x2 << '\n';
    } else if (discriminant >= -tolerance) {
        std::cout << "One real root: " << -b / (2.0 * a) << '\n';
    } else {
        std::cout << "There are no real roots.\n";
    }
}
