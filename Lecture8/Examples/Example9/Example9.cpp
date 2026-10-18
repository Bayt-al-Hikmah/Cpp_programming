#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class GreaterThan {
private:
    int threshold;

public:
    // Store the threshold when constructing the object.
    GreaterThan(int value) : threshold(value) {}

    // Make the object callable like a function.
    bool operator()(int number) const {
        return number > threshold;
    }
};

int main() {
    vector<int> numbers = {5, 12, 8, 20, 15, 3};

    // Create a function object that checks values greater than 10.
    GreaterThan check(10);

    cout << boolalpha;

    cout << "15 > 10: " << check(15) << '\n';
    cout << "5 > 10: " << check(5) << '\n';

    // Reuse the function object with an STL algorithm.
    int count = count_if(
        numbers.begin(),
        numbers.end(),
        check
    );

    cout << "Numbers greater than 10: " << count << '\n';

    // Create another function object with a different threshold.
    GreaterThan check15(15);

    int count15 = count_if(
        numbers.begin(),
        numbers.end(),
        check15
    );

    cout << "Numbers greater than 15: " << count15 << '\n';

    return 0;
}