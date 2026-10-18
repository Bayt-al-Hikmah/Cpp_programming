#include <functional>
#include <iostream>

using namespace std;

// Ordinary function.
int multiply(int a, int b) {
    return a * b;
}

// Function object.
struct Add {
    int operator()(int a, int b) const {
        return a + b;
    }
};

int main() {
    // A callable that accepts two integers and returns an integer.
    function<int(int, int)> operation;

    // Store a lambda.
    operation = [](int a, int b) {
        return a + b;
    };

    cout << "Lambda addition: "
         << operation(10, 20) << '\n';

    // Store an ordinary function.
    operation = multiply;

    cout << "Function multiplication: "
         << operation(10, 20) << '\n';

    // Store a function object.
    operation = Add{};

    cout << "Function object addition: "
         << operation(10, 20) << '\n';

    // Replace the stored callable with another lambda.
    operation = [](int a, int b) {
        return a - b;
    };

    cout << "Lambda subtraction: "
         << operation(20, 5) << '\n';

    return 0;
}