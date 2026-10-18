// Working with Abstract Classes

#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;

    virtual ~Shape() = default;
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }
};

int main() {

    // Creating an Object
    Rectangle rectangle(5, 4);

    // Displaying the Area
    cout << "Area: " << rectangle.area() << endl;

    return 0;
}