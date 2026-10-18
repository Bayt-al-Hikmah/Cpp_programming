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

    // Display the original measurements
    std::cout << "\nOriginal measurements: ";

    for (double value : measurements) {
        std::cout << value << " ";
    }

    // Copy the original measurements
    std::vector<double> cleanedMeasurements(measurements.size());

    std::copy(
        measurements.begin(),
        measurements.end(),
        cleanedMeasurements.begin()
    );

    // Remove negative measurements
    auto newEnd = std::remove_if(
        cleanedMeasurements.begin(),
        cleanedMeasurements.end(),
        [](double value) {
            return value < 0.0;
        }
    );

    cleanedMeasurements.erase(
        newEnd,
        cleanedMeasurements.end()
    );

    std::cout << "\nAfter removing negative values: ";

    for (double value : cleanedMeasurements) {
        std::cout << value << " ";
    }

    if (cleanedMeasurements.empty()) {
        std::cout << "\nNo valid measurements remain.\n";
        return 0;
    }

    // Normalize each measurement by dividing it by 10
    std::transform(
        cleanedMeasurements.begin(),
        cleanedMeasurements.end(),
        cleanedMeasurements.begin(),
        [](double value) {
            return value / 10.0;
        }
    );

    std::cout << "\nNormalized measurements: ";

    for (double value : cleanedMeasurements) {
        std::cout << value << " ";
    }

    // Sort measurements in ascending order
    std::sort(
        cleanedMeasurements.begin(),
        cleanedMeasurements.end()
    );

    std::cout << "\nSorted measurements: ";

    for (double value : cleanedMeasurements) {
        std::cout << value << " ";
    }

    // Reverse the order
    std::reverse(
        cleanedMeasurements.begin(),
        cleanedMeasurements.end()
    );

    std::cout << "\nReversed measurements: ";

    for (double value : cleanedMeasurements) {
        std::cout << value << " ";
    }

    // Calculate the sum
    double sum = std::accumulate(
        cleanedMeasurements.begin(),
        cleanedMeasurements.end(),
        0.0
    );

    // Calculate the average
    double average = sum / cleanedMeasurements.size();

    // Count measurements greater than 5
    int count = std::count_if(
        cleanedMeasurements.begin(),
        cleanedMeasurements.end(),
        [](double value) {
            return value > 5.0;
        }
    );

    std::cout << "\nSum: " << sum << "\n";
    std::cout << "Average: " << average << "\n";
    std::cout << "Measurements greater than 5: "
              << count << "\n";

    return 0;
}