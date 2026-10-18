#include <iostream>
#include <string>
using namespace std;

namespace University {

    class Person {
    protected:
        string name;
        int age;

    public:
        Person(string n, int a) {
            name = n;
            age = a;
        }

        virtual void display() const {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
        }

        virtual ~Person() {
        }
    };

    class Student : public Person {
    private:
        int studentID;
        double grade1;
        double grade2;
        double grade3;

        static int studentCount;

    public:
        Student(string n, int a, int id,
                double g1, double g2, double g3)
            : Person(n, a) {

            studentID = id;
            grade1 = g1;
            grade2 = g2;
            grade3 = g3;

            studentCount++;
        }

        // Copy constructor
        Student(const Student &other)
            : Person(other.name, other.age) {

            studentID = other.studentID;
            grade1 = other.grade1;
            grade2 = other.grade2;
            grade3 = other.grade3;

            studentCount++;
        }

        // Assignment operator
        Student& operator=(const Student &other) {
            if (this != &other) {
                name = other.name;
                age = other.age;
                studentID = other.studentID;
                grade1 = other.grade1;
                grade2 = other.grade2;
                grade3 = other.grade3;
            }

            return *this;
        }

        ~Student() override {
            studentCount--;
        }

        double average() const {
            return (grade1 + grade2 + grade3) / 3;
        }

        int getStudentID() const {
            return studentID;
        }

        static int getStudentCount() {
            return studentCount;
        }

        void display() const override {
            Person::display();

            cout << "Student ID: " << studentID << endl;
            cout << "Average: " << average() << endl;
        }

        bool operator==(const Student &other) const {
            return studentID == other.studentID;
        }

        bool operator<(const Student &other) const {
            return average() < other.average();
        }

        friend ostream& operator<<(ostream &out,
                                   const Student &student) {
            out << "Name: " << student.name << endl;
            out << "Student ID: " << student.studentID << endl;
            out << "Average: " << student.average();

            return out;
        }
    };

    int Student::studentCount = 0;

    class StudentManager {
    private:
        Student* students[10];
        int count;

    public:
        StudentManager() {
            count = 0;
        }

        void addStudent(Student* student) {
            if (count < 10) {
                students[count] = student;
                count++;
            }
        }

        void displayAll() const {
            for (int i = 0; i < count; i++) {
                students[i]->display();
                cout << endl;
            }
        }

        Student* findStudent(int id) const {
            for (int i = 0; i < count; i++) {
                if (students[i]->getStudentID() == id) {
                    return students[i];
                }
            }

            return nullptr;
        }

        void displayBestStudent() const {
            if (count == 0) {
                cout << "No students available." << endl;
                return;
            }

            Student* best = students[0];

            for (int i = 1; i < count; i++) {
                if (*best < *students[i]) {
                    best = students[i];
                }
            }

            cout << "Best student:" << endl;
            best->display();
        }
    };

}

using namespace University;

int main() {
    Student student1("Ali", 20, 101, 16, 18, 14);
    Student student2("Sara", 21, 102, 19, 18, 20);
    Student student3("Amine", 19, 103, 12, 15, 14);

    StudentManager manager;

    manager.addStudent(&student1);
    manager.addStudent(&student2);
    manager.addStudent(&student3);

    cout << "All students:" << endl;
    manager.displayAll();

    cout << "Searching for student 102:" << endl;

    Student* found = manager.findStudent(102);

    if (found != nullptr) {
        cout << *found << endl;
    } else {
        cout << "Student not found." << endl;
    }

    cout << endl;

    manager.displayBestStudent();

    cout << endl;
    cout << "Number of Student objects: "
         << Student::getStudentCount() << endl;

    return 0;
}