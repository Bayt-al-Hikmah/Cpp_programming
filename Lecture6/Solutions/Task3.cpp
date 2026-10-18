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
                throw runtime_error("Division by zero is not allowed.");
            }
            return a / b;

        default:
            throw invalid_argument("Invalid operation.");
    }
}

int main() {
    double num1, num2;
    char operation;

    try {
        cout << "Enter the first number: ";
        cin >> num1;

        cout << "Enter an operation (+, -, *, /): ";
        cin >> operation;

        cout << "Enter the second number: ";
        cin >> num2;

        double result = calculate(num1, num2, operation);

        cout << "Result: " << result << '\n';
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << '\n';
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << '\n';
    }

    return 0;
}