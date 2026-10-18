#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

class MeasurementBatch {
private:
    std::vector<double> readings_;

public:
    // Construct from a vector by value.
    explicit MeasurementBatch(std::vector<double> readings)
        : readings_(std::move(readings)) {}

    // Copy constructor.
    MeasurementBatch(const MeasurementBatch&) = default;

    // Copy-assignment operator.
    MeasurementBatch& operator=(const MeasurementBatch&) = default;

    // Move constructor.
    MeasurementBatch(MeasurementBatch&& other) noexcept
        : readings_(std::move(other.readings_)) {}

    // Move-assignment operator.
    MeasurementBatch& operator=(MeasurementBatch&& other) noexcept {
        if (this != &other) {
            readings_ = std::move(other.readings_);
        }

        return *this;
    }

    std::size_t size() const noexcept {
        return readings_.size();
    }

    void display() const {
        std::cout << "Readings: ";

        for (double reading : readings_) {
            std::cout << reading << ' ';
        }

        std::cout << "\nCount: " << size() << "\n";
    }
};

int main() {
    std::cout << "=== Initial construction ===\n";

    MeasurementBatch first({20.1, 20.3, 20.5});

    first.display();

    std::cout << "\n=== Move construction ===\n";

    MeasurementBatch second(std::move(first));

    std::cout << "Second batch:\n";
    second.display();

    std::cout << "First batch count after move: "
              << first.size() << '\n';

    std::cout << "\n=== Move assignment ===\n";

    MeasurementBatch third({100.0, 200.0});

    std::cout << "Third batch before assignment:\n";
    third.display();

    third = std::move(second);

    std::cout << "Third batch after assignment:\n";
    third.display();

    std::cout << "Second batch count after move: "
              << second.size() << '\n';

    return 0;
}