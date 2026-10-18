// Creating a Thread with a Lambda

#include <iostream>
#include <thread>
using namespace std;

int main() {

    // Create a worker using a lambda
    thread worker([] {

        cout << "Worker thread is running.\n";

        int result = 25 * 4;

        cout << "Calculation result: " << result << '\n';

    });

    cout << "Main thread is running.\n";

    // Wait for the worker
    worker.join();

    cout << "Worker thread completed.\n";

    return 0;
}