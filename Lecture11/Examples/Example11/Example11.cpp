// Stream Manipulators: Leading Zeros

#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    int id = 42;

    cout << "Original ID: " << id << '\n';

    // Display the ID using five characters
    cout << "Formatted ID: "
         << setfill('0')
         << setw(5)
         << id << '\n';

    // Restore the default fill character
    cout << setfill(' ');

    cout << "Another ID: "
         << setw(5)
         << 123 << '\n';

    return 0;
}