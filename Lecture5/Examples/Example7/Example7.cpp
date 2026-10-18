// Working with Polymorphism

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void talk() const {
        cout << "Animal makes a sound." << endl;
    }

    virtual ~Animal() = default;
};

class Cat : public Animal {
public:
    void talk() const override {
        cout << "Meow!" << endl;
    }
};

class Dog : public Animal {
public:
    void talk() const override {
        cout << "Woof!" << endl;
    }
};

int main() {

    // Creating Objects
    Cat cat;
    Dog dog;

    // Using Base-Class Pointers
    Animal* a1 = &cat;
    Animal* a2 = &dog;

    // Calling Overridden Functions
    a1->talk();
    a2->talk();

    return 0;
}