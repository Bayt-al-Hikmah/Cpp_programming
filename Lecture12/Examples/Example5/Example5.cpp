// Data Race: Incorrect Shared Counter

#include <iostream>
#include <thread>
using namespace std;

int main() {

    int counter = 0;

    // Both threads modify the same counter
    auto increment = [&] {

        for (int i = 0; i < 100000; i++) {
            ++counter;
        }

    };

    thread first(increment);
    thread second(increment);

    first.join();
    second.join();

    // The result is not guaranteed
    cout << "Final counter: " << counter << '\n';

    return 0;
}