#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    using A = remove_reference_t<int&>;
    using B = remove_cv_t<const int>;
    using C = decay_t<int[5]>;
    using D = decay_t<const double&>;

    cout << boolalpha;

    cout << is_same_v<A, int> << '\n';
    cout << is_same_v<B, int> << '\n';
    cout << is_same_v<C, int*> << '\n';
    cout << is_same_v<D, double> << '\n';
}