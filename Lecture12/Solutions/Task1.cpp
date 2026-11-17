#include <array>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

int main() {
    std::vector<int> values(1'000'000);
    std::iota(values.begin(), values.end(), 1);

    constexpr std::size_t workerCount = 4;
    std::array<long long, workerCount> partialSums{};
    std::array<std::thread, workerCount> workers;

    for (std::size_t worker = 0; worker < workerCount; ++worker) {
        const std::size_t first = values.size() * worker / workerCount;
        const std::size_t last = values.size() * (worker + 1) / workerCount;

        workers[worker] = std::thread([&, worker, first, last] {
            long long localSum = 0;
            for (std::size_t i = first; i < last; ++i) {
                localSum += values[i];
            }
            partialSums[worker] = localSum;
        });
    }

    for (auto& worker : workers) {
        worker.join();
    }

    const long long parallelSum =
        std::accumulate(partialSums.begin(), partialSums.end(), 0LL);
    const long long sequentialSum =
        std::accumulate(values.begin(), values.end(), 0LL);

    std::cout << "Parallel sum:   " << parallelSum << '\n'
              << "Sequential sum: " << sequentialSum << '\n'
              << "Results match:  " << std::boolalpha
              << (parallelSum == sequentialSum) << '\n';
}
