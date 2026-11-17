#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>

struct Employee {
    int id;
    std::string name;
    double salary;
};

int main() {
    std::vector<std::string> records = {
        "101,Ahmed,25000",
        "102,Sara,32000",
        "103,Yacine,28000",
        "104,Lina,35000",
        "105,Omar,invalid"
    };

    std::vector<Employee> employees;

    double totalSalary = 0;
    Employee highestPaid{0, "", 0};

    for (const std::string& record : records) {
        std::stringstream ss(record);

        std::string idField;
        std::string nameField;
        std::string salaryField;
        std::string extraField;

        // Extract the three fields
        if (!std::getline(ss, idField, ',') ||
            !std::getline(ss, nameField, ',') ||
            !std::getline(ss, salaryField, ',')) {

            std::cerr << "Invalid record: " << record << '\n';
            continue;
        }

        // Reject unexpected additional fields
        if (std::getline(ss, extraField, ',')) {
            std::cerr << "Invalid record: " << record << '\n';
            continue;
        }

        try {
            std::size_t idPos = 0;
            std::size_t salaryPos = 0;

            int id = std::stoi(idField, &idPos);
            double salary = std::stod(salaryField, &salaryPos);

            // Ensure the entire field was converted
            if (idPos != idField.size() ||
                salaryPos != salaryField.size() ||
                id <= 0 ||
                nameField.empty() ||
                salary < 0 ||
                !std::isfinite(salary)) {

                throw std::invalid_argument("Invalid field value");
            }

            Employee employee{id, nameField, salary};

            employees.push_back(employee);
            totalSalary += salary;

            if (employees.size() == 1 ||
                salary > highestPaid.salary) {
                highestPaid = employee;
            }

            std::cout << "ID: " << employee.id
                      << ", Name: " << employee.name
                      << ", Salary: " << employee.salary
                      << '\n';

        } catch (const std::exception& e) {
            std::cerr << "Error processing record: "
                      << record << '\n';
            std::cerr << "Reason: " << e.what() << '\n';
        }
    }

    if (employees.empty()) {
        std::cout << "\nNo valid employee records found.\n";
        return 1;
    }

    double averageSalary = totalSalary / employees.size();

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\nAverage salary: "
              << averageSalary << '\n';

    std::cout << "Highest-paid employee: "
              << highestPaid.name << '\n';

    std::cout << "Employee ID: "
              << highestPaid.id << '\n';

    std::cout << "Salary: "
              << highestPaid.salary << '\n';

    return 0;
}