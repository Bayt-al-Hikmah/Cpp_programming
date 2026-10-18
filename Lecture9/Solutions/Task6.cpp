#include <iostream>
#include <string>
#include <type_traits>
#include <concepts>

// 1. Printable concept.
template <typename T>
concept Printable = requires(std::ostream& os, const T& value){
    { os << value } -> std::same_as<std::ostream&>;
};

// 2. Generic storage class.
template <typename T>
class Storage{
private:
    T value;

public:
    explicit Storage(T v)
        : value(std::move(v))
    {
    }

    const T& get() const{
        return value;
    }

    // 3. Compare with a value of another type.
    template <typename U>
    bool compareWith(const U& other) const
        requires requires(const T& a, const U& b){
            { a == b } -> std::convertible_to<bool>;
        }
    {
        return value == other;
    }

    // 4. Display only if T is printable.
    void display() const
        requires Printable<T>
    {
        std::cout << value << '\n';
    }
};

// 5. Normalize types.
template <typename T>
using NormalizedType = std::remove_cvref_t<T>;

// 6. Select a storage type.
template <typename T>
using SelectedStorageType =
    std::conditional_t<
        std::is_integral_v<std::remove_cvref_t<T>>,
        long long,
        double
    >;

// 7. Constrained arithmetic conversion.
template <typename To, typename From>
    requires std::is_arithmetic_v<To> &&
             std::is_arithmetic_v<From> &&
             std::is_convertible_v<From, To>
To convertArithmetic(From value){
    return static_cast<To>(value);
}

int main(){
    Storage<int> integerStorage(42);
    Storage<double> doubleStorage(3.14);
    Storage<std::string> stringStorage(std::string("Hello"));

    std::cout << "Stored integer: " << integerStorage.get() << '\n';

    std::cout << "Stored double: " << doubleStorage.get() << '\n';

    std::cout << "Stored string: " << stringStorage.get() << '\n';

    std::cout << "\nDisplaying values:\n";

    integerStorage.display();
    doubleStorage.display();
    stringStorage.display();

    std::cout << "\nComparisons:\n";

    std::cout << std::boolalpha;

    std::cout << "42 == 42.0: " << integerStorage.compareWith(42.0) << '\n';

    std::cout << "3.14 == 3: " << doubleStorage.compareWith(3) << '\n';

    std::cout << "\nType selection:\n";

    static_assert(std::is_same_v<
        NormalizedType<const int&>, int>);

    static_assert(std::is_same_v<
        SelectedStorageType<int>, long long>);

    static_assert(std::is_same_v<
        SelectedStorageType<double>, double>);

    std::cout << "int selects long long: " << std::is_same_v<
                     SelectedStorageType<int>, long long>
              << '\n';

    std::cout << "double selects double: "
              << std::is_same_v<
                     SelectedStorageType<double>, double>
              << '\n';

    std::cout << "\nArithmetic conversion:\n";

    double converted = convertArithmetic<double>(42);

    std::cout << "42 converted to double: " << converted << '\n';

    // Invalid operations are rejected:
    // convertArithmetic<std::string>(42);
    // integerStorage.display() requires Printable<int>,
    // which is satisfied; a non-printable type would fail.

    return 0;
}