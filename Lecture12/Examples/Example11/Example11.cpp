// Future: Comparing wait() and get()

#include <iostream>
#include <future>
using namespace std;

int calculateValue() {

    return 100 * 5;
}

int main() {

    future<int> result = async(
        launch::async,
        calculateValue
    );

    // Wait for the task to finish
    result.wait();

    cout << "Calculation completed.\n";

    // Retrieve the result
    int value = result.get();

    cout << "Result: " << value << '\n';

    return 0;
}