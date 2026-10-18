// Working with Control Flow

#include <iostream>
using namespace std;

int main() {

    int age = 20;
    int number = -5;
    int choice = 2;

    // If Statement
    if (age >= 18) {
        cout << "You are an adult." << endl;
    }

    // If Else Statement
    if (age >= 18) {
        cout << "Access granted." << endl;
    }
    else {
        cout << "Access denied." << endl;
    }

    // If Else If Statement
    if (number > 0) {
        cout << "Number is positive." << endl;
    }
    else if (number < 0) {
        cout << "Number is negative." << endl;
    }
    else {
        cout << "Number is zero." << endl;
    }

    // Ternary Operator
    string status = (age >= 18) ? "Adult" : "Minor";

    cout << "Status: " << status << endl;

    // Switch Statement
    switch (choice) {

        case 1:
            cout << "Start" << endl;
            break;

        case 2:
            cout << "Settings" << endl;
            break;

        case 3:
            cout << "Help" << endl;
            break;

        case 4:
            cout << "Exit" << endl;
            break;

        default:
            cout << "Invalid choice" << endl;
            break;
    }

    // Working with Intentional Fallthrough

    switch (number) {

        case 1:
            cout << "One" << endl;
            [[fallthrough]];

        case 2:
            cout << "Two" << endl;
            break;

        default:
            cout << "Other number" << endl;
            break;
    }

    return 0;
}