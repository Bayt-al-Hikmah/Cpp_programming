#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    int age;
    int id;
    double grade;
};

int main() {
    int numberOfStudents;
    vector<Student> students;

    // Ask how many students to register
    cout << "How many students do you want to register? ";
    cin >> numberOfStudents;

    // Input the details of each student
    for (int i = 0; i < numberOfStudents; i++) {
        Student student;

        cout << "\nEnter details for student " << i + 1 << ":\n";

        cout << "Name: ";
        getline(cin >> ws, student.name);

        cout << "Age: ";
        cin >> student.age;

        cout << "Student ID: ";
        cin >> student.id;

        cout << "Grade: ";
        cin >> student.grade;

        // Store the student in the vector
        students.push_back(student);
    }

    // Display the details of all students
    cout << "\n========== Student Records ==========\n";

    for (const Student& student : students) {
        cout << "\nName: " << student.name << '\n';
        cout << "Age: " << student.age << '\n';
        cout << "Student ID: " << student.id << '\n';
        cout << "Grade: " << student.grade << '\n';
    }

    return 0;
}