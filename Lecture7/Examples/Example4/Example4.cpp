// Working with Sets and Maps

#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
    // A set stores unique values in sorted order
    set<int> grades = {15, 12, 18, 15, 10};

    cout << "Unique grades: ";

    for (int grade : grades)
        cout << grade << ' ';

    cout << "\n\n";

    // A map associates student IDs with names
    map<int, string> students;

    students[1001] = "Ali";
    students[1002] = "Sara";
    students[1003] = "Yacine";

    cout << "Student 1002: " << students[1002] << '\n';

    // Search for a student
    auto it = students.find(1003);

    if (it != students.end()) {
        cout << "Found student: " << it->second << '\n';
    } else {
        cout << "Student not found\n";
    }

    return 0;
}