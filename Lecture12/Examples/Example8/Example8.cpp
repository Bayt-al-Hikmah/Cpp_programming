// Synchronization: Using condition_variable

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

int main() {

    mutex reportMutex;
    condition_variable reportCondition;

    bool reportReady = false;

    // Worker waits until the report is ready
    auto workerFunction = [&] {

        unique_lock<mutex> lock(reportMutex);

        // Wait until the condition becomes true
        reportCondition.wait(lock, [&] {
            return reportReady;
        });

        cout << "The report is ready.\n";
    };

    // Start the worker
    thread worker(workerFunction);

    // Simulate preparing the report
    {
        lock_guard<mutex> lock(reportMutex);

        reportReady = true;
    }

    // Notify a waiting thread
    reportCondition.notify_one();

    // Wait for the worker to finish
    worker.join();

    cout << "Program completed.\n";

    return 0;
}