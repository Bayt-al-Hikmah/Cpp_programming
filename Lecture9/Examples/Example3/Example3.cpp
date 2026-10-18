#include <iostream>
using namespace std;

class Printer {
public:
    template <typename T>
    void print(const T& value) const {
        cout << value << '\n';
    }
};

int main() {
    Printer printer;

    printer.print(42);
    printer.print(3.14);
    printer.print("Hello");
}