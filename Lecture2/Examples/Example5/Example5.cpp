// Working with Loops

#include <iostream>
using namespace std;

int main() {
    // While Loop
    int i = 0;

    while (i < 5) {
        cout << "While: " << i << endl;
        i++;
    }

    // Do-While Loop
    int number = 0;

    do {
        cout << "Do-While: " << number << endl;
        number++;
    } while (number < 5);

    // For Loop
    for (int j = 0; j < 5; j++) {
        cout << "For: " << j << endl;
    }

    // Range-Based For Loop
    int numbers[] = {10, 20, 30, 40, 50};

    for (int number : numbers) {
        cout << "Range-Based For: " << number << endl;
    }

    // Range-Based For with Reference
    for (int& number : numbers) {
        number *= 2;
    }

    cout << "After multiplying:" << endl;

    for (const int& number : numbers) {
        cout << number << endl;
    }

    // Break
    for (int j = 0; j < 10; j++) {

        if (j == 5) {
            break;
        }

        cout << "Break: " << j << endl;
    }

    // Continue
    for (int j = 1; j <= 10; j++) {

        if (j % 2 == 0) {
            continue;
        }

        cout << "Continue: " << j << endl;
    }

    return 0;
}