// Working with Memory Architecture and Dynamic Memory Allocation

#include <iostream>
using namespace std;

int global = 100;

// Static Storage
void counter() {
    static int count = 0;
    count++;
    cout << "Counter: " << count << endl;
}

int main() {

    // Stack / Automatic Storage
    int a = 5;
    int b = 10;

    cout << "Stack variable a: " << a << endl;
    cout << "Stack variable b: " << b << endl;

    // Static Storage
    cout << "Global variable: " << global << endl;
    counter();
    counter();
    counter();

    // Dynamic Memory Allocation
    int* p1 = new int;
    *p1 = 5;
    cout << "Dynamic value: " << *p1 << endl;
    delete p1;


    // Dynamic Memory Initialization
    int* p2 = new int(20);
    cout << "Initialized dynamic value: " << *p2 << endl;
    delete p2;

    // Value Initialization
    int* p3 = new int();
    cout << "Value-initialized int: " << *p3 << endl;
    *p3 = 30;
    cout << "After changing value: " << *p3 << endl;
    delete p3;

    // Memory Leak
    int* p4 = new int(40);
    cout << "Allocated value: " << *p4 << endl;
    // p4 = nullptr; 
    // Memory leak:
    // The allocated int still exists,
    // but its address has been lost.
    delete p4;

    // Dangling Pointer
    int* p5 = new int(50);
    cout << "Before delete: " << *p5 << endl;
    delete p5;

    // p5 is now a dangling pointer.
    // *p5 would be invalid.

    // Avoiding Dangling Pointers
    int* p6 = new int(60);
    cout << "Before delete: " << *p6 << endl;
    delete p6;
    p6 = nullptr;
    cout << "Pointer is now nullptr: " << (p6 == nullptr) << endl;

    // Double Deletion
    int* p7 = new int(70);
    cout << "Value before deletion: " << *p7 << endl;
    delete p7;
    p7 = nullptr;
    // Safe because p7 is nullptr.
    delete p7;
    cout << "Second delete was safe because pointer is nullptr." << endl;


    // Pointer and Dynamically Allocated Object
    int* p8 = new int(80);
    cout << "Pointer address: " << p8 << endl;
    cout << "Dynamic object value: " << *p8 << endl;
    delete p8;
    p8 = nullptr;

    return 0;
}