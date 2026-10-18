// student.cpp

#include <iostream>
#include "student.hpp"
using namespace std;

// Function Definition
void printStudent(const string& name, double first, double second, double third) {
    double average = calculateAverage(first, second, third);

    cout << "Student: " << name << endl;
    cout << "First Score: " << first << endl;
    cout << "Second Score: " << second << endl;
    cout << "Third Score: " << third << endl;
    cout << "Average: " << average << endl;
}