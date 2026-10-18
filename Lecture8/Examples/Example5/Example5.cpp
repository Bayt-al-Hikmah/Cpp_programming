#include <iostream>

using namespace std;

int main() {
    // Lambda with no parameters.
    auto sayHello = []() {
        cout << "Hello!\n";
    };

    sayHello();

    // Lambda with two parameters.
    auto add = [](int a, int b) {
        return a + b;
    };

    cout << "Sum: " << add(10, 20) << '\n';

    // Lambda that returns a value.
    auto square = [](int number) {
        return number * number;
    };

    cout << "Square: " << square(5) << '\n';

    // Lambda with an explicit return type.
    auto divide = [](double a, double b) -> double {
        return a / b;
    };

    cout << "Division: " << divide(10.0, 4.0) << '\n';

    return 0;
}