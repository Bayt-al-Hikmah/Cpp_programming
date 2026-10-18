#include <iostream>
#include <vector>
#include <algorithm>

class GreaterThan {
private:
    double threshold;

public:
    // Constructor
    GreaterThan(double value) : threshold(value) {}

    // Function call operator
    bool operator()(double value) const {
        return value > threshold;
    }
};

int main() {
    int n;

    std::cout << "Enter the number of values: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Invalid number of values.\n";
        return 1;
    }

    std::vector<double> values(n);

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter value " << i + 1 << ": ";
        std::cin >> values[i];
    }

    double threshold;

    std::cout << "\nEnter the threshold: ";
    std::cin >> threshold;

    // Create a function object
    GreaterThan condition(threshold);

    // Count values greater than the threshold
    int count = std::count_if(
        values.begin(),
        values.end(),
        condition
    );

    std::cout << "Number of values greater than "
              << threshold << ": " << count << "\n";

    // Find the first value greater than the threshold
    auto it = std::find_if(
        values.begin(),
        values.end(),
        condition
    );

    if (it != values.end()) {
        std::cout << "First value greater than threshold: "
                  << *it << "\n";
    } else {
        std::cout << "No value exceeds the threshold.\n";
    }

    // Display all values satisfying the condition
    std::cout << "Values greater than " << threshold << ": ";

    for (double value : values) {
        if (condition(value)) {
            std::cout << value << " ";
        }
    }

    std::cout << "\n";

    // Compare the function object with a lambda
    auto lambdaCondition = [threshold](double value) {
        return value > threshold;
    };

    int lambdaCount = std::count_if(
        values.begin(),
        values.end(),
        lambdaCondition
    );

    std::cout << "Count using the lambda: "
              << lambdaCount << "\n";

    return 0;
}