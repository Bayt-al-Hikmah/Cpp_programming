// Concurrency: Creating and Joining Threads

#include <iostream>
#include <thread>
using namespace std;

// Function executed by the worker thread
void calculate() {

    cout << "Calculation started.\n";

    int result = 10 * 20;

    cout << "Result: " << result << '\n';
}

int main() {

    cout << "Main function started.\n";

    // Create a worker thread
    thread worker(calculate);

    cout << "Main thread is running.\n";

    // Wait for the worker to finish
    worker.join();

    cout << "Main function finished.\n";

    return 0;
}