#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <string>

class BankAccount {
public:
    BankAccount(std::string number, std::string holder, double initialBalance)
        : accountNumber_(std::move(number)),
          accountHolder_(std::move(holder)),
          balance_(initialBalance) {
        if (accountNumber_.empty() || accountHolder_.empty() ||
            !std::isfinite(balance_) || balance_ < 0.0) {
            throw std::invalid_argument("Invalid account details or initial balance.");
        }
    }

    bool deposit(double amount) {
        if (!std::isfinite(amount) || amount <= 0.0) {
            return false;
        }
        balance_ += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (!std::isfinite(amount) || amount <= 0.0 || amount > balance_) {
            return false;
        }
        balance_ -= amount;
        return true;
    }

    bool transferTo(BankAccount& destination, double amount) {
        if (this == &destination) {
            return std::isfinite(amount) && amount > 0.0 && amount <= balance_;
        }
        if (!std::isfinite(amount) || amount <= 0.0 || amount > balance_) {
            return false;
        }
        balance_ -= amount;
        destination.balance_ += amount;
        return true;
    }

    double balance() const { return balance_; }

    void display() const {
        std::cout << "Account: " << accountNumber_
                  << " | Holder: " << accountHolder_
                  << " | Balance: " << balance_ << '\n';
    }

private:
    std::string accountNumber_;
    std::string accountHolder_;
    double balance_;
};

int main() {
    BankAccount account1("ACC001", "Ali", 1000.0);
    BankAccount account2("ACC002", "Sara", 500.0);

    account1.deposit(200.0);
    account1.withdraw(100.0);
    account1.transferTo(account2, 300.0);

    account1.display();
    account2.display();
}
