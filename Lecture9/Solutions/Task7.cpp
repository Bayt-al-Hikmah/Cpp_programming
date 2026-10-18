#include <iostream>
#include <type_traits>
#include <concepts>

// 1. Minimum for two values of the same type.
template <typename T>
    requires requires(const T& a, const T& b){
        { a < b } -> std::convertible_to<bool>;
    }
T minimumValue(const T& a, const T& b){
    return (b < a) ? b : a;
}

// 2. Minimum for different types.
// Disabled when T and U are identical, avoiding overlap
// with the same-type overload.
template <typename T, typename U>
    requires (!std::same_as<T, U>) &&
             requires(const T& a, const U& b)
             {
                 { a < b } -> std::convertible_to<bool>;
                 { b < a } -> std::convertible_to<bool>;
             }
auto minimumValue(const T& a, const U& b)
    -> std::common_type_t<T, U>{
    using Common = std::common_type_t<T, U>;

    Common x = a;
    Common y = b;

    return (y < x) ? y : x;
}

// 3. Arithmetic-only calculator.
template <typename T>
    requires std::is_arithmetic_v<T>
class NumericCalculator{
private:
    T value;

public:
    explicit NumericCalculator(T v) : value(v) {}

    T add(T other) const{
        return value + other;
    }

    T subtract(T other) const{
        return value - other;
    }

    T multiply(T other) const{
        return value * other;
    }

    T divide(T other) const{
        return value / other;
    }
};

// 4. Type description.
template <typename T>
void describeNumber(T value){
    if constexpr (std::is_integral_v<T>){
        std::cout << value << " is an integral value\n";
    }else if constexpr (std::is_floating_point_v<T>){
        std::cout << value << " is a floating-point value\n";
    }else{
        std::cout << "Unsupported numeric type\n";
    }
}

// 5. Compile-time absolute value.
constexpr int absoluteValue(int value){
    return value < 0 ? -value : value;
}

static_assert(absoluteValue(-10) == 10);
static_assert(absoluteValue(5) == 5);
static_assert(absoluteValue(0) == 0);

// 6. Custom type supporting comparison.
class Temperature{
private:
    double degrees;

public:
    explicit Temperature(double d) : degrees(d) {}

    double get() const{
        return degrees;
    }

    friend bool operator<(const Temperature& a,
                          const Temperature& b)
    {
        return a.degrees < b.degrees;
    }
};

int main(){
    // Same-type minimum.
    std::cout << "Minimum of 10 and 20: "
              << minimumValue(10, 20) << '\n';

    // Mixed-type minimum.
    auto mixedMinimum = minimumValue(10, 2.5);

    std::cout << "Minimum of 10 and 2.5: "
              << mixedMinimum << '\n';

    static_assert(std::is_same_v<
        decltype(mixedMinimum), double>);

    // Integer calculator.
    NumericCalculator<int> integers(10);

    std::cout << "\nInteger calculations:\n";
    std::cout << "10 + 3 = " << integers.add(3) << '\n';
    std::cout << "10 - 3 = " << integers.subtract(3) << '\n';
    std::cout << "10 * 3 = " << integers.multiply(3) << '\n';
    std::cout << "10 / 3 = " << integers.divide(3) << '\n';

    // Floating-point calculator.
    NumericCalculator<double> decimals(10.0);

    std::cout << "\nFloating-point calculations:\n";
    std::cout << "10 / 3 = " << decimals.divide(3.0) << '\n';

    // Compile-time absolute value.
    constexpr int absolute = absoluteValue(-25);

    std::cout << "\nAbsolute value of -25: " << absolute << '\n';

    // Type descriptions.
    describeNumber(42);
    describeNumber(3.14);

    // Custom comparison.
    Temperature cold(10.0);
    Temperature hot(30.0);

    auto colder = minimumValue(cold, hot);

    std::cout << "Lower temperature: " << colder.get() << '\n';

    return 0;
}