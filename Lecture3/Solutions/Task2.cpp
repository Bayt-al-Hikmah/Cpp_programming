#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    int subjectCount{};
    std::cout << "Enter the number of subjects: ";
    if (!(std::cin >> subjectCount) || subjectCount <= 0) {
        std::cerr << "The number of subjects must be positive.\n";
        return 1;
    }

    std::vector<std::vector<double>> marks(static_cast<std::size_t>(subjectCount));
    double totalMarks = 0.0;
    std::size_t totalTests = 0;

    for (int subject = 0; subject < subjectCount; ++subject) {
        int testCount{};
        std::cout << "How many tests were taken in subject " << subject + 1 << "? ";
        if (!(std::cin >> testCount) || testCount <= 0) {
            std::cerr << "Each subject must have at least one test.\n";
            return 1;
        }

        auto& subjectMarks = marks[static_cast<std::size_t>(subject)];
        subjectMarks.resize(static_cast<std::size_t>(testCount));
        double subjectTotal = 0.0;

        for (int test = 0; test < testCount; ++test) {
            std::cout << "Enter mark " << test + 1 << " for subject " << subject + 1 << ": ";
            double mark{};
            if (!(std::cin >> mark) || mark < 0.0 || mark > 20.0) {
                std::cerr << "Enter a valid mark between 0 and 20.\n";
                return 1;
            }
            subjectMarks[static_cast<std::size_t>(test)] = mark;
            subjectTotal += mark;
            totalMarks += mark;
            ++totalTests;
        }

        std::cout << "Subject " << subject + 1 << " marks: ";
        for (double mark : subjectMarks) {
            std::cout << mark << ' ';
        }
        std::cout << "| Average: " << subjectTotal / subjectMarks.size() << '\n';
    }

    std::cout << std::fixed << std::setprecision(2)
              << "Overall average: " << totalMarks / static_cast<double>(totalTests) << '\n';
}
