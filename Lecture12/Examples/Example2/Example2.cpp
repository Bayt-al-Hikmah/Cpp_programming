// Passing Arguments to a Thread

#include <iostream>
#include <thread>
using namespace std;

// Function executed by the worker
void processOrder(int orderId, double amount) {

    cout << "Processing order...\n";

    cout << "Order ID: " << orderId << '\n';
    cout << "Order amount: " << amount << '\n';
}

int main() {

    // Create a thread and pass its arguments
    thread worker(processOrder, 101, 249.99);

    // Wait for the order to be processed
    worker.join();

    cout << "Order processing completed.\n";

    return 0;
}