#include <iostream>
#include <type_traits>

// 1. constexpr power function.
constexpr int power(int base, unsigned int exponent){
    int result = 1;

    for (unsigned int i = 0; i < exponent; ++i){
        result *= base;
    }

    return result;
}

// 2. Compile-time checks.
static_assert(power(2, 0) == 1);
static_assert(power(2, 5) == 32);
static_assert(power(3, 4) == 81);

// 3. consteval factorial.
consteval unsigned long long compileTimeFactorial(unsigned int n){
    unsigned long long result = 1;

    for (unsigned int i = 2; i <= n; ++i){
        result *= i;
    }

    return result;
}

// 4. Mandatory compile-time calls.
constexpr auto factorial5 = compileTimeFactorial(5);
constexpr auto factorial6 = compileTimeFactorial(6);

static_assert(factorial5 == 120);
static_assert(factorial6 == 720);

// 5. Mutable configuration variable with static initialization.
constinit int globalConfiguration = 100;

// 6. if constexpr type inspection.
template <typename T>
void inspectValue(const T& value){
    if constexpr (std::is_integral_v<T>){
        std::cout << "Integral value: " << value << '\n';
    }else if constexpr (std::is_floating_point_v<T>){
        std::cout << "Floating-point value: " << value << '\n';
    }
    else if constexpr (std::is_pointer_v<T>){
        std::cout << "Pointer value: "
                  << static_cast<const void*>(value) << '\n';
    }else{
        std::cout << "Other type\n";
    }
}

// 7. Recursive template metaprogramming.
template <unsigned int N>
struct Factorial{
    static constexpr unsigned long long value =
        N * Factorial<N - 1>::value;
};

// Base-case specialization.
template <>
struct Factorial<0>{
    static constexpr unsigned long long value = 1;
};

static_assert(Factorial<6>::value == 720);

// 8. Compile-time type selection.
template <bool UseDouble>
using SelectedNumericType = std::conditional_t<UseDouble, double, int>;

static_assert(std::is_same_v<SelectedNumericType<true>, double>);
static_assert(std::is_same_v<SelectedNumericType<false>, int>);

int main(){
    std::cout << "power(2, 5): " << power(2, 5) << '\n';

    std::cout << "Factorial of 5: " << factorial5 << '\n';

    std::cout << "Factorial of 6 using consteval: " << factorial6 << '\n';

    std::cout << "Factorial of 6 using templates: " << Factorial<6>::value << '\n';

    // constinit does not imply const.
    globalConfiguration = 200;

    std::cout << "Updated configuration: " << globalConfiguration << '\n';

    inspectValue(42);
    inspectValue(3.14);

    int number = 10;
    int* pointer = &number;

    inspectValue(pointer);

    return 0;
}