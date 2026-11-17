// Working with variables

#include <iostream>
#include <string> // include so we use string
using namespace std;

int main() {
    // Create variable

    // Numeric variables
    // int
    int a = 4;
    // short
    short b = 5;
    // unsigned int
    unsigned int count = 100;
    // float
    float temperature = 36.5f;
    // double
    double price = 19.99;
    // long double
    long double value = 3.141592653589793238L;

    // Character
    char grade = 'A';

    // Boolean
    bool isLoggedIn = true;

    // String
    string name = "Alice";

    // Constants
    constexpr double pi = 3.141592653589793; // compile-time constant
    const double ratio = 4.5949483;          // read-only after initialization

    std::cout << a << ' ' << b << ' ' << count << ' ' << temperature << ' '
              << price << ' ' << value << ' ' << grade << ' ' << isLoggedIn
              << ' ' << name << ' ' << pi << ' ' << ratio << '\n';

    return 0;
}