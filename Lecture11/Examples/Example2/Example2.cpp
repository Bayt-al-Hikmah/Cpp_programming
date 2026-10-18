// File Opening Modes

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    // Open a file and replace its previous contents
    ofstream output("application.log");

    if (!output) {
        cerr << "Could not create the log file.\n";
        return 1;
    }

    output << "Application initialized.\n";

    output.close();


    // Open the same file in append mode
    ofstream logFile("application.log", ios::app);

    if (!logFile) {
        cerr << "Could not open the log file.\n";
        return 1;
    }

    // Add new records without deleting previous ones
    logFile << "Sensor connected.\n";
    logFile << "Measurement received.\n";

    logFile.close();


    // Read and display the complete log
    ifstream input("application.log");

    if (!input) {
        cerr << "Could not read the log file.\n";
        return 1;
    }

    string line;

    cout << "=== Application Log ===\n";

    while (getline(input, line)) {
        cout << line << '\n';
    }

    return 0;
}