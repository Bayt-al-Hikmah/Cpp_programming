#include <iostream>
#include <cmath>
using namespace std;

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double r = 0, double i = 0) {
        real = r;
        imaginary = i;
    }

    double getReal() const {
        return real;
    }

    double getImaginary() const {
        return imaginary;
    }

    Complex operator+(const Complex &other) const {
        return Complex(
            real + other.real,
            imaginary + other.imaginary
        );
    }

    Complex operator-(const Complex &other) const {
        return Complex(
            real - other.real,
            imaginary - other.imaginary
        );
    }

    Complex operator*(const Complex &other) const {
        return Complex(
            real * other.real - imaginary * other.imaginary,
            real * other.imaginary + imaginary * other.real
        );
    }

    Complex operator/(const Complex &other) const {
        double denominator =
            other.real * other.real +
            other.imaginary * other.imaginary;

        return Complex(
            (real * other.real + imaginary * other.imaginary)
                / denominator,

            (imaginary * other.real - real * other.imaginary)
                / denominator
        );
    }

    bool operator==(const Complex &other) const {
        return real == other.real &&
               imaginary == other.imaginary;
    }

    bool operator!=(const Complex &other) const {
        return !(*this == other);
    }

    double modulus() const {
        return sqrt(real * real + imaginary * imaginary);
    }

    friend ostream& operator<<(ostream &out, const Complex &c) {
        out << c.real;

        if (c.imaginary >= 0) {
            out << " + " << c.imaginary << "i";
        } else {
            out << " - " << -c.imaginary << "i";
        }

        return out;
    }
};

int main() {
    Complex c1(4, 3);
    Complex c2(2, -1);

    cout << "First number: " << c1 << endl;
    cout << "Second number: " << c2 << endl;

    cout << "Addition: " << c1 + c2 << endl;
    cout << "Subtraction: " << c1 - c2 << endl;
    cout << "Multiplication: " << c1 * c2 << endl;
    cout << "Division: " << c1 / c2 << endl;

    cout << "Modulus of first number: "
         << c1.modulus() << endl;

    cout << "Are they equal? "
         << (c1 == c2) << endl;

    cout << "Are they different? "
         << (c1 != c2) << endl;

    return 0;
}