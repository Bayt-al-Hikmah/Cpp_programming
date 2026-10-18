#include <iostream>
using namespace std;

// Print any number of arguments
template <typename... Args>
void printAll(const Args&... args) {
    ((cout << args << ' '), ...);
    cout << '\n';
}

// Calculate the sum of any number of arguments
template <typename... Args>
auto sum(const Args&... args) {
    return (0 + ... + args);
}

int main() {
    printAll(10, 3.14, "Hello");

    cout << sum(1, 2, 3, 4, 5) << '\n';
    cout << sum(1.5, 2.5, 3.0) << '\n';

    // The initial value makes an empty pack valid.
    cout << sum() << '\n';
}