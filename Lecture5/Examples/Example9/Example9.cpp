// Working with Namespaces

#include <iostream>
using namespace std;

namespace Math {
    int add(int a, int b) {
        return a + b;
    }
}

namespace Calculator {
    int add(int a, int b) {
        return a + b + 10;
    }
}

int main() {

    // Calling Functions from Different Namespaces
    cout << "Math: " << Math::add(3, 4) << endl;
    cout << "Calculator: " << Calculator::add(3, 4) << endl;

    return 0;
}