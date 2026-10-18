// Working with Inheritance

#include <iostream>
#include <string>
using namespace std;

class Animal {
protected:
    string name;

public:
    Animal(const string& n) : name(n) {}

    void sleep() const {
        cout << name << " is sleeping." << endl;
    }
};

class Dog : public Animal {
public:
    Dog(const string& n) : Animal(n) {}

    void bark() const {
        cout << name << " says woof!" << endl;
    }
};

int main() {

    // Creating an Object
    Dog dog("Max");

    // Calling Inherited and Derived Functions
    dog.sleep();
    dog.bark();

    return 0;
}