#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;

    std::cout << "Enter the number of students: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Invalid number of students.\n";
        return 1;
    }

    std::vector<double> grades(n);

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter grade for student " << i + 1 << ": ";
        std::cin >> grades[i];

        if (grades[i] < 0 || grades[i] > 20) {
            std::cout << "Grades must be between 0 and 20.\n";
            return 1;
        }
    }

    // Count passing students
    double passingGrade = 10.0;

    int passingCount = std::count_if(
        grades.begin(),
        grades.end(),
        [passingGrade](double grade) {
            return grade >= passingGrade;
        }
    );

    std::cout << "\nNumber of passing students: "
              << passingCount << "\n";

    // Find the first excellent grade
    auto excellent = std::find_if(
        grades.begin(),
        grades.end(),
        [](double grade) {
            return grade >= 16.0;
        }
    );

    if (excellent != grades.end()) {
        std::cout << "First excellent grade: "
                  << *excellent << "\n";
    } else {
        std::cout << "No student received an excellent grade.\n";
    }

    // Increase each grade by 1 point, without exceeding 20
    std::transform(
        grades.begin(),
        grades.end(),
        grades.begin(),
        [](double grade) {
            return std::min(grade + 1.0, 20.0);
        }
    );

    std::cout << "\nGrades after bonus: ";

    for (double grade : grades) {
        std::cout << grade << " ";
    }

    // Remove failing grades
    auto newEnd = std::remove_if(
        grades.begin(),
        grades.end(),
        [passingGrade](double grade) {
            return grade < passingGrade;
        }
    );

    grades.erase(newEnd, grades.end());

    std::cout << "\nGrades after removing failures: ";

    for (double grade : grades) {
        std::cout << grade << " ";
    }

    if (!grades.empty()) {
        // Calculate the average of passing grades
        double total = std::accumulate(
            grades.begin(),
            grades.end(),
            0.0
        );

        double average = total / grades.size();

        std::cout << "\nAverage passing grade: "
                  << average << "\n";

        // Sort grades from highest to lowest
        std::sort(
            grades.begin(),
            grades.end(),
            [](double a, double b) {
                return a > b;
            }
        );

        std::cout << "Grades from highest to lowest: ";

        for (double grade : grades) {
            std::cout << grade << " ";
        }

        std::cout << "\n";
    } else {
        std::cout << "\nNo passing grades remain.\n";
    }

    return 0;
}