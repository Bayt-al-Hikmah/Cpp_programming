#include <iostream>
#include <vector>

int main() {

    std::vector<int> numbers;

    std::cout << "Initial size: " << numbers.size() << '\n';

    std::cout << "Initial capacity: " << numbers.capacity() << '\n';

    numbers.reserve(5);

    std::cout << "\nAfter reserve(5):\n";
    std::cout << "Size: " << numbers.size() << '\n';
    std::cout << "Capacity: " << numbers.capacity() << '\n';

    for (int i = 1; i <= 5; ++i){
        numbers.push_back(i * 10);

        std::cout << "Added " << i * 10 << " | Size: " << numbers.size() << " | Capacity: " << numbers.capacity() << '\n';
    }

    auto it = numbers.begin();

    std::cout << "\nFirst element: " << *it << '\n';

    std::cout << "\nAdding more elements:\n";

    for (int i = 6; i <= 10; ++i){
        std::size_t oldCapacity = numbers.capacity();

        numbers.push_back(i * 10);

        std::cout << "Added " << i * 10 << " | Size: " << numbers.size() << " | Capacity: " << numbers.capacity();

        if (numbers.capacity() != oldCapacity){
            std::cout << " | Reallocation occurred";
        }

        std::cout << '\n';
    }

    std::cout << "\nAll elements: ";

    for (int number : numbers){
        std::cout << number << ' ';
    }

    std::cout << "\n\nResizing to 3 elements:\n";

    numbers.resize(3);

    std::cout << "Size: " << numbers.size() << '\n';
    std::cout << "Capacity: " << numbers.capacity() << '\n';

    std::cout << "\nEnter a minimum value to keep: ";

    int minimum;
    std::cin >> minimum;

    for (auto it = numbers.begin(); it != numbers.end();){
        if (*it < minimum){
            it = numbers.erase(it);
        } else {
            ++it;
        }
    }

    std::cout << "\nRemaining elements: ";

    for (int number : numbers) {
        std::cout << number << ' ';
    }

    std::cout << '\n';

    std::cout << "Final size: " << numbers.size() << '\n';
    std::cout << "Final capacity: " << numbers.capacity() << '\n';

    return 0;
}