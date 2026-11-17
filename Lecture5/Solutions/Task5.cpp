#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Robot {
public:
    Robot(int id, std::string name)
        : name_(std::move(name)), id_(id) {
        if (id_ <= 0 || name_.empty()) {
            throw std::invalid_argument("A robot needs a positive ID and a name.");
        }
    }
    int id() const { return id_; }
    virtual void operate() = 0;
    virtual void display(std::ostream& out) const {
        out << name_ << " (ID " << id_ << ')';
    }
    virtual ~Robot() = default;

protected:
    std::string name_;

private:
    int id_;
};

class Navigator {
public:
    void moveTo(double x, double y) { x_ = x; y_ = y; }
    void displayPosition(std::ostream& out) const {
        out << "Position: (" << x_ << ", " << y_ << ')';
    }
private:
    double x_ = 0.0;
    double y_ = 0.0;
};

class Communicator {
public:
    void connect() { connected_ = true; }
    void disconnect() { connected_ = false; }
    bool isConnected() const { return connected_; }
private:
    bool connected_ = false;
};

class MobileRobot final : public Robot, public Navigator, public Communicator {
public:
    using Robot::Robot;
    void operate() override { std::cout << name_ << " is moving.\n"; }
    void display(std::ostream& out) const override {
        Robot::display(out);
        out << " | ";
        displayPosition(out);
        out << " | Communication: " << (isConnected() ? "connected" : "disconnected");
    }
};

class ArmRobot final : public Robot {
public:
    using Robot::Robot;
    void operate() override { std::cout << name_ << " is performing an arm operation.\n"; }
};

class Sensor {
public:
    Sensor(std::string type, std::size_t count)
        : type_(std::move(type)), measurements_(count, 0) {
        if (type_.empty()) throw std::invalid_argument("Sensor type cannot be empty.");
    }
    void setMeasurement(std::size_t index, int value) {
        measurements_.at(index) = value;
    }
    void display(std::ostream& out) const {
        out << type_ << " sensor measurements: ";
        for (int value : measurements_) out << value << ' ';
        out << '\n';
    }
private:
    std::string type_;
    std::vector<int> measurements_;
};

class RobotManager {
public:
    void addRobot(std::unique_ptr<Robot> robot) {
        if (!robot) throw std::invalid_argument("Cannot add an empty robot.");
        robots_.push_back(std::move(robot));
    }
    void operateAll() {
        for (auto& robot : robots_) robot->operate();
    }
    void displayAll(std::ostream& out) const {
        for (const auto& robot : robots_) {
            robot->display(out);
            out << '\n';
        }
    }
private:
    std::vector<std::unique_ptr<Robot>> robots_;
};

int main() {
    RobotManager manager;
    auto mobile = std::make_unique<MobileRobot>(101, "Explorer");
    mobile->moveTo(10.0, 20.0);
    mobile->connect();
    manager.addRobot(std::move(mobile));
    manager.addRobot(std::make_unique<ArmRobot>(102, "Manipulator"));

    manager.displayAll(std::cout);
    manager.operateAll();

    Sensor sensor("Distance", 3);
    sensor.setMeasurement(0, 10);
    sensor.setMeasurement(1, 20);
    sensor.setMeasurement(2, 30);
    Sensor sensorCopy = sensor;
    sensorCopy.setMeasurement(0, 99);
    sensor.display(std::cout);
    sensorCopy.display(std::cout);
}
