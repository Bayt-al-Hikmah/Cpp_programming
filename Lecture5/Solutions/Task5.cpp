#include <iostream>
#include <string>
using namespace std;

namespace Robotics {

    class Device {
    private:
        int deviceID;

    public:
        Device(int id) {
            deviceID = id;
        }

        int getDeviceID() const {
            return deviceID;
        }

        virtual ~Device() {
        }
    };

    class Robot : virtual public Device {
    protected:
        string name;
        bool operating;

    public:
        Robot(int id, string n)
            : Device(id) {

            name = n;
            operating = false;
        }

        virtual void operate() = 0;

        virtual void display() const {
            cout << "Robot: " << name << endl;
            cout << "Device ID: " << getDeviceID() << endl;
            cout << "Operating: "
                 << (operating ? "Yes" : "No") << endl;
        }

        virtual ~Robot() {
        }
    };

    class Navigator : virtual public Device {
    protected:
        double x;
        double y;

    public:
        Navigator(int id)
            : Device(id) {

            x = 0;
            y = 0;
        }

        void move(double newX, double newY) {
            x = newX;
            y = newY;
        }

        void displayPosition() const {
            cout << "Position: ("
                 << x << ", " << y << ")" << endl;
        }
    };

    class Communicator : virtual public Device {
    protected:
        bool connected;

    public:
        Communicator(int id)
            : Device(id) {

            connected = false;
        }

        void connect() {
            connected = true;
        }

        void disconnect() {
            connected = false;
        }

        void communicate() const {
            if (connected) {
                cout << "Communication is active." << endl;
            } else {
                cout << "Communication is inactive." << endl;
            }
        }
    };

    class MobileRobot : public Robot,
                        public Navigator,
                        public Communicator {
    public:
        MobileRobot(int id, string n)
            : Device(id),
              Robot(id, n),
              Navigator(id),
              Communicator(id) {
        }

        void operate() override {
            operating = true;
            cout << name << " is operating." << endl;
        }

        void display() const override {
            Robot::display();
            displayPosition();
            communicate();
        }
    };

    class Sensor {
    private:
        int* measurements;
        int size;

    public:
        Sensor(int n) {
            size = n;
            measurements = new int[size];

            for (int i = 0; i < size; i++) {
                measurements[i] = 0;
            }
        }

        // Copy constructor
        Sensor(const Sensor &other) {
            size = other.size;
            measurements = new int[size];

            for (int i = 0; i < size; i++) {
                measurements[i] = other.measurements[i];
            }
        }

        // Assignment operator
        Sensor& operator=(const Sensor &other) {
            if (this != &other) {
                int* newMeasurements = new int[other.size];

                for (int i = 0; i < other.size; i++) {
                    newMeasurements[i] = other.measurements[i];
                }

                delete[] measurements;

                measurements = newMeasurements;
                size = other.size;
            }

            return *this;
        }

        ~Sensor() {
            delete[] measurements;
        }

        void setMeasurement(int index, int value) {
            measurements[index] = value;
        }

        void display() const {
            cout << "Sensor measurements: ";

            for (int i = 0; i < size; i++) {
                cout << measurements[i] << " ";
            }

            cout << endl;
        }
    };

    class RobotManager {
    private:
        Robot* robots[10];
        int count;

    public:
        RobotManager() {
            count = 0;
        }

        void addRobot(Robot* robot) {
            if (count < 10) {
                robots[count] = robot;
                count++;
            }
        }

        void operateAll() {
            for (int i = 0; i < count; i++) {
                robots[i]->operate();
            }
        }

        void displayAll() const {
            for (int i = 0; i < count; i++) {
                robots[i]->display();
                cout << endl;
            }
        }
    };

}

using namespace Robotics;

int main() {
    MobileRobot robot1(101, "Explorer");
    MobileRobot robot2(102, "Transporter");

    RobotManager manager;

    manager.addRobot(&robot1);
    manager.addRobot(&robot2);

    robot1.move(10, 20);
    robot1.connect();

    cout << "Robot information:" << endl;
    manager.displayAll();

    cout << "Operating robots:" << endl;
    manager.operateAll();

    cout << endl;

    Sensor sensor1(3);

    sensor1.setMeasurement(0, 10);
    sensor1.setMeasurement(1, 20);
    sensor1.setMeasurement(2, 30);

    Sensor sensor2 = sensor1;

    cout << "Original sensor:" << endl;
    sensor1.display();

    cout << "Copied sensor:" << endl;
    sensor2.display();

    sensor2.setMeasurement(0, 99);

    cout << "After modifying the copied sensor:" << endl;

    cout << "Original sensor:" << endl;
    sensor1.display();

    cout << "Copied sensor:" << endl;
    sensor2.display();

    return 0;
}