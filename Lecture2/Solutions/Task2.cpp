#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n, k;
    cout << "Enter number n : ";
    cin >> n;
    for(int i = 2 ; i <= n; i++){
        k = floor(sqrt(i));
        for (int j = k; j > 0; j--){
            if(i % j == 0 && j != 1){
                break;
            }else if (j == 1){
                cout << i << endl;
            }
        }

    }
    return 0;
}