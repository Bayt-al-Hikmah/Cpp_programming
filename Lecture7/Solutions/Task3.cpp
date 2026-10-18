#include <iostream>
#include <map>
#include <string>

int main(){

    std::map<int, std::string> students;
    int n, id;
    std::string name;

    std::cout << "Enter the number of students: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i){
        std::cout << "Enter student ID: ";
        std::cin >> id;

        std::cout << "Enter student name: ";
        std::cin >> name;

        students[id] = name;
    }

    std::cout << "\nStudent database:\n";

    for (const auto& student : students){
        std::cout << "ID: " << student.first << ", Name: " << student.second << '\n';
    }

    std::cout << "\nEnter a student ID to search for: ";
    std::cin >> id;

    auto it = students.find(id);

    if (it != students.end()){
        std::cout << "Student found: " << it->second << '\n';

        std::cout << "Enter the new name: ";
        std::cin >> name;

        it->second = name;

        std::cout << "Student name updated.\n";
    } else {
        std::cout << "Student not found.\n";
    }

    std::cout << "\nUpdated database:\n";

    for (const auto& student : students){
        std::cout << "ID: " << student.first << ", Name: " << student.second << '\n';
    }

    return 0;
}