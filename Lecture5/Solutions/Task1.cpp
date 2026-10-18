#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(string number, string holder, double initialBalance) {
        accountNumber = number;
        accountHolder = holder;
        balance = initialBalance;
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    string getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    void setAccountHolder(string accountHolder) {
        this->accountHolder = accountHolder;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    void transfer(BankAccount &destination, double amount) {
        if (amount <= balance) {
            balance -= amount;
            destination.balance += amount;
        } else {
            cout << "Insufficient balance for transfer." << endl;
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: " << balance << endl;
    }
};

int main() {
    BankAccount account1("ACC001", "Ali", 1000);
    BankAccount account2("ACC002", "Sara", 500);

    cout << "Initial accounts:" << endl;

    account1.display();
    cout << endl;

    account2.display();
    cout << endl;

    account1.deposit(200);
    account1.withdraw(100);
    account1.transfer(account2, 300);

    cout << "After transactions:" << endl;

    account1.display();
    cout << endl;

    account2.display();

    return 0;
}