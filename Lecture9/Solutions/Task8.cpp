#include <iostream>
#include <type_traits>
#include <concepts>
#include <string>

// 1. General type validator.
template <typename T>
struct TypeValidator{
    using Type = std::remove_cvref_t<T>;

    static constexpr bool isArithmetic =
        std::is_arithmetic_v<Type>;

    static constexpr bool isPointer =
        std::is_pointer_v<Type>;

    static constexpr const char* name = "General type";

    static void display(){
        std::cout << name
                  << " | Arithmetic: " << std::boolalpha
                  << isArithmetic
                  << " | Pointer: " << isPointer
                  << '\n';
    }
};

// 2. Full specialization for bool.
template <>
struct TypeValidator<bool>{
    using Type = bool;

    static constexpr bool isArithmetic = true;
    static constexpr bool isPointer = false;

    static constexpr const char* name = "Boolean type";

    static void display(){
        std::cout << name << '\n';
    }
};

// 3. Partial specialization for pointer types.
template <typename T>
struct TypeValidator<T*>{
    using Type = T*;

    static constexpr bool isArithmetic = false;
    static constexpr bool isPointer = true;

    static constexpr const char* name = "Pointer type";

    static void display(){
        std::cout << name
                  << " | Pointee type: "
                  << TypeValidator<
                         std::remove_cvref_t<T>
                     >::name
                  << '\n';
    }
};

// 4. Concept accepting integral and floating-point types.
template <typename T>
concept ValidNumericType =
    std::is_integral_v<std::remove_cvref_t<T>> ||
    std::is_floating_point_v<std::remove_cvref_t<T>>;

// 5. Function constrained by ValidNumericType.
template <ValidNumericType T>
auto doubleValue(T value){
    return value + value;
}

// 6. Compile-time type selection.
template <bool Condition>
using SelectedType =
    std::conditional_t<Condition, int, double>;

// 7. Trait detecting addition and multiplication.
template <typename T>
concept SupportsAdditionAndMultiplication = requires(T a, T b){
    a + b;
    a * b;
};

// 8. Custom class supporting both operations.
class Number{
private:
    double value;

public:
    explicit Number(double v) : value(v) {}

    double get() const{
        return value;
    }

    friend Number operator+(const Number& a, const Number& b){
        return Number(a.value + b.value);
    }

    friend Number operator*(const Number& a, const Number& b){
        return Number(a.value * b.value);
    }
};

int main(){
    // General and specialized classification.
    TypeValidator<int>::display();
    TypeValidator<double>::display();
    TypeValidator<bool>::display();
    TypeValidator<int*>::display();

    // 9. Validate arithmetic properties.
    static_assert(TypeValidator<int>::isArithmetic);
    static_assert(TypeValidator<double>::isArithmetic);

    static_assert(!TypeValidator<int*>::isArithmetic);
    static_assert(TypeValidator<int*>::isPointer);

    static_assert(TypeValidator<bool>::isArithmetic);
    static_assert(!TypeValidator<bool>::isPointer);

    // Normalize references and cv-qualifiers before classification.
    using Normalized = std::remove_cvref_t<const int&>;

    static_assert(std::is_same_v<Normalized, int>);
    static_assert(TypeValidator<Normalized>::isArithmetic);

    // 10. Test the numeric concept.
    static_assert(ValidNumericType<int>);
    static_assert(ValidNumericType<double>);
    static_assert(ValidNumericType<const int&>);

    static_assert(!ValidNumericType<int*>);
    static_assert(!ValidNumericType<std::string>);

    std::cout << "\nNumeric operations:\n";

    std::cout << "doubleValue(10): " << doubleValue(10) << '\n';

    std::cout << "doubleValue(2.5): " << doubleValue(2.5) << '\n';

    // Conditional type selection.
    static_assert(std::is_same_v<SelectedType<true>, int>);
    static_assert(std::is_same_v<SelectedType<false>, double>);

    std::cout << "\nSelected types:\n";

    std::cout << "Condition true selects int: " << std::is_same_v<SelectedType<true>, int> << '\n';

    std::cout << "Condition false selects double: " << std::is_same_v<SelectedType<false>, double><< '\n';

    // Operation detection.
    static_assert(SupportsAdditionAndMultiplication<int>);
    static_assert(SupportsAdditionAndMultiplication<double>);
    static_assert(SupportsAdditionAndMultiplication<Number>);

    static_assert(!SupportsAdditionAndMultiplication<std::string>);

    Number a(3.0);
    Number b(4.0);

    Number sum = a + b;
    Number product = a * b;

    std::cout << "\nCustom type operations:\n";

    std::cout << "3 + 4 = " << sum.get() << '\n';
    std::cout << "3 * 4 = " << product.get() << '\n';

    return 0;
}