#include <iostream>
#include <type_traits>
using namespace std;

template <bool UseInteger>
struct NumberType {
    using type = conditional_t<UseInteger, int, double>;
};

int main() {
    NumberType<true>::type a = 10;
    NumberType<false>::type b = 3.14;

    cout << a << '\n';
    cout << b << '\n';

    static_assert(is_same_v<NumberType<true>::type, int>);
    static_assert(is_same_v<NumberType<false>::type, double>);
}