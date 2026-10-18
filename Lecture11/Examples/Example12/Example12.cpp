// Stream Manipulators: Generating a Formatted Invoice

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    int quantity;
    double price;
    bool available;
};

int main() {

    // Create product records
    Product products[] = {
        {1, "Notebook", 10, 3.50, true},
        {2, "Keyboard", 5, 27.25, true},
        {3, "Mouse", 8, 12.00, true},
        {4, "Monitor", 3, 150.75, false},
        {5, "USB Cable", 20, 4.99, true}
    };

    int count = sizeof(products) / sizeof(products[0]);


    // Open the invoice file
    ofstream file("invoice.txt");

    if (!file) {
        cerr << "Could not create the invoice.\n";
        return 1;
    }


    // Display and save the invoice header
    cout << "=== SHOP INVOICE ===\n\n";
    file << "=== SHOP INVOICE ===\n\n";


    // Configure common formatting
    cout << fixed << setprecision(2);
    file << fixed << setprecision(2);


    // Display column headings
    cout << left
         << setw(8) << "ID"
         << setw(15) << "Product"
         << right
         << setw(10) << "Quantity"
         << setw(12) << "Price"
         << setw(14) << "Available"
         << '\n';

    file << left
         << setw(8) << "ID"
         << setw(15) << "Product"
         << right
         << setw(10) << "Quantity"
         << setw(12) << "Price"
         << setw(14) << "Available"
         << '\n';


    cout << string(59, '-') << '\n';
    file << string(59, '-') << '\n';


    // Display each product
    for (const Product& product : products) {

        cout << setfill('0')
             << setw(5) << product.id;

        file << setfill('0')
             << setw(5) << product.id;


        // Restore space filling for the remaining columns
        cout << setfill(' ')
             << left << setw(3) << ""
             << setw(15) << product.name
             << right
             << setw(10) << product.quantity
             << setw(12) << product.price
             << setw(14) << boolalpha << product.available
             << '\n';

        file << setfill(' ')
             << left << setw(3) << ""
             << setw(15) << product.name
             << right
             << setw(10) << product.quantity
             << setw(12) << product.price
             << setw(14) << boolalpha << product.available
             << '\n';
    }


    // Calculate the total inventory value
    double total = 0.0;

    for (const Product& product : products) {
        total += product.quantity * product.price;
    }


    // Display the total
    cout << "\nTotal inventory value: " << total << '\n';

    file << "\nTotal inventory value: " << total << '\n';


    // Demonstrate different number bases
    int quantity = products[0].quantity;

    cout << "\nQuantity in decimal: " << dec << quantity << '\n';
    cout << "Quantity in hexadecimal: " << hex << quantity << '\n';
    cout << "Quantity in octal: " << oct << quantity << '\n';

    file << "\nQuantity in decimal: " << dec << quantity << '\n';
    file << "Quantity in hexadecimal: " << hex << quantity << '\n';
    file << "Quantity in octal: " << oct << quantity << '\n';


    // Check the final output operation
    file.close();

    if (!file) {
        cerr << "Error while saving the invoice.\n";
        return 1;
    }

    cout << dec;
    cout << "\nInvoice saved to invoice.txt.\n";

    return 0;
}