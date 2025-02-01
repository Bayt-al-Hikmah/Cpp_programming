#include <iostream>
using namespace std;

int main(){
    float **subjects,sum = 0,avg = 0 ;
    int l, k;
    int *subjects_tests_number;
    int total_test_numbers = 0;
    cout << "Enter number of subjects : ";
    cin >> l;
    subjects = new float*[l];
    subjects_tests_number = new int[l];
    for (int i = 0; i < l; i++){
        cout << "Enter How many test subject " << i + 1 << " have: ";
        cin >> k;
        *(subjects + i) = new float[k];
        *(subjects_tests_number + i) = k;
        for (int j = 0; j < k; j++){
            cout << "Enter test " << j + 1 << " of subject " << i + 1 << " grade: ";
            cin >> *(*(subjects + i) + j);
        }
    }
    for (int i = 0; i < l; i++){
        avg = 0;
        cout << "Subject " << i + 1 << " tests marks and average :\n";
        for (int j = 0; j < *(subjects_tests_number + i); j++){
            cout << "Test " << j + 1 << " grade : " << *(*(subjects + i) + j) << endl;
            avg +=  *(*(subjects + i) + j) / *(subjects_tests_number + i);
            sum += *(*(subjects + i) + j);
            total_test_numbers++; 
        }
        delete[] *(subjects + i);
        cout << "The average of subject " << i + 1 << " is " << avg << endl;
    }
    avg = sum / total_test_numbers;
    cout << "The total average is " << avg << endl;
    delete[] subjects_tests_number;
    delete[] subjects;
    return 0;
}