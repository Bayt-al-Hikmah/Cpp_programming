#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {5, 12, 8, 17, 9, 15, 6, 18};

    cout << "Original: ";

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << '\n';

    // Remove grades below 10.
    auto newEnd = remove_if(
        grades.begin(),
        grades.end(),
        [](int grade) {
            return grade < 10;
        }
    );

    // Actually remove the elements from the vector.
    grades.erase(newEnd, grades.end());

    cout << "After removal: ";

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << '\n';

    cout << "New size: " << grades.size() << '\n';

    return 0;
}