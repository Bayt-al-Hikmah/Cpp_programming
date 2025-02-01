#include <iostream>
#include <vector>
#include <string>
using namespace std;

using Book= struct{
    string name;
    string author;
    int number_of_pages;
};

int main(){
    vector<Book> Library;
    Book tmp;
    int n;
    cout << "Enter number of Books you have : ";
    cin >> n;
    for(int i = 0; i < n; i++){
        cout << "Enter Book " << i + 1 << " name : ";
        cin >> tmp.name;
        cout << "Enter Book " << i + 1 << " author : ";
        cin >> tmp.author;
        cout << "Enter Book " << i + 1 << " pages numbers : ";
        cin >> tmp.number_of_pages;
        Library.push_back(tmp);
    }
    cout << "You have saved " << n << " Books\n";
    for(int i = 0; i < n; i++){
        cout << "Book " << i + 1 << " " << Library[i].name << " : by " << Library[i].author << " have " << Library[i].number_of_pages << " pages \n";
    }
    return 0;
}