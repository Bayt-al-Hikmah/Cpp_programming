#include <iostream>
#include <string>
#include <type_traits>

// 1. Function template with two potentially different types.
template <typename T, typename U>
auto convertAndCombine(T a, U b){
    return a + b;
}

// 2. Function template accepting any single type.
template <typename T>
void displayValue(const T& value){
    std::cout << value << '\n';
}

// 3. Class template storing a measurement.
template <typename T>
class Measurement{
private:
    T value;

public:
    explicit Measurement(T v) : value(v) {}

    const T& get() const{
        return value;
    }

    // 4. Member function template comparing different types.
    template <typename U>
    bool isGreaterThan(const U& other) const
        requires requires(const T& a, const U& b) {
            { a > b } -> std::convertible_to<bool>;
        }
    {
        return value > other;
    }
};

// 5. Class template with a default template argument.
template <typename T = int>
class Container{
private:
    T value;

public:
    explicit Container(T v) : value(v) {}

    void display() const
    {
        std::cout << "Container value: " << value << '\n';
    }
};

// 6. Function template requiring both arguments to have the same type.
template <typename T>
T sameTypeCombine(T a, T b){
    return a + b;
}

int main(){
    // Different argument types.
    auto result1 = convertAndCombine(10, 2.5);
    auto result2 = convertAndCombine(4.5f, 2.5);

    std::cout << "10 + 2.5 = " << result1 << '\n';
    std::cout << "4.5f + 2.5 = " << result2 << '\n';

    // Template argument deduction determines the return type.
    static_assert(std::is_same_v<decltype(result1), double>);
    static_assert(std::is_same_v<decltype(result2), double>);

    displayValue(42);
    displayValue(3.14);
    displayValue(std::string("Generic programming"));

    Measurement<int> m1(100);
    Measurement<double> m2(75.5);

    std::cout << std::boolalpha;

    std::cout << "100 > 90.5: " << m1.isGreaterThan(90.5) << '\n';

    std::cout << "75.5 > 80: " << m2.isGreaterThan(80) << '\n';

    // Default template argument: T = int.
    Container<> c1(50);
    c1.display();

    // Class template argument deduction (CTAD).
    Container c2(3.14);
    c2.display();

    // Additional challenge.
    // sameTypeCombine(10, 2.5); // Compilation error.

    // Explicitly select T = double.
    auto result3 = sameTypeCombine<double>(10, 2.5);

    std::cout << "Explicit same-type result: " << result3 << '\n';

    return 0;
}