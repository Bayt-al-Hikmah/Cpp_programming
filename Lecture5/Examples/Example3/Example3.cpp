// Working with Constructors and Destructors

#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string brand;

public:
    Car(const string& b) : brand(b) {
        cout << brand << " created." << endl;
    }

    ~Car() {
        cout << brand << " destroyed." << endl;
    }

    void display() const {
        cout << "Brand: " << brand << endl;
    }
};

int main() {

    // Creating an Object
    Car car("Toyota");

    // Calling a Member Function
    car.display();

    return 0;
}