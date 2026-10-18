// File Streams: Reading and Writing Files

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {

    vector<double> measurements = {23.5, 24.1, 22.8, 25.0};

    // Open a file for writing
    ofstream output("measurements.txt");

    if (!output) {
        cerr << "Error: Could not open the file.\n";
        return 1;
    }

    // Write measurements to the file
    for (double value : measurements) {
        output << value << '\n';
    }

    output.close();

    cout << "Measurements saved successfully.\n";


    // Open the file for reading
    ifstream input("measurements.txt");

    if (!input) {
        cerr << "Error: Could not read the file.\n";
        return 1;
    }

    vector<double> values;
    double value;

    // Read measurements from the file
    while (input >> value) {
        values.push_back(value);
    }

    if (!input.eof()) {
        cerr << "Error: Invalid data in the file.\n";
        return 1;
    }

    input.close();


    // Calculate statistics
    double total = 0.0;
    double highest = values[0];
    double lowest = values[0];

    for (double measurement : values) {

        total += measurement;

        if (measurement > highest) {
            highest = measurement;
        }

        if (measurement < lowest) {
            lowest = measurement;
        }
    }

    double average = total / values.size();


    // Display the results
    cout << "\n=== Measurement Report ===\n";

    for (double measurement : values) {
        cout << measurement << '\n';
    }

    cout << "Average: " << average << '\n';
    cout << "Highest: " << highest << '\n';
    cout << "Lowest: " << lowest << '\n';


    // Save the report to another file
    ofstream report("report.txt");

    if (!report) {
        cerr << "Error: Could not create the report.\n";
        return 1;
    }

    report << "=== Measurement Report ===\n";
    report << "Average: " << average << '\n';
    report << "Highest: " << highest << '\n';
    report << "Lowest: " << lowest << '\n';

    report.close();

    cout << "\nReport saved successfully.\n";

    return 0;
}