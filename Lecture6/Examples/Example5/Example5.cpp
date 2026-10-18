// Working with exceptions
#include <iostream>
#include <stdexcept>
using namespace std;

double calculate(double a, double b, char operation) {
    switch (operation) {
        case '+':
            return a + b;

        case '-':
            return a - b;

        case '*':
            return a * b;

        case '/':
            if (b == 0) {
                throw invalid_argument("Cannot divide by zero.");
            }

            return a / b;

        default:
            throw invalid_argument("Invalid operation.");
    }
}

int main() {
    double a, b;
    char operation;

    cout << "Enter the first number: ";
    cin >> a;

    cout << "Enter an operation (+, -, *, /): ";
    cin >> operation;

    cout << "Enter the second number: ";
    cin >> b;

    try {
        double result = calculate(a, b, operation);
        cout << "Result: " << result << '\n';
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}