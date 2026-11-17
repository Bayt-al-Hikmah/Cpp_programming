#include <iostream>

bool isPrime(int value) {
    if (value < 2) {
        return false;
    }

    for (int divisor = 2; divisor <= value / divisor; ++divisor) {
        if (value % divisor == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int limit{};
    std::cout << "Display prime numbers up to: ";
    if (!(std::cin >> limit) || limit < 2) {
        std::cout << "There are no prime numbers in this range.\n";
        return 0;
    }

    for (int number = 2; number <= limit; ++number) {
        if (isPrime(number)) {
            std::cout << number << '\n';
        }
    }
}
