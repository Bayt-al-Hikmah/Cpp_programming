#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Status {
    Active,
    Inactive,
    Faulty
};

struct Sensor {
    int id;
    string name;
    double measurement;
    Status status;
};

string statusToString(Status status) {
    switch (status) {
        case Status::Active:
            return "Active";
        case Status::Inactive:
            return "Inactive";
        case Status::Faulty:
            return "Faulty";
        default:
            return "Unknown";
    }
}

int main() {
    int numberOfSensors;

    cout << "How many sensors do you want to register? ";
    cin >> numberOfSensors;

    if (numberOfSensors <= 0) {
        cout << "The number of sensors must be positive.\n";
        return 1;
    }

    vector<Sensor> sensors;

    for (int i = 0; i < numberOfSensors; ++i) {
        Sensor sensor;
        int statusChoice;

        cout << "\n--- Sensor " << i + 1 << " ---\n";

        cout << "Enter sensor ID: ";
        cin >> sensor.id;

        cout << "Enter sensor name: ";
        cin >> sensor.name;

        cout << "Enter measurement value: ";
        cin >> sensor.measurement;

        cout << "Select sensor status:\n";
        cout << "1. Active\n";
        cout << "2. Inactive\n";
        cout << "3. Faulty\n";
        cout << "Enter your choice: ";
        cin >> statusChoice;

        switch (statusChoice) {
            case 1:
                sensor.status = Status::Active;
                break;
            case 2:
                sensor.status = Status::Inactive;
                break;
            case 3:
                sensor.status = Status::Faulty;
                break;
            default:
                cout << "Invalid choice. Setting status to Inactive.\n";
                sensor.status = Status::Inactive;
        }

        sensors.push_back(sensor);
    }

    cout << "\n========== SENSOR COLLECTION ==========\n";

    for (const Sensor& sensor : sensors) {
        cout << "\nID: " << sensor.id << '\n';
        cout << "Name: " << sensor.name << '\n';
        cout << "Measurement: " << sensor.measurement << '\n';
        cout << "Status: " << statusToString(sensor.status) << '\n';
    }

    return 0;
}