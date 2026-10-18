// Working with Advanced Functions

#include <iostream>
using namespace std;

// Inline Function
inline int square(int number) {
    return number * number;
}

// Recursive Function
unsigned long long factorial(unsigned int number) {
    if (number == 0) {
        return 1;
    }
    return number * factorial(number - 1);
}

// Functions for Higher-Order Functions
double add(double a, double b) {
    return a + b;
}

double multiply(double a, double b) {
    return a * b;
}

// Function Pointer Parameter
double calculate(double a, double b, double (*operation)(double, double)) {
    return operation(a, b);
}


int main() {

    // Inline Functions
    cout << "Square of 5: " << square(5) << endl;
    cout << "Square of 8: " << square(8) << endl;

    // Recursive Functions
    unsigned int number = 5;
    cout << "\nFactorial of " << number << ": " << factorial(number) << endl;

    // Function Pointers
    double result = calculate(10.0, 4.0, add);
    cout << "\nAddition: " << result << endl;
    result = calculate(10.0, 4.0, multiply);
    cout << "Multiplication: " << result << endl;

    // Lambda Expressions
    result = calculate(10.0, 4.0, [](double a, double b) {
            return a - b;
        }
    );

    cout << "Subtraction: " << result << endl;

    result = calculate(10.0, 4.0, [](double a, double b) {
            return a / b;
        }
    );
    cout << "Division: " << result << endl;

    return 0;
}