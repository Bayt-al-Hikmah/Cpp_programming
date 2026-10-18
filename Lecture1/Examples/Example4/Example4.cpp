// Type Conversion and Type Casting

#include <iostream>
#include <string>
using namespace std;

int main() {

    // Implicit type conversion
    int age = 25;

    double value = age;

    cout << "Integer: " << age << endl;
    cout << "Converted to double: " << value << endl;


    // Explicit type casting
    double price = 19.99;

    int number = static_cast<int>(price);

    cout << "Double: " << price << endl;
    cout << "Converted to integer: " << number << endl;


    // Converting between char and int
    char letter = 'A';

    int code = letter;

    cout << "Character: " << letter << endl;
    cout << "Character code: " << code << endl;

    int value2 = 66;

    char letter2 = static_cast<char>(value2);

    cout << "Integer: " << value2 << endl;
    cout << "Converted to character: " << letter2 << endl;


    // String to number
    string text = "42";

    int number2 = stoi(text);

    cout << "String: " << text << endl;
    cout << "Converted to integer: " << number2 << endl;


    // Number to string
    int score = 100;

    string scoreText = to_string(score);

    cout << "Number: " << score << endl;
    cout << "Converted to string: " << scoreText << endl;


    return 0;
}