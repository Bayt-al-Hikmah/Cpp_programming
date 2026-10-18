// String Streams: Parsing CSV Records

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {

    string record = "101,Ahmed,25000";

    stringstream input(record);

    string idText;
    string name;
    string salaryText;

    // Extract fields separated by commas
    if (!getline(input, idText, ',') ||
        !getline(input, name, ',') ||
        !getline(input, salaryText)) {

        cerr << "Invalid employee record.\n";
        return 1;
    }

    // Convert numeric fields
    size_t position;
    int id;
    double salary;

    try {
        id = stoi(idText, &position);

        if (position != idText.size()) {
            cerr << "Invalid employee ID.\n";
            return 1;
        }

        salary = stod(salaryText, &position);

        if (position != salaryText.size()) {
            cerr << "Invalid salary.\n";
            return 1;
        }

    } catch (const exception&) {
        cerr << "Could not convert employee data.\n";
        return 1;
    }

    // Display the employee information
    cout << "Employee ID: " << id << '\n';
    cout << "Name: " << name << '\n';
    cout << "Salary: " << salary << '\n';

    return 0;
}