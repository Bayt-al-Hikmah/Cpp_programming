// Working with unique_ptr

#include <iostream>
#include <memory>
#include <string>
using namespace std;

int main() {

    // Create a dynamically managed string
    unique_ptr<string> sensorName =
        make_unique<string>("Pressure Sensor");

    // Access the object
    cout << "Sensor name: " << *sensorName << '\n';

    // Access a member through the pointer
    cout << "Number of characters: "
         << sensorName->size() << '\n';

    // Check ownership
    if (sensorName) {
        cout << "The sensor name is available.\n";
    }

    // Release the current object and become empty
    sensorName.reset();

    if (!sensorName) {
        cout << "The pointer no longer owns an object.\n";
    }

    return 0;
}