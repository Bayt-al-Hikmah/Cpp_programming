// Managing Vector Size and Capacity

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers;

    // Reserve storage for at least five elements
    numbers.reserve(5);

    cout << "Initial size: " << numbers.size() << '\n';
    cout << "Initial capacity: " << numbers.capacity() << '\n';

    // Add elements
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    cout << "\nAfter adding three elements:\n";
    cout << "Size: " << numbers.size() << '\n';
    cout << "Capacity: " << numbers.capacity() << '\n';

    // Increase the number of elements
    numbers.resize(5);

    cout << "\nAfter resize(5):\n";

    for (int n : numbers)
        cout << n << ' ';

    cout << "\nSize: " << numbers.size() << '\n';

    // Remove the last element
    numbers.pop_back();

    cout << "\nAfter pop_back():\n";
    cout << "Size: " << numbers.size() << '\n';

    return 0;
}