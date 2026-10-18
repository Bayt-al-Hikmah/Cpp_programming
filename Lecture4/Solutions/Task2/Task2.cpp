#include <iostream>
#include "array_funcs.h"
using namespace std;

int main(){
    int size;
    cout << "Enter Number of Element : ";
    cin >> size;
    int* arr = new int[size];
    for (int i = 0; i < size; i++){
        cout << "Enter the " << i + 1 << "  Element : ";
        cin >> *(arr + i);
    }
    cout << "The Biggest Element is " << largest(size, arr) << endl;
    cout << "The Smallest Element is " << smallest(size, arr) << endl;
    cout << "The Average of The Element is " << avg(size, arr) << endl;
    delete[] arr;
    return 0;
}