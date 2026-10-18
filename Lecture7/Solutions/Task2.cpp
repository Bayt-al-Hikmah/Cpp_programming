#include <iostream>
#include <set>

int main(){
    std::set<int> products;
    int n, id, target;

    std::cout << "How many product IDs do you want to enter? ";
    std::cin >> n;

    for (int i = 0; i < n; ++i){
        std::cout << "Enter product ID: ";
        std::cin >> id;

        auto result = products.insert(id);

        if (result.second)
            std::cout << "Product added.\n";
        else
            std::cout << "Product ID already exists.\n";
    }

    std::cout << "\nProduct IDs: ";

    for (int product : products){
        std::cout << product << ' ';
    }

    std::cout << "\nNumber of unique products: " << products.size() << '\n';

    std::cout << "Enter an ID to search for: ";
    std::cin >> target;

    auto it = products.find(target);

    if (it != products.end())
        std::cout << "Product found: " << *it << '\n';
    else
        std::cout << "Product not found.\n";

    return 0;
}