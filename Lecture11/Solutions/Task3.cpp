#include <iostream>
#include <fstream>
#include <iomanip>
#include <type_traits>
#include <limits>

struct Product {
    int id;
    int quantity;
    double price;
};

int main() {
    static_assert(
        std::is_trivially_copyable_v<Product>,
        "Product must be trivially copyable."
    );

    Product products[] = {
        {101, 10, 25.50},
        {102, 5, 100.00},
        {103, 20, 12.75},
        {104, 8, 75.25},
        {105, 15, 40.00}
    };

    const std::size_t count =
        sizeof(products) / sizeof(products[0]);

    // Write products to the binary file
    std::ofstream outFile(
        "products.bin",
        std::ios::binary
    );

    if (!outFile) {
        std::cerr << "Error: Cannot open products.bin for writing.\n";
        return 1;
    }

    outFile.write(
        reinterpret_cast<const char*>(products),
        static_cast<std::streamsize>(sizeof(products))
    );

    if (!outFile) {
        std::cerr << "Error: Failed to write product records.\n";
        return 1;
    }

    outFile.close();

    if (!outFile) {
        std::cerr << "Error: Failed to close products.bin correctly.\n";
        return 1;
    }

    // Read products from the binary file
    std::ifstream inFile(
        "products.bin",
        std::ios::binary
    );

    if (!inFile) {
        std::cerr << "Error: Cannot open products.bin for reading.\n";
        return 1;
    }

    double totalValue = 0;
    Product mostExpensive{};
    bool foundProduct = false;

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\n--- Product Records ---\n";

    while (true) {
        Product p{};

        inFile.read(
            reinterpret_cast<char*>(&p),
            sizeof(Product)
        );

        std::streamsize bytesRead = inFile.gcount();

        if (bytesRead == 0) {
            if (inFile.bad()) {
                std::cerr << "Error: Failed while reading the file.\n";
                return 1;
            }

            if (inFile.eof())
                break;

            std::cerr << "Error: Unexpected read failure.\n";
            return 1;
        }

        if (bytesRead != static_cast<std::streamsize>(sizeof(Product))) {
            std::cerr << "Error: Incomplete product record.\n";
            return 1;
        }

        if (p.id <= 0 || p.quantity < 0 ||
            p.price < 0 || !std::isfinite(p.price)) {
            std::cerr << "Error: Invalid product data.\n";
            return 1;
        }

        std::cout << "ID: " << p.id
                  << ", Quantity: " << p.quantity
                  << ", Price: " << p.price
                  << ", Value: " << p.quantity * p.price
                  << '\n';

        totalValue += p.quantity * p.price;

        if (!foundProduct || p.price > mostExpensive.price) {
            mostExpensive = p;
            foundProduct = true;
        }
    }

    inFile.close();

    if (!inFile) {
        std::cerr << "Error: Failed to close products.bin correctly.\n";
        return 1;
    }

    std::cout << "\nTotal inventory value: "
              << totalValue << '\n';

    if (foundProduct) {
        std::cout << "Most expensive product ID: "
                  << mostExpensive.id << '\n';

        std::cout << "Highest unit price: "
                  << mostExpensive.price << '\n';
    }

    return 0;
}