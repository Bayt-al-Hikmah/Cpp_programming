// Working with error codes
#include <iostream>
using namespace std;

enum class DivideError {
    None,
    DivisionByZero
};

struct DivideResult {
    double value;
    DivideError error;
};

DivideResult divide(double a, double b) {
    if (b == 0) {
        return {0.0, DivideError::DivisionByZero};
    }

    return {a / b, DivideError::None};
}

int main() {
    DivideResult result = divide(10, 0);

    if (result.error == DivideError::None) {
        cout << "Result: " << result.value << '\n';
    }
    else {
        cout << "Error: Cannot divide by zero.\n";
    }

    return 0;
}