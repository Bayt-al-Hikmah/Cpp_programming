#include <iostream>
#include <string>

using namespace std;

int main() {
    // Works with types that support addition to themselves.
    auto doubleValue = [](auto value) {
        return value + value;
    };

    cout << doubleValue(10) << '\n';
    cout << doubleValue(2.5) << '\n';
    cout << doubleValue(string("Hello")) << '\n';

    // Generic lambda with two parameters.
    auto add = [](auto a, auto b) {
        return a + b;
    };

    cout << add(10, 20) << '\n';
    cout << add(1.5, 2.5) << '\n';

    return 0;
}