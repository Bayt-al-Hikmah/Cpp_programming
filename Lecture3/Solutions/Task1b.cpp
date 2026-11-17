#include <iostream>
#include <string>

int main() {
    std::string text;
    std::cout << "Enter a line: ";
    std::getline(std::cin, text);

    const char* current = text.c_str();
    std::size_t length = 0;
    while (*current != '\0') {
        ++current;
        ++length;
    }

    std::cout << "Length: " << length << '\n';
}
