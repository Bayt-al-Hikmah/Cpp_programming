// Working with Encapsulation

#include <iostream>
using namespace std;

class BankAccount {
private:
    double balance;

public:
    BankAccount(double initialBalance) : balance(initialBalance) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    double getBalance() const {
        return balance;
    }
};

int main() {

    // Creating an Object
    BankAccount account(1000);

    // Depositing Money
    account.deposit(500);

    // Displaying Balance
    cout << "Balance: " << account.getBalance() << endl;

    // account.balance = 5000; // Error: balance is private

    return 0;
}