#include <iostream>
using namespace std;

int main(){
    char* str = new char[100];
    cout << "Enter string : ";
    cin >> str;
    for (int i = 0 ; ; i++){
        if(*(str + i) == '\0'){
            cout << "The length of the string is " << i << endl;
            break;
        }
    } 
    delete[] str;
    return 0;
}