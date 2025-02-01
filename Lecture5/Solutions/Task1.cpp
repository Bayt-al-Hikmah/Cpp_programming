#include <iostream>
#include <string>

using namespace std;

class Bank{
    private :
    int account_number;
    string account_holder_name;
    float account_balance;
    public :
    Bank (int id, string name, float balance){
        account_number = id;
        account_holder_name = name;
        account_balance = balance;
    }
    void deposit(float amount){
        if(amount > 0){
           account_balance += amount ; 
           cout << account_holder_name  << " account new balance is " << account_balance << endl;

        }else{
            cout << "amount can't be negative" << endl;
        }
    }
    void withdraw(float amount){
        if(amount > 0){
           account_balance -= amount ; 
           cout << account_holder_name  << " account new balance is " << account_balance << endl;

        }else{
            cout << "amount can't be negative" << endl;
        }
    }
    float get_balance(){
        return account_balance;
    }
    void transfer(Bank &other,float amount){
        if(amount > 0){
           other.deposit(amount);
           this->withdraw(amount);

        }else{
            cout << "amount can't be negative" << endl;
        }
    }
    void display_info(){
        cout << "========================================" << endl;
        cout << "Account Number: " << account_number << endl;
        cout << "Account Holder: " << account_holder_name << endl;
        cout << "Balance: " << account_balance << endl;
    }


};
int main(){
    Bank  account1(1,"Ali",700);
    Bank  account2(1,"Cat",1200);
    account1.transfer(account2,500);
    account1.display_info();
    account2.display_info();
    return 0;
}