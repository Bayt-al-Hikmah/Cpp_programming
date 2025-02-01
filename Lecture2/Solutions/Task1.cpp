#include <iostream>
#include <cmath>
using namespace std;

int main(){
    float a, b, c, x, x1, x2, delta;
    cout << "Enter the value of a : ";
    cin >> a;
    cout << "Enter the value of b : ";
    cin >> b;
    cout << "Enter the value of c : ";
    cin >> c;
    if (a == 0 && b == 0){
        cout << "There is no equation" << endl;
    }else if(a == 0 && b != 0){
        x = -c / b;
        cout << "Solution is :\n";
        cout << "x = ";
        cout << x << endl;
    }else{
        delta = b * b - 4 * a * c;
        if(delta < 0){
            cout << "No solution " << endl;

        }else if(delta == 0){
            x = -b / (2 * a);
            cout << "Solution is :\n";
            cout << "x = " ;
            cout<< x << endl;
        }else{
            x1 = (-b + sqrt(delta)) / (2 * a);
            x2 = (-b - sqrt(delta)) / (2 * a);
            cout << "Solutions are :\n";
            cout << "x1 = " ;
            cout<< x1 << endl;
            cout << "x2 = " ;
            cout << x2 << endl;
        }
    }
    return 0;
}