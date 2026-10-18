#include <iostream>

using namespace std;

int main() {
    int threshold = 15;

    // Capture threshold by value.
    auto checkByValue = [threshold](int grade) {
        return grade >= threshold;
    };

    // Capture threshold by reference.
    auto checkByReference = [&threshold](int grade) {
        return grade >= threshold;
    };

    cout << boolalpha;

    cout << "Initial threshold: " << threshold << '\n';

    cout << "Value capture, grade 12: "
         << checkByValue(12) << '\n';

    cout << "Reference capture, grade 12: "
         << checkByReference(12) << '\n';

    // Modify the original variable.
    threshold = 10;

    cout << "\nNew threshold: " << threshold << '\n';

    cout << "Value capture, grade 12: "
         << checkByValue(12) << '\n';

    cout << "Reference capture, grade 12: "
         << checkByReference(12) << '\n';

    return 0;
}