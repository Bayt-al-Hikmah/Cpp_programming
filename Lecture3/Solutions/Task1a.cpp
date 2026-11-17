#include <cstddef>
#include <iostream>

int main() {
    constexpr std::size_t capacity = 256;
    char text[capacity]{};

    std::cout << "Enter a line (maximum 255 characters): ";
    std::cin.getline(text, static_cast<std::streamsize>(capacity));
    if (!std::cin) {
        std::cerr << "Input was too long or could not be read.\n";
        return 1;
    }

    const char* current = text;
    std::size_t length = 0;
    while (*current != '\0') {
        ++current;
        ++length;
    }

    std::cout << "Length: " << length << '\n';
}
