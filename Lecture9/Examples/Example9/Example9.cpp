#include <iostream>
#include <type_traits>
using namespace std;

template <
    typename T,
    typename = enable_if_t<is_integral_v<T>>
>
void process(T value) {
    cout << "Integral: " << value << '\n';
}

template <
    typename T,
    typename = enable_if_t<is_floating_point_v<T>>
>
void process(T value, int = 0) {
    cout << "Floating-point: " << value << '\n';
}

int main() {
    process(42);
    process(3.14);
}