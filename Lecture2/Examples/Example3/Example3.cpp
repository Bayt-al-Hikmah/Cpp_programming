// Working with Bitwise Operator

#include <iostream>
using namespace std;

int main() {

    int A = 5;  // 0101
    int B = 3;  // 0011

    cout << "A & B = " << (A & B) << endl;
    cout << "A | B = " << (A | B) << endl;
    cout << "A ^ B = " << (A ^ B) << endl;
    cout << "A << 1 = " << (A << 1) << endl;
    cout << "A >> 1 = " << (A >> 1) << endl;

    return 0;
}