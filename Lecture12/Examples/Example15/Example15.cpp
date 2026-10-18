// Promise: Communicating Exceptions

#include <iostream>
#include <future>
#include <exception>
#include <stdexcept>
using namespace std;

int main() {

    promise<int> promiseObject;

    future<int> result = promiseObject.get_future();

    // Simulate a failed operation
    try {

        throw runtime_error("Calculation failed.");

    } catch (...) {

        // Store the current exception in the promise
        promiseObject.set_exception(current_exception());
    }

    // Retrieve the result or handle the exception
    try {

        int value = result.get();

        cout << "Result: " << value << '\n';

    } catch (const exception& error) {

        cout << "Task failed: " << error.what() << '\n';
    }

    return 0;
}