#include <cmath>
#include <iostream>
#include <stdexcept>

class Complex {
public:
    Complex(double real = 0.0, double imaginary = 0.0)
        : real_(real), imaginary_(imaginary) {}

    Complex operator+(const Complex& other) const {
        return {real_ + other.real_, imaginary_ + other.imaginary_};
    }

    Complex operator-(const Complex& other) const {
        return {real_ - other.real_, imaginary_ - other.imaginary_};
    }

    Complex operator*(const Complex& other) const {
        return {real_ * other.real_ - imaginary_ * other.imaginary_,
                real_ * other.imaginary_ + imaginary_ * other.real_};
    }

    Complex operator/(const Complex& other) const {
        const double denominator = other.real_ * other.real_ +
                                   other.imaginary_ * other.imaginary_;
        if (denominator == 0.0) {
            throw std::domain_error("Cannot divide by zero complex number.");
        }
        return {(real_ * other.real_ + imaginary_ * other.imaginary_) / denominator,
                (imaginary_ * other.real_ - real_ * other.imaginary_) / denominator};
    }

    bool operator==(const Complex& other) const {
        return real_ == other.real_ && imaginary_ == other.imaginary_;
    }

    double modulus() const { return std::hypot(real_, imaginary_); }

    friend std::ostream& operator<<(std::ostream& out, const Complex& value) {
        out << value.real_;
        if (value.imaginary_ >= 0.0) {
            out << " + " << value.imaginary_ << 'i';
        } else {
            out << " - " << -value.imaginary_ << 'i';
        }
        return out;
    }

private:
    double real_;
    double imaginary_;
};

int main() {
    const Complex first{4.0, 3.0};
    const Complex second{2.0, -1.0};

    std::cout << "First: " << first << '\n'
              << "Second: " << second << '\n'
              << "Sum: " << first + second << '\n'
              << "Difference: " << first - second << '\n'
              << "Product: " << first * second << '\n'
              << "Quotient: " << first / second << '\n'
              << "Modulus of first: " << first.modulus() << '\n'
              << std::boolalpha << "Equal: " << (first == second) << '\n';
}
