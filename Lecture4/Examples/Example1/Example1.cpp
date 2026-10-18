// Working with Functions

#include <iostream>
#include <string>
using namespace std;

// Function Declarations
int sum(int a, int b);
double sum(double a, double b);
int cube(int number);

void swapByValue(int a, int b);
void swapByReference(int& a, int& b);

void printName(const string& name);
void greet(const string& name, const string& greeting = "Hello");


int main() {

    // Calling Functions
    int result = sum(10, 20);
    cout << "Sum: " << result << endl;
    cout << "Cube: " << cube(3) << endl;

    // Function Overloading
    cout << "Integer Sum: " << sum(5, 10) << endl;
    cout << "Double Sum: " << sum(2.5, 3.5) << endl;

    // Pass-by-Value
    int a = 5;
    int b = 10;

    cout << "\nBefore swapByValue: a = " << a << ", b = " << b << endl;
    swapByValue(a, b);
    cout << "After swapByValue: a = " << a << ", b = " << b << endl;

    // Pass-by-Reference
    cout << "\nBefore swapByReference: a = " << a << ", b = " << b << endl;
    swapByReference(a, b);
    cout << "After swapByReference: a = " << a << ", b = " << b << endl;

    // Const Reference
    string name = "Ali";
    printName(name);

    // Default Arguments
    greet("Ali");
    greet("Sara", "Welcome");

    return 0;
}


// Function Definitions
int sum(int a, int b) {
    return a + b;
}

double sum(double a, double b) {
    return a + b;
}

int cube(int number) {
    return number * number * number;
}

// Pass-by-Value
void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

// Pass-by-Reference
void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Const Reference
void printName(const string& name) {
    cout << "\nName: " << name << endl;
    // name = "Omar"; // Error: name cannot be modified
}

// Default Arguments
void greet(const string& name, const string& greeting) {
    cout << greeting << ", " << name << "!" << endl;
}