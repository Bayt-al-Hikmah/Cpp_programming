// Working with Scope, Storage Duration, and Lifetime
#include <iostream>
using namespace std;

// Global Variable
int value = 100;

// Function Declaration
void countCalls();
void showScope();
int& getElement(int numbers[], int index);

int main() {

    // Global Variable
    cout << "Global value: " << value << endl;

    // Local Variable and Shadowing
    int value = 20;
    cout << "\nLocal value: " << value << endl;
    cout << "Global value: " << ::value << endl;


    // Block Scope
    int x = 10;
    {
        int y = 20;
        cout << "\nOuter block x: " << x << endl;
        cout << "Inner block y: " << y << endl;
        x = 30;
    }
    cout << "Modified x: " << x << endl;
    // cout << y; // Error: y is outside its scope

    // Function Scope Demonstration
    cout << "\nCalling showScope():" << endl;
    showScope();

    // Static and Automatic Variables
    cout << "\nCounting Function Calls:" << endl;
    countCalls();
    countCalls();
    countCalls();

    // Returning a Reference
    int numbers[] = {10, 20, 30};
    cout << "\nBefore modification: " << numbers[1] << endl;
    getElement(numbers, 1) = 99;
    cout << "After modification: " << numbers[1] << endl;

    return 0;
}

// Local and Block Scope
void showScope() {
    int number = 10;
    {
        int number2 = 20;
        cout << "Local number: " << number << endl;
        cout << "Block number2: " << number2 << endl;
    }
    // cout << number2; // Error: number2 is outside its scope
}

// Automatic and Static Storage Duration
void countCalls() {
    int ordinaryCount = 0;
    static int persistentCount = 0;

    ordinaryCount++;
    persistentCount++;

    cout << "Ordinary: " << ordinaryCount << ", Static: " << persistentCount << endl;
}

// Returning a Reference to an Existing Object
int& getElement(int numbers[], int index) {
    return numbers[index];
}