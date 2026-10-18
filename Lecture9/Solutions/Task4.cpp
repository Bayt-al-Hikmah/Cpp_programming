#include <iostream>
#include <string>
#include <utility>

// 1. Log an arbitrary number of values.
template <typename... Args>
void logValues(const Args&... args){
    ((std::cout << args << ' '), ...);
    std::cout << '\n';
}

// 2. Sum any number of values.
// The initial value allows an empty argument pack.
template <typename... Args>
auto sumValues(const Args&... args){
    return (0 + ... + args);
}

// 3. Count the arguments.
template <typename... Args>
constexpr std::size_t countArguments(const Args&...){
    return sizeof...(Args);
}

// 4. Check whether every argument is positive.
template <typename... Args>
constexpr bool allPositive(const Args&... args){
    return ((args > 0) && ...);
}

// 5. Product of an arbitrary number of values.
// The empty product is defined as 1.
template <typename... Args>
auto productValues(const Args&... args){
    return (1 * ... * args);
}

// 6. A function that receives one value.
template <typename T>
void printOne(const T& value){
    std::cout << value << ' ';
}

// 7. Demonstrate forwarding a parameter pack.
template <typename... Args>
void forwardToPrintOne(const Args&... args){
    (printOne(args), ...);
    std::cout << '\n';
}

int main(){
    logValues(10, 3.14, "hello", std::string("C++"));

    std::cout << "Sum: " << sumValues(10, 20, 3.5) << '\n';

    std::cout << "Empty sum: " << sumValues() << '\n';

    std::cout << "Argument count: " << countArguments(10, 2.5, "test") << '\n';

    std::cout << std::boolalpha;

    std::cout << "All positive: " << allPositive(1, 2, 3.5) << '\n';

    std::cout << "Contains non-positive value: " << allPositive(1, -2, 3) << '\n';

    // Empty conjunction is true.
    std::cout << "Empty allPositive: " << allPositive() << '\n';

    std::cout << "Product: " << productValues(2, 3, 4) << '\n';

    std::cout << "Empty product: " << productValues() << '\n';

    std::cout << "Forwarded values: ";
    forwardToPrintOne(10, 2.5, "world");

    return 0;
}