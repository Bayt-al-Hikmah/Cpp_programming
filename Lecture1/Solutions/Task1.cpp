#include <iostream>
using namespace std;

#define PI 3.14

int main(){
    float s, r;
    cout << "Enter circle radius : ";
    cin >> r;
    s = r * r * PI;
    cout << "The surface of the circle is " << s << endl;
    return 0;
}



