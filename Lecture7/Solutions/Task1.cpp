#include <iostream>
#include <vector>
#include <algorithm>

int main(){

    std::vector<int> grades;
    int n, grade, target;

    std::cout << "Enter the number of students: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i){
        std::cout << "Enter grade " << i + 1 << ": ";
        std::cin >> grade;
        grades.push_back(grade);
    }

    std::cout << "\nGrades: ";

    for (auto it = grades.begin(); it != grades.end(); ++it){
        std::cout << *it << ' ';
    }

    std::sort(grades.begin(), grades.end());

    std::cout << "\nSorted grades: ";

    for (int grade : grades){
        std::cout << grade << ' ';
    }

    std::cout << "\nEnter a grade to search for: ";
    std::cin >> target;

    auto it = std::find(grades.begin(), grades.end(), target);

    if (it != grades.end())
        std::cout << "Grade found: " << *it << '\n';
    else
        std::cout << "Grade not found.\n";

    if (!grades.empty()){
        std::cout << "Minimum grade: " << *std::min_element(grades.begin(), grades.end()) << '\n';
        std::cout << "Maximum grade: " << *std::max_element(grades.begin(), grades.end()) << '\n';
        std::cout << "Number of grades: " << grades.size() << '\n';
    }

    return 0;
}