// Working with nested structures and pointers
#include <iostream>
#include <string>
using namespace std;

struct Address {
    string city;
    string street;
};

struct Student {
    string name;
    int age;
    Address address;
};

int main() {
    Student student{
        "Ali",
        23,
        {"Algiers", "Didouche Mourad"}
    };

    Student* ptr = &student;

    cout << "Name: " << ptr->name << '\n';
    cout << "City: " << ptr->address.city << '\n';
    cout << "Street: " << ptr->address.street << '\n';

    ptr->age = 24;

    cout << "Updated age: " << student.age << '\n';

    return 0;
}