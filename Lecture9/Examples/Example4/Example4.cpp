#include <iostream>
using namespace std;

// General template
template <typename T>
struct TypeInfo {
    static void describe() {
        cout << "General type\n";
    }
};

// Full specialization for bool
template <>
struct TypeInfo<bool> {
    static void describe() {
        cout << "Boolean type\n";
    }
};

// Partial specialization for pointer types
template <typename T>
struct TypeInfo<T*> {
    static void describe() {
        cout << "Pointer type\n";
    }
};

int main() {
    TypeInfo<int>::describe();
    TypeInfo<bool>::describe();
    TypeInfo<double*>::describe();
}