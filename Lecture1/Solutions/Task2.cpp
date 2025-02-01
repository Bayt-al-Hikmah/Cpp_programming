#include <iostream>
using namespace std;

int main(){
    char name[10];
    float grades[3], avg;
    cout << "Enter student name : ";
    cin >> name;
    printf("Enter first grade : ");
    cin >> grades[0];
    printf("Enter second grade : ");
    cin >> grades[1];
    cout <<"Enter third grade : ";
    cin >> grades[2];
    avg = (grades[0] + grades[1] + grades[2]) / 3.0;
    cout << name << " have those marks " << grades[0] << ", " << grades[1] << ", " << grades[2] << " \n And this is his average " << avg << endl;
    return 0;
}