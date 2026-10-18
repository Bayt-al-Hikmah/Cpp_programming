#include <iostream>
#include <type_traits>
#include <string>

// 1. General type classifier.
template <typename T>
struct TypeClassifier{
    static constexpr const char* name = "General type";

    static void display(){
        std::cout << name
                  << " | Integral: " << std::boolalpha
                  << std::is_integral_v<T>
                  << " | Floating-point: "
                  << std::is_floating_point_v<T>
                  << '\n';
    }
};

// 2. Full specialization for bool.
template <>
struct TypeClassifier<bool>{
    static constexpr const char* name = "Boolean type";

    static void display()
    {
        std::cout << name << '\n';
    }
};

// 3. Partial specialization for pointer types.
template <typename T>
struct TypeClassifier<T*>{
    static constexpr const char* name = "Pointer type";

    static void display()
    {
        std::cout << name
                  << " | Points to: "
                  << TypeClassifier<T>::name
                  << '\n';
    }
};

// 4. Variable template for arithmetic classification.
template <typename T>
inline constexpr bool isArithmeticType =
    std::is_arithmetic_v<T>;

// 5. Conditional compile-time type selection.
template <typename T>
using NumericChoice =
    std::conditional_t<std::is_integral_v<T>, int, double>;

int main(){
    TypeClassifier<int>::display();
    TypeClassifier<double>::display();
    TypeClassifier<bool>::display();
    TypeClassifier<int*>::display();

    // 6. Remove reference qualifiers.
    using ReferenceType = int&;
    using NormalizedType = std::remove_reference_t<ReferenceType>;

    static_assert(std::is_same_v<NormalizedType, int>);

    std::cout << "Reference removed: " << std::is_same_v<NormalizedType, int> << '\n';

    // 7. Conditional type selection.
    static_assert(std::is_same_v<NumericChoice<int>, int>);
    static_assert(std::is_same_v<NumericChoice<double>, double>);

    std::cout << "NumericChoice<int> is int: " << std::is_same_v<NumericChoice<int>, int> << '\n';

    std::cout << "NumericChoice<double> is double: "<< std::is_same_v<NumericChoice<double>, double> << '\n';

    // 8. Compile-time validation of the variable template.
    static_assert(isArithmeticType<int>);
    static_assert(isArithmeticType<double>);
    static_assert(!isArithmeticType<bool*>);
    static_assert(!isArithmeticType<std::string>);

    std::cout << "int is arithmetic: " << isArithmeticType<int> << '\n';

    std::cout << "double is arithmetic: " << isArithmeticType<double> << '\n';

    std::cout << "bool* is arithmetic: " << isArithmeticType<bool*> << '\n';

    std::cout << "string is arithmetic: " << isArithmeticType<std::string> << '\n';

    return 0;
}