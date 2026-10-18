// Working with Classes and Objects

#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int age;

    void display() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

int main() {

    // Creating Objects
    Student s1;
    Student s2;

    // Assigning Values
    s1.name = "Ali";
    s1.age = 20;

    s2.name = "Sara";
    s2.age = 22;

    // Calling Member Functions
    s1.display();
    s2.display();

    return 0;
}