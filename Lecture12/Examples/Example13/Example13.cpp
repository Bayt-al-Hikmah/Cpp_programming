// Asynchronous Execution: Processing a Vector

#include <iostream>
#include <future>
#include <vector>
#include <functional>
using namespace std;

// Calculate the sum of a collection
long long calculateTotal(const vector<int>& values) {

    long long total = 0;

    for (int value : values) {
        total += value;
    }

    return total;
}

int main() {

    vector<int> values = {10, 20, 30, 40, 50};

    // Pass a reference to the vector
    future<long long> result = async(
        launch::async,
        calculateTotal,
        cref(values)
    );

    cout << "Processing measurements...\n";

    // Retrieve the total
    cout << "Total: " << result.get() << '\n';

    return 0;
}