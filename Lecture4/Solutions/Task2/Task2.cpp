#include <iostream>
#include <vector>
#include "array_funcs.h"

int main() {
    int count{};
    std::cout << "Enter the number of elements: ";
    if (!(std::cin >> count) || count <= 0) {
        std::cerr << "The number of elements must be positive.\n";
        return 1;
    }

    std::vector<int> values(static_cast<std::size_t>(count));
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << "Enter element " << i + 1 << ": ";
        if (!(std::cin >> values[i])) {
            std::cerr << "Invalid input.\n";
            return 1;
        }
    }

    std::cout << "Largest: " << largest(values) << '\n'
              << "Smallest: " << smallest(values) << '\n'
              << "Average: " << average(values) << '\n';
}
