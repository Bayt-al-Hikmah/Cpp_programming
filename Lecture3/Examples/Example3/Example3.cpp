// Working with Arrays

#include <iostream>
using namespace std;

int main() {

    // Fixed-Size Array
    int grades[5];

    grades[0] = 15;
    grades[1] = 18;
    grades[2] = 12;
    grades[3] = 16;
    grades[4] = 14;

    cout << "Grade 1: " << grades[0] << endl;
    cout << "Grade 2: " << grades[1] << endl;
    cout << "Grade 3: " << grades[2] << endl;
    cout << "Grade 4: " << grades[3] << endl;
    cout << "Grade 5: " << grades[4] << endl;

    // Array Initialization
    int numbers[5] = {10, 20, 30, 40, 50};
    cout << "First number: " << numbers[0] << endl;
    cout << "Last number: " << numbers[4] << endl;

    // Loop Through an Array
    for (int i = 0; i < 5; i++) {
        cout << "Number " << i << ": " << numbers[i] << endl;
    }

    // Array and Pointer
    int* p = numbers;

    cout << "First element through pointer: " << *p << endl;
    cout << "Second element through pointer: " << *(p + 1) << endl;
    cout << "Third element through pointer: " << *(p + 2) << endl;

    // Pointer Arithmetic
    p++;
    cout << "After p++: " << *p << endl;
    p += 2;
    cout << "After p += 2: " << *p << endl;

    // Modify Array Through Pointer
    int values[3] = {10, 20, 30};
    int* ptr = values;
    *ptr = 100;
    *(ptr + 1) = 200;
    *(ptr + 2) = 300;
    cout << "After modifying through pointer:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << values[i] << endl;
    }

    // Multidimensional Array
    int table[3][2] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    cout << "Table:" << endl;
    for (int row = 0; row < 3; row++) {
        for (int column = 0; column < 2; column++) {
            cout << table[row][column] << " ";
        }
        cout << endl;
    }

    // Accessing a Specific Element
    cout << "Row 0, Column 1: " << table[0][1] << endl;
    cout << "Row 2, Column 0: " << table[2][0] << endl;

    // Dynamic Array
    int* dynamicArray = new int[5];
    dynamicArray[0] = 10;
    dynamicArray[1] = 20;
    dynamicArray[2] = 30;
    dynamicArray[3] = 40;
    dynamicArray[4] = 50;
    cout << "Dynamic array:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << dynamicArray[i] << endl;
    }

    // Dynamic Array with Pointer Arithmetic
    cout << "Dynamic array through pointer:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << *(dynamicArray + i) << endl;
    }

    // Resize Dynamic Array
    int* oldArray = new int[5];

    for (int i = 0; i < 5; i++) {
        oldArray[i] = i + 1;
    }

    // Create a larger array
    int* newArray = new int[10];

    // Copy old values
    for (int i = 0; i < 5; i++) {
        newArray[i] = oldArray[i];
    }

    // Delete old array
    delete[] oldArray;

    // Point to the new array
    oldArray = newArray;

    // Add new values
    oldArray[5] = 6;
    oldArray[6] = 7;
    oldArray[7] = 8;
    oldArray[8] = 9;
    oldArray[9] = 10;
    cout << "Resized array:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << oldArray[i] << endl;
    }

    // Dynamic 2D Array
    int rows = 3;
    int columns = 4;
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
    }

    // Fill Dynamic 2D Array
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            matrix[row][column] = row * columns + column + 1;
        }
    }

    // Print Dynamic 2D Array
    cout << "Dynamic 2D array:" << endl;
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            cout << matrix[row][column] << " ";
        }
        cout << endl;
    }

    // Access Dynamic 2D Array
    cout << "Matrix[1][2]: " << matrix[1][2] << endl;

    // Deallocate Dynamic 2D Array
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    // Deallocate Dynamic Arrays
    delete[] dynamicArray;
    delete[] oldArray;

    return 0;
}