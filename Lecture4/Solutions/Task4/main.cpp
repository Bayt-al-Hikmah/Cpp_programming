// Working with Header Files

#include <iostream>
#include "number_utils.hpp"
using namespace std;

int main() {

    // Variables
    int number;

    // Input
    cout << "Enter an integer: ";
    cin >> number;

    // Calling the Function
    if (isEven(number)) {
        cout << number << " is even." << endl;
    } else {
        cout << number << " is odd." << endl;
    }

    return 0;
}