// Working with Containers and Iterators

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 18, 12, 16, 10};

    // Display grades using iterators
    for (auto it = grades.begin(); it != grades.end(); ++it) {
        cout << *it << ' ';
    }

    cout << '\n';

    // Access the first grade
    auto it = grades.begin();

    cout << "First grade: " << *it << '\n';

    // Move to the third grade
    it += 2;

    cout << "Third grade: " << *it << '\n';

    // Display the number of grades
    cout << "Number of grades: " << grades.size() << '\n';

    return 0;
}