// Working with Pointers and References
#include <iostream>
using namespace std;

int main() {
    // Address of a Variable
    int a = 5;
    cout << "Value of a: " << a << endl;
    cout << "Address of a: " << &a << endl;

    // Pointer
    int* ptr = &a;
    cout << "Pointer address: " << ptr << endl;
    cout << "Value through pointer: " << *ptr << endl;

    // Modifying Data Through a Pointer
    *ptr = 10;
    cout << "After modifying through pointer: " << a << endl;

    // nullptr
    int* empty = nullptr;
    if (empty != nullptr) {
        cout << "Value: " << *empty << endl;
    } else {
        cout << "Pointer is nullptr" << endl;
    }

    // Pointer Arithmetic
    int numbers[] = {10, 20, 30, 40};
    int* p = numbers;
    cout << "First element: " << *p << endl;
    cout << "Second element: " << *(p + 1) << endl;
    cout << "Third element: " << *(p + 2) << endl;
    cout << "Fourth element: " << *(p + 3) << endl;

    // Pointer Arithmetic with Increment
    p++;
    cout << "After p++: " << *p << endl;

    // Pointer to Constant
    int x = 10;
    int y = 20;
    const int* p1 = &x;
    cout << "Value through pointer to const: " << *p1 << endl;
    p1 = &y;
    cout << "After changing pointer: " << *p1 << endl;
    // *p1 = 30; // Error

    // Constant Pointer
    int value = 10;
    int* const p2 = &value;
    *p2 = 20;
    cout << "Value through constant pointer: " << value << endl;
    // p2 = &x; // Error

    // Constant Pointer to Constant
    const int z = 30;
    const int* const p3 = &z;
    cout << "Constant pointer to constant: " << *p3 << endl;
    // *p3 = 40; // Error
    // p3 = &x;   // Error


    // Reference
    int number = 5;
    int& ref = number;
    cout << "Number: " << number << endl;
    cout << "Reference: " << ref << endl;
    ref = 15;
    cout << "After modifying reference: " << number << endl;

    // Const Reference
    int original = 10;
    const int& constRef = original;
    cout << "Const reference: " << constRef << endl;

    // constRef = 20; // Error
    original = 20;
    cout << "After modifying original: " << constRef << endl;


    // Pointer vs Reference
    int first = 100;
    int second = 200;

    int* pointer = &first;
    int& reference = first;

    cout << "Pointer: " << *pointer << endl;
    cout << "Reference: " << reference << endl;

    pointer = &second;

    cout << "Pointer after changing target: " << *pointer << endl;
    cout << "Reference still refers to: " << reference << endl;

    return 0;
}