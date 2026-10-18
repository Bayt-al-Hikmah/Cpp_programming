#include <iostream>
#include <type_traits>
#include <vector>
#include <string>
using namespace std;

template <typename T, typename = void>
struct HasSize : false_type {};

template <typename T>
struct HasSize<
    T,
    void_t<decltype(declval<const T&>().size())>
> : true_type {};

int main() {
    cout << boolalpha;

    cout << HasSize<vector<int>>::value << '\n';
    cout << HasSize<string>::value << '\n';
    cout << HasSize<int>::value << '\n';
}