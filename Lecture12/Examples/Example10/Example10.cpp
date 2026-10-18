// Asynchronous Execution: Concurrent Progress

#include <iostream>
#include <future>
using namespace std;

int calculateTotal() {

    int total = 0;

    for (int i = 1; i <= 1000000; i++) {
        total += i;
    }

    return total;
}

int main() {

    // Start the calculation
    future<int> result = async(
        launch::async,
        calculateTotal
    );

    // Perform other work
    cout << "Preparing the report...\n";
    cout << "Checking application settings...\n";

    // Retrieve the calculation result
    cout << "Total: " << result.get() << '\n';

    return 0;
}