#include <iostream>
#include <type_traits>
using namespace std;

template <typename T>
T doubleValue(T value) {
    static_assert(
        is_arithmetic_v<T>,
        "T must be an arithmetic type"
    );

    return value * 2;
}

int main() {
    cout << boolalpha;

    cout << is_integral_v<int> << '\n';    // true
    cout << is_integral_v<double> << '\n'; // false

    cout << is_pointer_v<int*> << '\n';    // true
    cout << is_same_v<int, int> << '\n';   // true

    cout << doubleValue(10) << '\n';
    cout << doubleValue(2.5) << '\n';

    // Uncomment to see a compile-time diagnostic:
    // doubleValue("Hello");
}