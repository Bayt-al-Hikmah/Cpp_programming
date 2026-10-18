// Asynchronous Execution: async and future

#include <iostream>
#include <future>
using namespace std;

// Function that performs a calculation
int calculateSquare(int value) {

    return value * value;
}

int main() {

    // Launch the calculation asynchronously
    future<int> result = async(
        launch::async,
        calculateSquare,
        12
    );

    cout << "The calculation has been requested.\n";

    // Retrieve the result
    cout << "Square: " << result.get() << '\n';

    return 0;
}