#include <iostream>
#include <concepts>
using namespace std;

template <integral T>
void describe(T value) {
    cout << "Integral value: " << value << '\n';
}

template <floating_point T>
void describe(T value) {
    cout << "Floating-point value: " << value << '\n';
}

int main() {
    describe(10);
    describe(3.14);
}