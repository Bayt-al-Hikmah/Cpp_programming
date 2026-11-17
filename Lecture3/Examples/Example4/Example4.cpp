// Working with Strings

#include <iostream>
#include <string>
#include <string_view>

using namespace std;

void printString(std::string_view text);

int main() {

    // C-Style String
    char name[4] = {'A', 'l', 'i', '\0'};
    cout << "C-Style String: " << name << endl;

    // C-Style String with Null Terminator
    char city[] = "Algiers";
    cout << "City: " << city << endl;

    // Dynamically Allocated C String
    char* dynamicName = new char[4];
    dynamicName[0] = 'A';
    dynamicName[1] = 'l';
    dynamicName[2] = 'i';
    dynamicName[3] = '\0';
    cout << "Dynamic C String: " << dynamicName << endl;
    delete[] dynamicName;

    // Array of C-Style Strings
    char** names = new char*[3];
    names[0] = new char[4];
    names[1] = new char[6];
    names[2] = new char[5];

    // First Name
    names[0][0] = 'A';
    names[0][1] = 'l';
    names[0][2] = 'i';
    names[0][3] = '\0';

    // Second Name
    names[1][0] = 'A';
    names[1][1] = 'l';
    names[1][2] = 'i';
    names[1][3] = 'c';
    names[1][4] = 'e';
    names[1][5] = '\0';

    // Third Name
    names[2][0] = 'O';
    names[2][1] = 'm';
    names[2][2] = 'a';
    names[2][3] = 'r';
    names[2][4] = '\0';

    cout << "Names:" << endl;

    for (int i = 0; i < 3; i++) {
        cout << names[i] << endl;
    }
    // Deallocate Each String
    for (int i = 0; i < 3; i++) {
        delete[] names[i];
    }

    // Deallocate Array of Pointers
    delete[] names;

    // std::string Construction
    string first = "Ali";
    string second;
    second = "Alice";
    string stars(5, '*');
    string copy = first;

    cout << "First: " << first << endl;
    cout << "Second: " << second << endl;
    cout << "Stars: " << stars << endl;
    cout << "Copy: " << copy << endl;

    // Modifying Strings
    string name1 = "Ali";
    name1[0] = 'O';
    cout << "After modifying character: " << name1 << endl;
    name1 = "Alice";
    cout << "After assigning new text: " << name1 << endl;

    // Concatenating Strings
    string firstName = "Ali";
    string lastName = " Anunnaki";
    string fullName = firstName + lastName;
    cout << "Full Name: " << fullName << endl;
    fullName += " Developer";
    cout << "After appending: " << fullName << endl;

    // String Length
    string text = "Hello World";
    cout << "String: " << text << endl;
    cout << "Length: " << text.size() << endl;

    // Searching in a String
    size_t position = text.find("World");
    if (position != string::npos) {
        cout << "World found at position: " << position << endl;
    } else {
        cout << "World was not found" << endl;
    }

    // Searching for a Missing String
    position = text.find("C++");
    if (position != string::npos) {
        cout << "C++ found at position: " << position << endl;
    } else {
        cout << "C++ was not found" << endl;
    }

    // Extracting Substrings
    cout << "First Word: " << text.substr(0, 5) << endl;
    cout << "Second Word: " << text.substr(6, 5) << endl;

    // Modifying a String with Multiple Operations
    string message = "Hello";
    message += " World";
    message[0] = 'h';
    cout << "Message: " << message << endl;

    // std::string_view
    string original = "Hello from C++";
    string_view view = original;
    cout << "Original String: " << original << endl;
    cout << "String View: " << view << endl;

    // String View with Substrings
    string_view part = view.substr(6, 4);
    cout << "Substring View: " << part << endl;

    // String View as a Function Parameter
    printString(original);

    return 0;
}

// Function Using std::string_view
void printString(std::string_view text) {
    std::cout << "Function Output: " << text << '\n';
}