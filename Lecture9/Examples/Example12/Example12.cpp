#include <iostream>
using namespace std;

constexpr int square(int n) {
    return n * n;
}

// Must be evaluated at compile time
consteval int cube(int n) {
    return n * n * n;
}

// Initialized statically but remains mutable
constinit int counter = 0;

int main() {
    // Compile-time evaluation
    constexpr int a = square(5);

    // Runtime evaluation
    int n;
    cin >> n;

    int b = square(n);

    cout << a << '\n';
    cout << b << '\n';

    constexpr int result = cube(3);

    counter = 10;

    cout << result << '\n';
    cout << counter << '\n';

    // int n = 3;
    // int value = cube(n); // Error: not a constant expression
}