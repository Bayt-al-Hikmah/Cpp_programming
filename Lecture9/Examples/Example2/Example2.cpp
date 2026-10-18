#include <iostream>
#include <string>
using namespace std;

template <typename T, typename U = int>
class Pair {
private:
    T first;
    U second;

public:
    Pair(T a, U b) : first(a), second(b) {}

    void display() const {
        cout << first << ", " << second << '\n';
    }
};

int main() {
    Pair<int> p1(10, 20);
    Pair<string, double> p2("Temperature", 36.5);

    p1.display();
    p2.display();
}