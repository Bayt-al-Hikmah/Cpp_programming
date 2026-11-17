#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

int main() {
    std::mutex mutex;
    std::condition_variable condition;
    int sharedValue = 0;
    bool valueReady = false;

    std::thread consumer([&] {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock, [&] { return valueReady; });
        const int receivedValue = sharedValue;
        lock.unlock();

        std::cout << "Consumer received: " << receivedValue << '\n';
    });

    std::thread producer([&] {
        {
            const std::lock_guard<std::mutex> lock(mutex);
            sharedValue = 42;
            valueReady = true;
        }
        condition.notify_one();
    });

    producer.join();
    consumer.join();
}
