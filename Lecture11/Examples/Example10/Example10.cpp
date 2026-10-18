// Stream Manipulators: Aligning Columns

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {

    // Display the table header
    cout << left << setw(15) << "Product"
         << right << setw(12) << "Unit Price" << '\n';

    cout << string(27, '-') << '\n';

    // Display product records
    cout << left << setw(15) << "Notebook"
         << right << setw(12) << fixed << setprecision(2)
         << 3.5 << '\n';

    cout << left << setw(15) << "Keyboard"
         << right << setw(12) << 27.25 << '\n';

    cout << left << setw(15) << "Mouse"
         << right << setw(12) << 12.0 << '\n';

    return 0;
}