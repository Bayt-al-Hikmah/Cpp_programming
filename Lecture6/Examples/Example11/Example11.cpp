// Working with std::optional
#include <iostream>
#include <optional>
using namespace std;

optional<double> findGrade(int studentID) {
    if (studentID == 1001) {
        return 16.5;
    }

    return nullopt;
}

int main() {
    int id;

    cout << "Enter student ID: ";
    cin >> id;

    optional<double> grade = findGrade(id);

    if (grade.has_value()) {
        cout << "Student grade: " << *grade << '\n';
    }
    else {
        cout << "Student not found.\n";
    }

    return 0;
}