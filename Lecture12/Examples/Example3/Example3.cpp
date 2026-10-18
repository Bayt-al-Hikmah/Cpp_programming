// Passing a Reference to a Thread

#include <iostream>
#include <thread>
#include <functional>
using namespace std;

// Modify the original variable
void increase(int& value) {

    value += 10;
}

int main() {

    int number = 5;

    cout << "Before thread: " << number << '\n';

    // Pass a reference to the original variable
    thread worker(increase, ref(number));

    worker.join();

    cout << "After thread: " << number << '\n';

    return 0;
}