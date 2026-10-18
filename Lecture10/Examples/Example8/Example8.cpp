// Custom Deleter for a File

#include <cstdio>
#include <iostream>
#include <memory>
using namespace std;

// Define a custom cleanup function
struct FileCloser {
    void operator()(FILE* file) const noexcept {
        if (file != nullptr) {
            cout << "Closing file.\n";
            fclose(file);
        }
    }
};

int main() {

    // Define a unique_ptr with a custom deleter
    using FilePtr = unique_ptr<FILE, FileCloser>;

    // Open a file for writing
    FilePtr file(fopen("measurements.txt", "w"));

    if (!file) {
        cerr << "Could not open the file.\n";
        return 1;
    }

    cout << "File opened successfully.\n";

    // Write data to the file
    fputs("Temperature = 24.5\n", file.get());

    cout << "Data written to the file.\n";

    // The file closes automatically when file leaves scope
    return 0;
}