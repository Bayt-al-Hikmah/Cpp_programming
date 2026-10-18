// Working with Header Files

#include <iostream>
#include "math_utils.hpp"
using namespace std;

int main() {

    // Variables
    int number;

    // Input
    cout << "Enter an integer: ";
    cin >> number;

    // Calling the Function
    cout << "Square: " << square(number) << endl;

    return 0;
}