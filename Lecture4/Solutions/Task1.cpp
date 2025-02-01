#include <iostream>
using namespace std;

int dec2bin(int n);

int main(){
    int d;
    cout << "Enter number : ";
    cin >> d;
    cout << dec2bin(d) << endl;
    return 0;
}

int dec2bin(int n){
    if (n == 0){
        return 0;
    }
    return n % 2 + 10 * dec2bin(n / 2);
}