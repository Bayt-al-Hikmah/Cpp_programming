#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Counter {
public:
    void increment() {
        const std::lock_guard<std::mutex> lock(mutex_);
        ++value_;
    }

    int value() const {
        const std::lock_guard<std::mutex> lock(mutex_);
        return value_;
    }

private:
    mutable std::mutex mutex_;
    int value_ = 0;
};

int main() {
    Counter counter;
    constexpr int threadCount = 8;
    constexpr int incrementsPerThread = 100'000;

    std::vector<std::thread> workers;
    workers.reserve(threadCount);

    for (int i = 0; i < threadCount; ++i) {
        workers.emplace_back([&counter] {
            for (int j = 0; j < incrementsPerThread; ++j) {
                counter.increment();
            }
        });
    }

    for (auto& worker : workers) {
        worker.join();
    }

    std::cout << "Final counter value: " << counter.value() << '\n';
}
