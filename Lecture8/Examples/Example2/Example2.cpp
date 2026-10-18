#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 8, 19, 12, 16, 10};

    // Sort from smallest to largest.
    sort(grades.begin(), grades.end());

    cout << "Ascending: ";

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << '\n';

    // Sort from largest to smallest.
    sort(
        grades.begin(),
        grades.end(),
        [](int a, int b) {
            return a > b;
        }
    );

    cout << "Descending: ";

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << '\n';

    // Reverse the current order.
    reverse(grades.begin(), grades.end());

    cout << "Reversed: ";

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << '\n';

    return 0;
}