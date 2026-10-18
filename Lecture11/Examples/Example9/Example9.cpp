// Stream Manipulators: Decimal Precision

#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    double price = 23.5;
    double temperature = 21.6789;

    // Default formatting
    cout << "Default price: " << price << '\n';

    // Display exactly two digits after the decimal point
    cout << fixed << setprecision(2);

    cout << "Formatted price: " << price << '\n';
    cout << "Temperature: " << temperature << '\n';

    return 0;
}