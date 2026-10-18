// Working with exception safety
#include <iostream>
#include <stdexcept>
using namespace std;

void updateGrade(double& grade, double newGrade) {
    if (newGrade < 0 || newGrade > 20) {
        throw invalid_argument("Grade must be between 0 and 20.");
    }

    grade = newGrade;
}

int main() {
    double grade = 15.5;

    try {
        updateGrade(grade, 25.0);
    }
    catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << '\n';
    }

    cout << "Current grade: " << grade << '\n';

    return 0;
}