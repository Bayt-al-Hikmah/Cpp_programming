#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;

    std::cout << "Enter the number of products: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Invalid number of products.\n";
        return 1;
    }

    std::vector<double> prices(n);

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter price of product " << i + 1 << ": ";
        std::cin >> prices[i];

        if (prices[i] < 0) {
            std::cout << "Prices cannot be negative.\n";
            return 1;
        }
    }

    // Count products with a specific price
    double targetPrice;

    std::cout << "\nEnter a price to count: ";
    std::cin >> targetPrice;

    int count = std::count(
        prices.begin(),
        prices.end(),
        targetPrice
    );

    std::cout << "Number of products with this price: "
              << count << "\n";

    // Copy prices into another vector
    std::vector<double> copiedPrices(prices.size());

    std::copy(
        prices.begin(),
        prices.end(),
        copiedPrices.begin()
    );

    std::cout << "\nCopied prices: ";
    for (double price : copiedPrices) {
        std::cout << price << " ";
    }

    // Apply a 10% discount
    std::transform(
        copiedPrices.begin(),
        copiedPrices.end(),
        copiedPrices.begin(),
        [](double price) {
            return price * 0.90;
        }
    );

    std::cout << "\nPrices after 10% discount: ";
    for (double price : copiedPrices) {
        std::cout << price << " ";
    }

    // Remove discounted prices below 10
    auto newEnd = std::remove_if(
        copiedPrices.begin(),
        copiedPrices.end(),
        [](double price) {
            return price < 10.0;
        }
    );

    copiedPrices.erase(newEnd, copiedPrices.end());

    std::cout << "\nPrices after removing values below 10: ";

    for (double price : copiedPrices) {
        std::cout << price << " ";
    }

    // Sort prices in ascending order
    std::sort(copiedPrices.begin(), copiedPrices.end());

    std::cout << "\nSorted prices: ";
    for (double price : copiedPrices) {
        std::cout << price << " ";
    }

    // Calculate the total
    double total = std::accumulate(
        copiedPrices.begin(),
        copiedPrices.end(),
        0.0
    );

    std::cout << "\nTotal of remaining prices: "
              << total << "\n";

    return 0;
}