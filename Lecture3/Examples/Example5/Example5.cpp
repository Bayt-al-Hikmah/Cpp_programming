// Working with Vectors

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {

    // Creating Vectors
    vector<int> numbers = {10, 20, 30, 40, 50};
    vector<double> prices = {10.5, 20.5, 30.5};
    vector<char> letters = {'A', 'B', 'C'};
    vector<string> names = {"Ali", "Alice", "Omar"};
    cout << "First number: " << numbers[0] << endl;
    cout << "First price: " << prices[0] << endl;
    cout << "First letter: " << letters[0] << endl;
    cout << "First name: " << names[0] << endl;

    // Empty Vector
    vector<int> values;
    cout << "Initial size: " << values.size() << endl;

    // Adding Elements
    values.push_back(10);
    values.push_back(20);
    values.push_back(30);
    cout << "After adding elements:" << endl;
    for (int value : values) {
        cout << value << endl;
    }

    // Accessing Elements
    cout << "First element: " << values[0] << endl;
    cout << "Second element: " << values[1] << endl;
    cout << "Third element: " << values[2] << endl;

    // Modifying Elements
    values[1] = 100;
    cout << "After modifying the second element:" << endl;
    for (int value : values) {
        cout << value << endl;
    }

    // Bounds-Checked Access
    cout << "Element at index 1: " << values.at(1) << endl;
    // values.at(10); // Throws std::out_of_range

    // Getting the Size
    cout << "Vector size: " << values.size() << endl;

    // Removing the Last Element
    values.pop_back();
    cout << "After pop_back:" << endl;
    for (int value : values) {
        cout << value << endl;
    }

    // Clearing a Vector
    values.clear();
    cout << "Size after clear: " << values.size() << endl;

    // Resizing a Vector
    vector<int> numbers2 = {10, 20, 30};
    numbers2.resize(5);
    cout << "After increasing size:" << endl;
    for (int number : numbers2) {
        cout << number << endl;
    }


    // Shrinking a Vector
    numbers2.resize(2);
    cout << "After decreasing size:" << endl;
    for (int number : numbers2) {
        cout << number << endl;
    }

    // Size vs Capacity
    vector<int> storage = {10, 20, 30};
    cout << "Size: " << storage.size() << endl;
    cout << "Capacity: " << storage.capacity() << endl;

    // Reserving Capacity
    storage.reserve(10);
    cout << "Size after reserve: " << storage.size() << endl;
    cout << "Capacity after reserve: " << storage.capacity() << endl;

    // Adding Elements Within Reserved Capacity
    storage.push_back(40);
    storage.push_back(50);
    cout << "After adding elements:" << endl;
    for (int number : storage) {
        cout << number << endl;
    }
    cout << "New size: " << storage.size() << endl;
    cout << "New capacity: " << storage.capacity() << endl;

    // Index-Based Loop
    vector<int> scores = {15, 18, 12, 16, 14};
    for (int i = 0; i < scores.size(); i++) {
        cout << "Score " << i << ": " << scores[i] << endl;
    }

    // Range-Based For Loop
    for (int score : scores) {
        cout << "Score: " << score << endl;
    }

    // Range-Based For with Reference
    for (int& score : scores) {
        score *= 2;
    }
    cout << "After multiplying scores:" << endl;
    for (const int& score : scores) {
        cout << score << endl;
    }

    // Vectors and Pointers
    vector<int> data = {10, 20, 30, 40, 50};
    int* ptr = data.data();
    cout << "First element through pointer: " << *ptr << endl;
    cout << "Second element through pointer: " << *(ptr + 1) << endl;
    cout << "Third element through pointer: " << *(ptr + 2) << endl;

    // Modifying Elements Through a Pointer
    *ptr = 100;
    cout << "First element after modification: " << data[0] << endl;

    // Iterating Through a Vector Using a Pointer
    cout << "Vector elements through pointer:" << endl;
    for (int i = 0; i < data.size(); i++) {
        cout << *(ptr + i) << endl;
    }

    // Pointer Invalidation
    int* oldPtr = data.data();
    cout << "First element before adding: " << *oldPtr << endl;
    data.reserve(data.capacity() + 100);
    // reserve() may reallocate the vector's storage.
    // oldPtr may now be invalid and must not be used.

    // Vector of Strings
    vector<string> students = {"Ali", "Alice", "Omar"};
    students.push_back("Sara");
    cout << "Students:" << endl;
    for (const string& student : students) {
        cout << student << endl;
    }

    // Modifying a String in a Vector
    students[0] = "Ahmed";
    cout << "First student: " << students[0] << endl;
    
    // Clearing a Vector
    students.clear();
    cout << "Students remaining: " << students.size() << endl;

    return 0;
}