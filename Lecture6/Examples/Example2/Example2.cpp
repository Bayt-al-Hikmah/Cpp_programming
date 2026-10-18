// Working with scoped enumerations
#include <iostream>
using namespace std;

enum class TrafficLight : unsigned char {
    Red,
    Yellow,
    Green
};

int main() {
    TrafficLight light = TrafficLight::Green;

    switch (light) {
        case TrafficLight::Red:
            cout << "Stop!\n";
            break;

        case TrafficLight::Yellow:
            cout << "Prepare to stop.\n";
            break;

        case TrafficLight::Green:
            cout << "Go!\n";
            break;
    }

    int value = static_cast<int>(light);

    cout << "Underlying value: " << value << '\n';

    return 0;
}