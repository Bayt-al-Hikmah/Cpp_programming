// Synchronization: Using mutex and lock_guard

#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

int main() {

    int counter = 0;

    // Protects access to the shared counter
    mutex counterMutex;

    // Operation performed by both threads
    auto increment = [&] {

        for (int i = 0; i < 100000; i++) {

            // Acquire the mutex
            lock_guard<mutex> lock(counterMutex);

            // Only one thread can modify the counter at a time
            ++counter;
        }

    };

    // Create two worker threads
    thread first(increment);
    thread second(increment);

    // Wait for both threads
    first.join();
    second.join();

    cout << "Final counter: " << counter << '\n';

    return 0;
}