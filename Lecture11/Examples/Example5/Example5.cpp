// String Streams: Processing Multiple Values

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {

    string data = "21.5 22.0 21.8 22.4 23.1";

    stringstream input(data);

    double value;
    double total = 0.0;
    int count = 0;

    // Read each measurement
    while (input >> value) {

        total += value;
        count++;
    }

    // Check whether measurements were found
    if (count == 0) {
        cout << "No measurements found.\n";
        return 0;
    }

    // Calculate the average
    double average = total / count;

    cout << "Number of measurements: " << count << '\n';
    cout << "Total: " << total << '\n';
    cout << "Average: " << average << '\n';

    return 0;
}