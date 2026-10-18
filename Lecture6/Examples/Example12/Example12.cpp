// Working with std::expected
#include <expected>
#include <iostream>
#include <string>
using namespace std;

expected<int, string> validateNumber(int number) {
    if (number < 0 || number > 100) {
        return unexpected(string("Number must be between 0 and 100."));
    }

    return number;
}

int main() {
    int number;

    cout << "Enter a number: ";
    cin >> number;

    auto result = validateNumber(number);

    if (result) {
        cout << "Valid number: " << *result << '\n';
    }
    else {
        cout << "Error: " << result.error() << '\n';
    }

    return 0;
}