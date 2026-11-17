#include <concepts>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// C++20 concept used by the concept-based square function.
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// 1. SFINAE version: substitution removes this overload for non-arithmetic T.
template <typename T,
          std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
constexpr T calculateSquareSFINAE(T value)
{
    return value * value;
}

// 2. C++20 concept-based equivalent.
template <Arithmetic T>
constexpr T calculateSquare(T value)
{
    return value * value;
}

// 3. Require multiplication to be a valid operation.
template <typename T>
concept Multipliable = requires(const T& left, const T& right)
{
    left * right;
};

template <Multipliable T>
auto calculateProduct(const T& left, const T& right)
{
    return left * right;
}

// 4. A type has size() if the expression is valid and size-like.
template <typename T>
concept HasSize = requires(const T& value)
{
    { value.size() } -> std::convertible_to<std::size_t>;
};

template <HasSize T>
std::size_t getSize(const T& value)
{
    return static_cast<std::size_t>(value.size());
}

// 5. Constrained overloads select a description based on the value type.
template <std::integral T>
void describeType(T value)
{
    std::cout << value << " is an integral type\n";
}

template <std::floating_point T>
void describeType(T value)
{
    std::cout << value << " is a floating-point type\n";
}

// Additional challenge: a container with size() and numeric indexed values.
template <typename C>
concept NumericContainer = HasSize<C> && requires(const C& container,
                                                   std::size_t index)
{
    container[index];
    requires std::is_arithmetic_v<
        std::remove_cvref_t<decltype(container[index])>>;
    // A character sequence such as std::string is not treated as a
    // numeric container merely because char is an arithmetic type.
    requires (!std::same_as<
        std::remove_cvref_t<decltype(container[index])>, char>);
};

template <NumericContainer C>
double sumElements(const C& values)
{
    double total = 0.0;
    for (std::size_t i = 0; i < values.size(); ++i)
    {
        total += static_cast<double>(values[i]);
    }
    return total;
}

int main()
{
    std::cout << "SFINAE square of 5: "
              << calculateSquareSFINAE(5) << '\n';

    std::cout << "Concept square of 2.5: "
              << calculateSquare(2.5) << '\n';

    std::cout << "Product of 6 and 7: "
              << calculateProduct(6, 7) << '\n';

    const std::string word = "templates";
    const std::vector<int> numbers{2, 4, 6, 8};

    std::cout << "String length: " << getSize(word) << '\n';
    std::cout << "Vector size: " << getSize(numbers) << '\n';

    describeType(42);
    describeType(3.14);

    std::cout << "Sum of vector elements: "
              << sumElements(numbers) << '\n';

    // Compile-time checks document which types satisfy each concept.
    static_assert(Arithmetic<int>);
    static_assert(Arithmetic<double>);
    static_assert(!Arithmetic<std::string>);
    static_assert(Multipliable<int>);
    static_assert(!Multipliable<std::string>);
    static_assert(HasSize<std::string>);
    static_assert(HasSize<std::vector<int>>);
    static_assert(!HasSize<int>);
    static_assert(NumericContainer<std::vector<int>>);
    static_assert(!NumericContainer<std::string>);

    return 0;
}
