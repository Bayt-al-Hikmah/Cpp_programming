#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

struct Product {
    std::string name;
    int id;
    int quantity;
    double price;
    bool available;
};

void printInvoice(std::ostream& out,
                  const std::vector<Product>& products) {

    out << "================ SHOP INVOICE ================\n\n";

    out << std::left
        << std::setw(16) << "Product"
        << std::setw(10) << "ID"
        << std::setw(10) << "Quantity"
        << std::setw(12) << "Unit Price"
        << std::setw(12) << "Available"
        << '\n';

    out << std::string(60, '-') << '\n';

    out << std::fixed << std::setprecision(2);

    for (const Product& p : products) {
        // Product name
        out << std::left << std::setw(16) << p.name;

        // ID with at least five characters
        out << std::setfill('0')
            << std::right << std::setw(5) << p.id
            << std::setfill(' ');

        // Quantity in decimal
        out << std::right << std::setw(5) << p.quantity;

        // Unit price with two decimal places
        out << std::setw(12) << p.price;

        // Availability as true or false
        out << std::boolalpha
            << std::setw(12) << p.available
            << std::noboolalpha
            << '\n';
    }

    out << "\n--- Quantity Representations ---\n";

    out << std::left
        << std::setw(16) << "Product"
        << std::right
        << std::setw(12) << "Decimal"
        << std::setw(12) << "Hexadecimal"
        << std::setw(12) << "Octal"
        << '\n';

    out << std::string(52, '-') << '\n';

    for (const Product& p : products) {
        out << std::left << std::setw(16) << p.name;

        out << std::right
            << std::dec << std::setw(12) << p.quantity
            << std::hex << std::setw(12) << p.quantity
            << std::oct << std::setw(12) << p.quantity
            << std::dec
            << '\n';
    }

    // Calculate the invoice total
    double total = 0;

    for (const Product& p : products) {
        if (p.available) {
            total += p.quantity * p.price;
        }
    }

    out << "\nInvoice total (available products): "
        << std::fixed << std::setprecision(2)
        << total << '\n';

    out << "===============================================\n";
}

int main() {
    std::vector<Product> products = {
        {"Keyboard", 1, 5, 25.50, true},
        {"Mouse", 12, 10, 12.75, true},
        {"Monitor", 103, 3, 180.00, true},
        {"Headphones", 24, 4, 45.99, false},
        {"USB Cable", 7, 20, 5.50, true}
    };

    // Display the invoice in the console
    printInvoice(std::cout, products);

    // Save the same invoice to a file
    std::ofstream file("invoice.txt");

    if (!file) {
        std::cerr << "Error: Cannot open invoice.txt for writing.\n";
        return 1;
    }

    printInvoice(file, products);

    file.close();

    if (!file) {
        std::cerr << "Error: Failed to save invoice.txt.\n";
        return 1;
    }

    std::cout << "\nInvoice saved successfully to invoice.txt.\n";

    return 0;
}