// Working with Multiple Inheritance

#include <iostream>
using namespace std;

class Printer {
public:
    void print() const {
        cout << "Printing..." << endl;
    }
};

class Scanner {
public:
    void scan() const {
        cout << "Scanning..." << endl;
    }
};

class Machine : public Printer, public Scanner {
};

int main() {

    // Creating an Object
    Machine machine;

    // Calling Inherited Functions
    machine.print();
    machine.scan();

    return 0;
}