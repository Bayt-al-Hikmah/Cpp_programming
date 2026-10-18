#include <iostream>
#include <string>
using namespace std;

// One type for both arguments
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Two potentially different types
template <typename T, typename U>
auto addDifferent(T a, U b) {
    return a + b;
}

int main() {
    // Automatic template argument deduction
    cout << add(10, 20) << '\n';       // int
    cout << add(2.5, 3.5) << '\n';     // double

    // Explicitly specify the template argument
    cout << add<double>(10, 2) << '\n'; // 12

    // Different argument types
    cout << addDifferent(10, 2.5) << '\n'; // 12.5

    // Strings support operator+
    cout << add(string("Hello "), string("World")) << '\n';
}