#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {12, 18, 9, 15, 18, 7, 16, 18};

    // Find the first occurrence of 18.
    auto it = find(grades.begin(), grades.end(), 18);

    if (it != grades.end()) {
        cout << "Found grade: " << *it << '\n';
        cout << "Position: " << it - grades.begin() << '\n';
    } else {
        cout << "Grade not found\n";
    }

    // Find the first grade greater than 15.
    auto highGrade = find_if(
        grades.begin(),
        grades.end(),
        [](int grade) {
            return grade > 15;
        }
    );

    if (highGrade != grades.end()) {
        cout << "First grade above 15: " << *highGrade << '\n';
    }

    // Count the number of occurrences of 18.
    int numberOfEighteens = count(
        grades.begin(),
        grades.end(),
        18
    );

    cout << "Number of 18s: " << numberOfEighteens << '\n';

    // Count grades greater than or equal to 10.
    int passingGrades = count_if(
        grades.begin(),
        grades.end(),
        [](int grade) {
            return grade >= 10;
        }
    );

    cout << "Passing grades: " << passingGrades << '\n';

    return 0;
}