// Synchronization: Minimizing the Critical Section

#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

int main() {

    int counter = 0;
    mutex counterMutex;

    auto increment = [&] {

        // Perform independent work locally
        int localCount = 0;

        for (int i = 0; i < 100000; i++) {
            ++localCount;
        }

        // Lock only when updating shared data
        lock_guard<mutex> lock(counterMutex);

        counter += localCount;
    };

    thread first(increment);
    thread second(increment);

    first.join();
    second.join();

    cout << "Final counter: " << counter << '\n';

    return 0;
}