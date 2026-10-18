// Communication Between Threads: promise and future

#include <iostream>
#include <future>
#include <thread>
#include <utility>
using namespace std;

int main() {

    // Create a promise that will provide an integer
    promise<int> promiseObject;

    // Obtain the associated future
    future<int> result = promiseObject.get_future();

    // Create a worker thread
    thread worker(
        [p = move(promiseObject)]() mutable {

            cout << "Worker is calculating...\n";

            int calculatedValue = 6 * 7;

            // Send the result to the future
            p.set_value(calculatedValue);
        }
    );

    cout << "Main thread is waiting for the result.\n";

    // Wait for and retrieve the result
    cout << "Result: " << result.get() << '\n';

    // Ensure the worker has terminated
    worker.join();

    return 0;
}