// User Output

#include <iostream>
using namespace std;

int main() {

    // Simple user output
    cout << "Hello" << "World" << endl;

    // Escape Sequences
    cout << "Hello\nWorld" << endl;        // New line
    cout << "Hello\tWorld" << endl;        // Tab
    cout << "He said: \"Hello!\"" << endl; // Double quote
    cout << "This is a backslash: \\" << endl;

    // Printing Variables
    int age = 25;
    char name[] = "Alice";

    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;

    // Printing Multiple Values
    int x = 10;
    int y = 20;

    cout << "x = " << x << ", y = " << y << endl;

    return 0;
}