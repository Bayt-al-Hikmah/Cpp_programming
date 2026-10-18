// Working with structures and type aliases
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int age;
    int studentID;
    double grade;
};

using StudentRecord = Student;

int main() {
    StudentRecord student{
        .name = "Ali",
        .age = 23,
        .studentID = 1001,
        .grade = 16.5
    };

    cout << "Name: " << student.name << '\n';
    cout << "Age: " << student.age << '\n';
    cout << "Student ID: " << student.studentID << '\n';
    cout << "Grade: " << student.grade << '\n';

    return 0;
}