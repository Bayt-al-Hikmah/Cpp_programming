// Asynchronous Execution: Exception Handling

#include <iostream>
#include <future>
#include <stdexcept>
using namespace std;

int divide(int a, int b) {

    if (b == 0) {
        throw runtime_error("Division by zero.");
    }

    return a / b;
}

int main() {

    // Launch a task that will fail
    future<int> result = async(
        launch::async,
        divide,
        10,
        0
    );

    try {

        // Retrieve the result
        int value = result.get();

        cout << "Result: " << value << '\n';

    } catch (const exception& error) {

        cout << "Task failed: " << error.what() << '\n';
    }

    return 0;
}