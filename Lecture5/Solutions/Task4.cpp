#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace University {

class Person {
public:
    Person(std::string name, int age) : name_(std::move(name)), age_(age) {
        if (name_.empty() || age_ < 0) {
            throw std::invalid_argument("Invalid person details.");
        }
    }

    virtual void display(std::ostream& out) const {
        out << "Name: " << name_ << "\nAge: " << age_;
    }
    virtual ~Person() = default;

protected:
    std::string name_;
    int age_;
};

class Student : public Person {
public:
    Student(std::string name, int age, int id)
        : Person(std::move(name), age), id_(id) {
        if (id_ <= 0) {
            throw std::invalid_argument("Student ID must be positive.");
        }
        ++liveCount_;
    }

    Student(const Student& other)
        : Person(other), id_(other.id_), grades_(other.grades_) {
        ++liveCount_;
    }

    Student(Student&& other) noexcept
        : Person(std::move(other)), id_(other.id_), grades_(std::move(other.grades_)) {
        ++liveCount_;
    }

    Student& operator=(const Student&) = default;
    Student& operator=(Student&&) noexcept = default;

    ~Student() override { --liveCount_; }

    void addGrade(double grade) {
        if (grade < 0.0 || grade > 20.0) {
            throw std::invalid_argument("A grade must be between 0 and 20.");
        }
        grades_.push_back(grade);
    }

    double average() const {
        if (grades_.empty()) {
            return 0.0;
        }
        double total = 0.0;
        for (double grade : grades_) {
            total += grade;
        }
        return total / static_cast<double>(grades_.size());
    }

    int id() const { return id_; }

    static std::size_t liveCount() { return liveCount_; }

    bool operator==(const Student& other) const { return id_ == other.id_; }
    bool operator<(const Student& other) const { return average() < other.average(); }

    void display(std::ostream& out) const override {
        Person::display(out);
        out << "\nStudent ID: " << id_ << "\nGrades: ";
        for (double grade : grades_) {
            out << grade << ' ';
        }
        out << "\nAverage: " << average();
    }

    friend std::ostream& operator<<(std::ostream& out, const Student& student) {
        student.display(out);
        return out;
    }

private:
    int id_;
    std::vector<double> grades_;
    inline static std::size_t liveCount_ = 0;
};

class StudentManager {
public:
    void addStudent(const Student& student) {
        if (findStudent(student.id()) != nullptr) {
            throw std::invalid_argument("A student with this ID already exists.");
        }
        students_.push_back(student);
    }

    bool removeStudent(int id) {
        const auto oldSize = students_.size();
        std::erase_if(students_, [id](const Student& student) {
            return student.id() == id;
        });
        return students_.size() != oldSize;
    }

    Student* findStudent(int id) {
        const auto it = std::find_if(students_.begin(), students_.end(),
            [id](const Student& student) { return student.id() == id; });
        return it == students_.end() ? nullptr : &*it;
    }

    const Student* findStudent(int id) const {
        const auto it = std::find_if(students_.begin(), students_.end(),
            [id](const Student& student) { return student.id() == id; });
        return it == students_.end() ? nullptr : &*it;
    }

    void displayAll(std::ostream& out) const {
        for (const Student& student : students_) {
            out << student << "\n\n";
        }
    }

private:
    std::vector<Student> students_;
};

} // namespace University

int main() {
    using University::Student;
    using University::StudentManager;

    Student ali("Ali", 20, 101);
    ali.addGrade(16);
    ali.addGrade(18);
    ali.addGrade(14);

    Student sara("Sara", 21, 102);
    sara.addGrade(19);
    sara.addGrade(18);
    sara.addGrade(20);

    StudentManager manager;
    manager.addStudent(ali);
    manager.addStudent(sara);

    manager.displayAll(std::cout);

    if (const Student* found = manager.findStudent(102)) {
        std::cout << "Found student:\n" << *found << '\n';
    }

    std::cout << "Live Student objects: " << Student::liveCount() << '\n';
}
