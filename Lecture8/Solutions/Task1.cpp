#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;

    std::cout << "Enter the number of measurements: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Invalid number of measurements.\n";
        return 1;
    }

    std::vector<double> measurements(n);

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter measurement " << i + 1 << ": ";
        std::cin >> measurements[i];
    }

    // Display all measurements
    std::cout << "\nMeasurements: ";
    for (double value : measurements) {
        std::cout << value << " ";
    }

    // Find a specific measurement
    double target;
    std::cout << "\n\nEnter a measurement to search for: ";
    std::cin >> target;

    auto it = std::find(
        measurements.begin(),
        measurements.end(),
        target
    );

    if (it != measurements.end()) {
        std::cout << "Measurement found at index "
                  << std::distance(measurements.begin(), it)
                  << ".\n";
    } else {
        std::cout << "Measurement not found.\n";
    }

    // Count measurements greater than a threshold
    double threshold;
    std::cout << "\nEnter a threshold: ";
    std::cin >> threshold;

    int count = std::count_if(
        measurements.begin(),
        measurements.end(),
        [threshold](double value) {
            return value > threshold;
        }
    );

    std::cout << "Measurements greater than "
              << threshold << ": " << count << "\n";

    // Find the first measurement greater than the threshold
    auto first = std::find_if(
        measurements.begin(),
        measurements.end(),
        [threshold](double value) {
            return value > threshold;
        }
    );

    if (first != measurements.end()) {
        std::cout << "First measurement greater than threshold: "
                  << *first << "\n";
    } else {
        std::cout << "No measurement exceeds the threshold.\n";
    }

    // Sort measurements in ascending order
    std::sort(measurements.begin(), measurements.end());

    std::cout << "\nAscending order: ";
    for (double value : measurements) {
        std::cout << value << " ";
    }

    // Sort measurements in descending order using a lambda
    std::sort(
        measurements.begin(),
        measurements.end(),
        [](double a, double b) {
            return a > b;
        }
    );

    std::cout << "\nDescending order: ";
    for (double value : measurements) {
        std::cout << value << " ";
    }

    // Calculate the average
    double sum = std::accumulate(
        measurements.begin(),
        measurements.end(),
        0.0
    );

    double average = sum / measurements.size();

    std::cout << "\nAverage measurement: " << average << "\n";

    return 0;
}