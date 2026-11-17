#include <array>
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string studentName;
    std::array<double, 3> grades{};

    std::cout << "Enter the student's full name: ";
    std::getline(std::cin, studentName);
    if (studentName.empty()) {
        std::cerr << "The name cannot be empty.\n";
        return 1;
    }

    double total = 0.0;
    for (std::size_t i = 0; i < grades.size(); ++i) {
        std::cout << "Enter grade " << i + 1 << ": ";
        if (!(std::cin >> grades[i]) || grades[i] < 0.0 || grades[i] > 20.0) {
            std::cerr << "Enter a valid grade between 0 and 20.\n";
            return 1;
        }
        total += grades[i];
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nStudent: " << studentName << '\n';
    for (std::size_t i = 0; i < grades.size(); ++i) {
        std::cout << "Grade " << i + 1 << ": " << grades[i] << '\n';
    }
    std::cout << "Average: " << total / grades.size() << '\n';
}
