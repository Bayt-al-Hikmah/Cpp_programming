#include <iostream>
#include <cmath>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void display() const = 0;

    virtual ~Shape() {
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) {
        radius = r;
    }

    double area() const override {
        return 3.14159 * radius * radius;
    }

    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }

    void display() const override {
        cout << "Circle" << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) {
        length = l;
        width = w;
    }

    double area() const override {
        return length * width;
    }

    double perimeter() const override {
        return 2 * (length + width);
    }

    void display() const override {
        cout << "Rectangle" << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
};

class Triangle : public Shape {
private:
    double a;
    double b;
    double c;

public:
    Triangle(double side1, double side2, double side3) {
        a = side1;
        b = side2;
        c = side3;
    }

    double perimeter() const override {
        return a + b + c;
    }

    double area() const override {
        double p = perimeter() / 2;

        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    void display() const override {
        cout << "Triangle" << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
};

int main() {
    Circle circle(5);
    Rectangle rectangle(4, 6);
    Triangle triangle(3, 4, 5);

    Shape* shapes[3];

    shapes[0] = &circle;
    shapes[1] = &rectangle;
    shapes[2] = &triangle;

    double totalArea = 0;

    for (int i = 0; i < 3; i++) {
        shapes[i]->display();

        totalArea += shapes[i]->area();

        cout << endl;
    }

    cout << "Total area: " << totalArea << endl;

    return 0;
}