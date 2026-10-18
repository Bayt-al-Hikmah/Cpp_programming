// Working with stack unwinding and RAII
#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

class Logger {
public:
    Logger() {
        cout << "Logger created.\n";
    }

    ~Logger() {
        cout << "Logger destroyed.\n";
    }
};

void process() {
    Logger logger;
    auto value = make_unique<int>(42);

    cout << "Value: " << *value << '\n';

    throw runtime_error("Processing failed.");
}

int main() {
    try {
        process();
    }
    catch (const exception& e) {
        cout << "Caught exception: " << e.what() << '\n';
    }

    cout << "Program continues.\n";

    return 0;
}