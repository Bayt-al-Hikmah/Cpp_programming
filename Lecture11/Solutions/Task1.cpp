#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

int main() {
    int n;

    std::cout << "Enter the number of students: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Error: Invalid number of students.\n";
        return 1;
    }

    // Write student data to a file
    std::ofstream outFile("students.txt");

    if (!outFile) {
        std::cerr << "Error: Could not open students.txt for writing.\n";
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        std::string name;
        double grade;

        std::cout << "\nEnter name of student " << i + 1 << ": ";
        std::cin >> std::ws;
        std::getline(std::cin, name);

        std::cout << "Enter grade: ";
        if (!(std::cin >> grade) || grade < 0 || grade > 20) {
            std::cerr << "Error: Grade must be between 0 and 20.\n";
            return 1;
        }

        outFile << name << '\n' << grade << '\n';
    }

    outFile.close();

    if (!outFile) {
        std::cerr << "Error: Failed to write student data.\n";
        return 1;
    }

    // Read student data from the file
    std::ifstream inFile("students.txt");

    if (!inFile) {
        std::cerr << "Error: Could not open students.txt for reading.\n";
        return 1;
    }

    std::string name;
    double grade;
    double total = 0;
    double highest = std::numeric_limits<double>::lowest();
    double lowest = std::numeric_limits<double>::max();
    int count = 0;

    std::cout << "\n--- Student Records ---\n";

    while (std::getline(inFile, name)) {
        if (!(inFile >> grade)) {
            std::cerr << "Error: Invalid or incomplete student record.\n";
            return 1;
        }

        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (grade < 0 || grade > 20) {
            std::cerr << "Error: Invalid grade in file.\n";
            return 1;
        }

        std::cout << "Name: " << name
                  << ", Grade: " << grade << '\n';

        total += grade;

        if (grade > highest)
            highest = grade;

        if (grade < lowest)
            lowest = grade;

        ++count;
    }

    if (inFile.bad()) {
        std::cerr << "Error: Failed while reading student data.\n";
        return 1;
    }

    inFile.close();

    if (count == 0) {
        std::cerr << "Error: No student records found.\n";
        return 1;
    }

    double average = total / count;

    // Display results
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAverage grade: " << average << '\n';
    std::cout << "Highest grade: " << highest << '\n';
    std::cout << "Lowest grade: " << lowest << '\n';

    // Save the report
    std::ofstream report("report.txt");

    if (!report) {
        std::cerr << "Error: Could not open report.txt for writing.\n";
        return 1;
    }

    report << std::fixed << std::setprecision(2);
    report << "Student Grade Report\n";
    report << "--------------------\n";
    report << "Number of students: " << count << '\n';
    report << "Average grade: " << average << '\n';
    report << "Highest grade: " << highest << '\n';
    report << "Lowest grade: " << lowest << '\n';

    report.close();

    if (!report) {
        std::cerr << "Error: Failed to write report.txt.\n";
        return 1;
    }

    std::cout << "\nReport saved successfully to report.txt.\n";

    return 0;
}