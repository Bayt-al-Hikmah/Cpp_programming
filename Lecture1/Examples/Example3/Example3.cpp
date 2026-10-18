// Working with Numbers

#include <iostream>
using namespace std;

int main() {
  
    int a = 4;
    int b = 5;

    // Arithmetic Operations
    int addition = a + b;
    int subtraction = a - b;
    int multiplication = a * b;
    int division = a / b;
    int remainder = a % b;

    cout << "Addition = " << addition << '\n';
    cout << "Subtraction = " << subtraction << '\n';
    cout << "Multiplication = " << multiplication << '\n';
    cout << "Division = " << division << '\n';
    cout << "Remainder = " << remainder << '\n';

    // Increment and Decrement
    cout << "Increment = " << a++ << '\n';
    cout << "Decrement = " << a-- << '\n';

    // Compound Assignment
    int number = 10;

    number += 5;  // number = number + 5
    cout << "After += 5: " << number << '\n';

    number -= 3;  // number = number - 3
    cout << "After -= 3: " << number << '\n';

    number *= 2;  // number = number * 2
    cout << "After *= 2: " << number << '\n';

    number /= 4;  // number = number / 4
    cout << "After /= 4: " << number << '\n';

    number %= 3;  // number = number % 3
    cout << "After %= 3: " << number << '\n';

    return 0;
}