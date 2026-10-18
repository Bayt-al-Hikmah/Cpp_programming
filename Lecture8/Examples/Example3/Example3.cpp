#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    vector<double> prices = {100.0, 200.0, 150.0, 50.0};

    // Calculate the total price.
    double total = accumulate(
        prices.begin(),
        prices.end(),
        0.0
    );

    cout << "Total: " << total << '\n';

    // Copy prices into another vector.
    vector<double> copiedPrices;

    copy(
        prices.begin(),
        prices.end(),
        back_inserter(copiedPrices)
    );

    cout << "Copied prices: ";

    for (double price : copiedPrices) {
        cout << price << ' ';
    }

    cout << '\n';

    // Apply a 10% discount to every price.
    vector<double> discountedPrices(prices.size());

    transform(
        prices.begin(),
        prices.end(),
        discountedPrices.begin(),
        [](double price) {
            return price * 0.9;
        }
    );

    cout << "Discounted prices: ";

    for (double price : discountedPrices) {
        cout << price << ' ';
    }

    cout << '\n';

    // Calculate the total after discounts.
    double discountedTotal = accumulate(
        discountedPrices.begin(),
        discountedPrices.end(),
        0.0
    );

    cout << "Discounted total: " << discountedTotal << '\n';

    return 0;
}