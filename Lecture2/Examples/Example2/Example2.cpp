// Working with Logical Operators

#include <iostream>
using namespace std;

int main() {

    int A = 5;
    int B = 6;

    cout << "B is greater than A AND B is less than 10: " << (B > A && B < 10) << endl;

    cout << "A is less than B OR A is positive: " << (A < B || A > 0) << endl;

    cout << "A is equal to B: " << !(A != B) << endl;

    return 0;
}