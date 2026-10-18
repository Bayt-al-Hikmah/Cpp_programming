// Working with Operator Overloading

#include <iostream>
using namespace std;

class Point {
public:
    int x, y;

    Point(int a, int b) : x(a), y(b) {}

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    void display() const {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

int main() {

    // Creating Objects
    Point p1(3, 4);
    Point p2(2, 5);

    // Adding Points
    Point p3 = p1 + p2;

    // Displaying the Result
    p3.display();

    return 0;
}