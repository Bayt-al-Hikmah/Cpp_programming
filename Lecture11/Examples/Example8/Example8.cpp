// Binary File I/O: Writing and Reading Records

#include <iostream>
#include <fstream>
#include <cstdint>
#include <type_traits>
using namespace std;

struct Product {
    int32_t id;
    int32_t quantity;
    double price;
};

int main() {

    static_assert(
        is_trivially_copyable_v<Product>,
        "Product must be trivially copyable."
    );

    // Create a product
    Product original{101, 10, 49.99};


    // Write the product to a binary file
    ofstream output("product.bin", ios::binary);

    if (!output) {
        cerr << "Could not open the binary file for writing.\n";
        return 1;
    }

    output.write(
        reinterpret_cast<const char*>(&original),
        static_cast<streamsize>(sizeof(original))
    );

    if (!output) {
        cerr << "Failed to write the product.\n";
        return 1;
    }

    output.close();


    // Open the binary file for reading
    ifstream input("product.bin", ios::binary);

    if (!input) {
        cerr << "Could not open the binary file for reading.\n";
        return 1;
    }

    Product loaded{};

    // Read the product record
    input.read(
        reinterpret_cast<char*>(&loaded),
        static_cast<streamsize>(sizeof(loaded))
    );

    // Verify that the complete record was read
    if (!input ||
        input.gcount() != static_cast<streamsize>(sizeof(loaded))) {

        cerr << "Incomplete product record.\n";
        return 1;
    }

    // Display the restored product
    cout << "Product ID: " << loaded.id << '\n';
    cout << "Quantity: " << loaded.quantity << '\n';
    cout << "Price: " << loaded.price << '\n';

    return 0;
}