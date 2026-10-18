// Working with enumerations
#include <iostream>
using namespace std;

enum Day {
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

int main() {
    Day today = Friday;

    switch (today) {
        case Monday:
            cout << "Start of the week.\n";
            break;

        case Friday:
            cout << "Almost the weekend!\n";
            break;

        case Saturday:
        case Sunday:
            cout << "Enjoy your weekend!\n";
            break;

        default:
            cout << "Keep working!\n";
    }

    return 0;
}