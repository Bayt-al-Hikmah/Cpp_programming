#include <functional>
#include <iostream>

using namespace std;

int subtract(int a, int b) {
    return a - b;
}

int main() {
    // Bind the second argument to 3.
    auto subtractThree = bind(
        subtract,
        placeholders::_1,
        3
    );

    cout << subtractThree(10) << '\n';
    cout << subtractThree(20) << '\n';

    // Reverse the argument order.
    auto reverseSubtract = bind(
        subtract,
        placeholders::_2,
        placeholders::_1
    );

    cout << reverseSubtract(3, 10) << '\n';

    return 0;
}