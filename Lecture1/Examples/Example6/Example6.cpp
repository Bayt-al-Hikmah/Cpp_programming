// User Input

#include <iostream>
using namespace std;

int main() {

    // Reading a single value
    int age;

    cout << "Enter your age: ";
    cin >> age;

    cout << "Your age is: " << age << endl;


    // Reading multiple values
    int year;
    double height;

    cout << "Enter your birth year and height: ";
    cin >> year >> height;

    cout << "Birth year: " << year << endl;
    cout << "Height: " << height << " meters" << endl;


    // Reading a string
    string name;

    cout << "Enter your name: ";
    cin >> name;

    cout << "Hello, " << name << "!" << endl;

    return 0;
}