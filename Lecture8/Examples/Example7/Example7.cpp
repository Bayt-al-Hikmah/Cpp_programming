#include <iostream>

using namespace std;

int main() {
    int value = 10;

    // Capture value by copy and allow modification of the copy.
    auto increase = [value]() mutable {
        value++;
        return value;
    };

    cout << "First call: " << increase() << '\n';
    cout << "Second call: " << increase() << '\n';
    cout << "Third call: " << increase() << '\n';

    // The original variable has not changed.
    cout << "Original value: " << value << '\n';

    return 0;
}