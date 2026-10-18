// Working with Sequence Containers

#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    // Fixed-size array
    array<int, 3> fixed = {10, 20, 30};

    // Dynamic array
    vector<int> dynamic = {10, 20, 30};
    dynamic.push_back(40);

    // Double-ended queue
    deque<int> numbers = {20, 30};
    numbers.push_front(10);
    numbers.push_back(40);

    // Doubly linked list
    list<int> linked = {10, 20, 30};
    linked.push_back(40);

    // Singly linked list
    forward_list<int> forward = {10, 20, 30};
    forward.push_front(5);

    cout << "Array: ";
    for (int n : fixed)
        cout << n << ' ';

    cout << "\nVector: ";
    for (int n : dynamic)
        cout << n << ' ';

    cout << "\nDeque: ";
    for (int n : numbers)
        cout << n << ' ';

    cout << "\nList: ";
    for (int n : linked)
        cout << n << ' ';

    cout << "\nForward list: ";
    for (int n : forward)
        cout << n << ' ';

    cout << '\n';

    return 0;
}