// Move Constructors and Move Assignment

#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class MeasurementBatch {
private:
    vector<double> readings;

public:
    // Constructor
    explicit MeasurementBatch(vector<double> values)
        : readings(move(values)) {
        cout << "Batch constructed.\n";
    }

    // Copy constructor
    MeasurementBatch(const MeasurementBatch&) = default;

    // Copy-assignment operator
    MeasurementBatch& operator=(const MeasurementBatch&) = default;

    // Move constructor
    MeasurementBatch(MeasurementBatch&& other) noexcept
        : readings(move(other.readings)) {
        cout << "Move constructor called.\n";
    }

    // Move-assignment operator
    MeasurementBatch& operator=(MeasurementBatch&& other) noexcept {
        if (this != &other) {
            readings = move(other.readings);
        }

        cout << "Move assignment called.\n";

        return *this;
    }

    // Display the number of readings
    void display() const {
        cout << "Number of readings: "
             << readings.size() << '\n';
    }
};

int main() {

    cout << "=== Create First Batch ===\n";

    MeasurementBatch first({20.1, 20.5, 21.0});

    first.display();

    cout << "\n=== Copy Construction ===\n";

    MeasurementBatch copied(first);

    copied.display();

    cout << "\n=== Move Construction ===\n";

    MeasurementBatch second(move(first));

    second.display();

    cout << "\n=== Move Assignment ===\n";

    MeasurementBatch third({100.0, 200.0});

    third.display();

    third = move(second);

    third.display();

    cout << "\n=== Moved-From Objects ===\n";

    first.display();
    second.display();

    return 0;
}