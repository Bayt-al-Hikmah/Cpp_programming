#include <cmath>
#include <iostream>
#include <memory>
#include <numbers>
#include <stdexcept>
#include <vector>

class Shape {
public:
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual ~Shape() = default;
};

std::ostream& operator<<(std::ostream& out, const Shape& shape) {
    shape.print(out);
    return out;
}

class Circle final : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {
        if (!std::isfinite(radius_) || radius_ <= 0.0) {
            throw std::invalid_argument("Circle radius must be positive.");
        }
    }

    double area() const override { return std::numbers::pi * radius_ * radius_; }
    double perimeter() const override { return 2.0 * std::numbers::pi * radius_; }
    void print(std::ostream& out) const override {
        out << "Circle(radius=" << radius_ << ", area=" << area()
            << ", perimeter=" << perimeter() << ')';
    }

private:
    double radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {
        if (!std::isfinite(width_) || !std::isfinite(height_) ||
            width_ <= 0.0 || height_ <= 0.0) {
            throw std::invalid_argument("Rectangle dimensions must be positive.");
        }
    }

    double area() const override { return width_ * height_; }
    double perimeter() const override { return 2.0 * (width_ + height_); }
    void print(std::ostream& out) const override {
        out << "Rectangle(width=" << width_ << ", height=" << height_
            << ", area=" << area() << ", perimeter=" << perimeter() << ')';
    }

private:
    double width_;
    double height_;
};

class Triangle : public Shape {
public:
    Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {
        if (!std::isfinite(a_) || !std::isfinite(b_) || !std::isfinite(c_) ||
            a_ <= 0.0 || b_ <= 0.0 || c_ <= 0.0 ||
            a_ + b_ <= c_ || a_ + c_ <= b_ || b_ + c_ <= a_) {
            throw std::invalid_argument("The side lengths do not form a valid triangle.");
        }
    }

    double perimeter() const override { return a_ + b_ + c_; }
    double area() const override {
        const double semiPerimeter = perimeter() / 2.0;
        return std::sqrt(semiPerimeter * (semiPerimeter - a_) *
                         (semiPerimeter - b_) * (semiPerimeter - c_));
    }
    void print(std::ostream& out) const override {
        out << "Triangle(sides=" << a_ << ", " << b_ << ", " << c_
            << ", area=" << area() << ", perimeter=" << perimeter() << ')';
    }

private:
    double a_;
    double b_;
    double c_;
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));

    double totalArea = 0.0;
    for (const auto& shape : shapes) {
        std::cout << *shape << '\n';
        totalArea += shape->area();
    }
    std::cout << "Total area: " << totalArea << '\n';
}
