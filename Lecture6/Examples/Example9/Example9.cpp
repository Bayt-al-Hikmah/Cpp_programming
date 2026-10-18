// Working with assertions
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    static_assert(sizeof(int) >= 2,
                  "int must be at least 2 bytes.");

    int age = 23;

    assert(age >= 0);

    cout << "Age: " << age << '\n';
    cout << "All assertions passed.\n";

    return 0;
}