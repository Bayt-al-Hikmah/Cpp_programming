## Objectives
- Understand how STL algorithms operate on iterator-defined ranges to search, count, sort, reverse, copy, transform, and remove elements.
- Apply standard algorithms such as `std::find`, `std::sort`, `std::transform`, and `std::accumulate` to solve common data-processing problems.
- Understand lambda expressions, including their syntax, captures, mutable behavior, and generic parameters.
- Use lambdas and function objects to customize STL algorithms with predicates, comparison functions, and transformation operations.
- Understand callable objects and use `std::function` to store and invoke compatible functions, lambdas, and function objects.
- Use `std::bind` and placeholders to bind arguments and adapt callable interfaces.
- Select appropriate callable mechanisms based on code clarity, flexibility, reusability, and performance.

## STL Algorithms
### Introduction
Algorithms are reusable operations that process ranges of elements. Instead of implementing a new loop for every task, we can use standard algorithms for common operations such as searching, sorting, counting, copying, transforming, and accumulating values.

Most of these algorithms are declared in the `<algorithm>` header. Numerical algorithms such as `std::accumulate` are declared in `<numeric>`.

An important principle is that algorithms generally work with iterators rather than requiring a specific container type, This means that an algorithm can often operate on different containers as long as their iterators support the required operations.

### Searching with `std::find()`
Suppose we have a vector of grades and want to determine whether a particular value exists. We could write a loop that checks each element until a match is found.

The STL already provides `std::find()`.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 18, 12, 16, 10};

    auto it = find(grades.begin(), grades.end(), 16);

    if (it != grades.end()) {
        cout << "Grade found: " << *it << '\n';
    } else {
        cout << "Grade not found\n";
    }

    return 0;
}
```
The algorithm receives three arguments:
```cpp
find(first, last, value);
```
- `first` identifies the beginning of the range.
- `last` identifies the position immediately after the range.
- `value` is the value we want to find.

The algorithm searches the range from the beginning until it finds a matching element or reaches the end. If a match is found, it returns an iterator to the first matching element. If no match exists, it returns the ending iterator.
### Searching with `std::find_if()`
Sometimes we do not want to search for a specific value. Instead, we want to find an element that satisfies a condition.

Suppose we want to find the first grade greater than or equal to 16. We could write a loop with an `if` statement, but `std::find_if()` allows us to express the condition separately.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {10, 12, 15, 18, 14};

    auto it = find_if(grades.begin(), grades.end(), [](int grade) {
            return grade >= 16;
        }
    );

    if (it != grades.end()) {
        cout << "First qualifying grade: " << *it << '\n';
    } else {
        cout << "No qualifying grade found\n";
    }

    return 0;
}
```
The third argument is a lambda expression:
```cpp
[](int grade) {
    return grade >= 16;
}
```
It receives a grade and returns `true` if the grade is at least 16.

The algorithm checks the elements in order and returns an iterator to the first element for which the condition evaluates to `true`.
### Counting with `std::count()`
Suppose we want to determine how many students received a particular grade. We could traverse the vector, compare each value, and maintain a counter.

The STL provides `std::count()`.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {15, 12, 15, 18, 15, 10};

    int numberOfFifteens = count(
        grades.begin(),
        grades.end(),
        15
    );

    cout << "Number of grades equal to 15: "
         << numberOfFifteens << '\n';

    return 0;
}
```
The algorithm examines the range and counts elements equal to the supplied value. It returns the number of matching elements.
### Ordering Elements with `std::sort()`
Searching becomes easier in some situations when data is organized in a particular order. Sorting is also useful when we want to display results from smallest to largest, rank examination grades, or prepare data for further processing.

C++ provides `std::sort()`.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 18, 12, 16, 10};

    sort(grades.begin(), grades.end());

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << '\n';

    return 0;
}
```
The expression:
```cpp
sort(grades.begin(), grades.end());
```
sorts the entire vector into ascending order according to the default ordering.

Unlike `find()`, `std::sort()` requires random-access iterators. That is why it works with `std::vector`, `std::array`, and `std::deque`, but not with `std::list` iterators.

A list has its own member function:
```cpp
numbers.sort();
```
which sorts the list directly.
#### Sorting in Descending Order
What if we want the largest grade first? We can supply a comparison function to `std::sort()`.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 18, 12, 16, 10};

    sort(
        grades.begin(),
        grades.end(),
        [](int a, int b) {
            return a > b;
        }
    );

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << '\n';

    return 0;
}
```
The third argument determines the ordering.
```cpp
[](int a, int b) {
    return a > b;
}
```
returns `true` when `a` should appear before `b`. This comparison causes the vector to be sorted in descending order.

The comparison must establish a **strict weak ordering**, meaning that it must obey specific consistency rules. We should not write inconsistent comparison functions that produce contradictory results.

### Reversing a Range with `std::reverse()`
Sorting and reversing are different operations. Sorting rearranges elements according to a comparison rule.

Reversing simply changes the order of elements within the range.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers = {10, 30, 20, 40};

    reverse(numbers.begin(), numbers.end());

    for (int number : numbers) {
        cout << number << ' ';
    }

    cout << '\n';

    return 0;
}
```
The original sequence was:
```
10 30 20 40
```
The reversed sequence is:
```
40 20 30 10
```
Notice that the elements are not sorted. Their original order has simply been reversed. `std::reverse()` requires a bidirectional range and modifies the elements in place.
### Copying Elements with `std::copy()`
Sometimes we want to transfer a range of elements into another destination.

The STL provides `std::copy()`.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> source = {10, 20, 30};
    vector<int> destination(source.size());

    copy(
        source.begin(),
        source.end(),
        destination.begin()
    );

    for (int number : destination) {
        cout << number << ' ';
    }

    cout << '\n';

    return 0;
}
```
The algorithm copies the elements from the source range into the destination, starting at `destination.begin()`. The destination must already have enough writable space for the elements being copied.

In this example:
```cpp
vector<int> destination(source.size());
```
creates a destination vector with the required number of elements.

A common mistake is to write:
```cpp
vector<int> destination;
copy(source.begin(), source.end(), destination.begin());
```
This is not valid because the destination vector is empty, so there is no writable range beginning at `destination.begin()`.

If we want the algorithm to grow a destination container as it copies, we can use an insertion iterator:
```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    vector<int> source = {10, 20, 30};
    vector<int> destination;

    copy(
        source.begin(),
        source.end(),
        back_inserter(destination)
    );

    for (int number : destination) {
        cout << number << ' ';
    }

    cout << '\n';

    return 0;
}
```
The `back_inserter()` function creates an output iterator that appends elements to the destination using its `push_back()` operation. This allows the vector to grow as elements are copied.
### Transforming Elements with `std::transform()`
Copying preserves the values of the source elements. Sometimes, however, we want to produce new values by applying an operation to each element.

For example, we may want to increase every grade by one point. The STL provides `std::transform()`.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {10, 12, 14, 16};
    vector<int> adjusted(grades.size());

    transform(
        grades.begin(),
        grades.end(),
        adjusted.begin(),
        [](int grade) {
            return grade + 1;
        }
    );

    for (int grade : adjusted) {
        cout << grade << ' ';
    }

    cout << '\n';

    return 0;
}
```
The algorithm reads each element in the input range, applies the supplied operation, and writes the result to the corresponding position in the destination range.

In this example:
```cpp
[](int grade) {
    return grade + 1;
}
```
defines how each value should be transformed.

The source vector remains unchanged because the results are written into `adjusted`. We could also transform the vector in place:
```cpp
transform(
    grades.begin(),
    grades.end(),
    grades.begin(),
    [](int grade) {
        return grade + 1;
    }
);
```
Here, the destination begins at the same position as the source. This is appropriate because the operation reads each element and writes its transformed value to that corresponding position.
### Removing Elements with `std::remove()`
Suppose we have a vector containing several values and want to remove every occurrence of `10`. It may seem natural to expect a function called `remove()` to reduce the vector's size.

However, `std::remove()` behaves differently. It rearranges the elements in the range so that the elements that do not match the requested value appear at the beginning. It returns an iterator marking the end of that resulting range. It does **not** change the size of the vector.

Let's examine an example:
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers = {10, 20, 10, 30, 40, 10};

    auto newEnd = remove(
        numbers.begin(),
        numbers.end(),
        10
    );

    cout << "Vector size: " << numbers.size() << '\n';
    cout << "Remaining logical range: ";

    for (auto it = numbers.begin(); it != newEnd; ++it) {
        cout << *it << ' ';
    }

    cout << '\n';

    return 0;
}
```
The vector's size remains six because `std::remove()` does not erase elements from the container.

The values beyond `newEnd` remain part of the vector, but their values are unspecified by the algorithm. We should not rely on what they contain.

This distinction is essential:
- `std::remove()` rearranges elements within a range.
- A container's `erase()` operation removes elements and changes its size.

### The Erase-Remove Idiom
To actually remove matching elements from a vector, we combine `std::remove()` with `vector::erase()`.

This is called the **erase-remove idiom**.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers = {10, 20, 10, 30, 40, 10};

    numbers.erase(
        remove(numbers.begin(), numbers.end(), 10),
        numbers.end()
    );

    for (int number : numbers) {
        cout << number << ' ';
    }

    cout << "\nSize: " << numbers.size() << '\n';

    return 0;
}
```
Let's break down the expression:
```cpp
numbers.erase(
    remove(numbers.begin(), numbers.end(), 10),
    numbers.end()
);
```
First, `remove()` moves the elements that should remain toward the beginning and returns the new logical end. Second, `erase()` removes the elements between that logical end and the vector's actual end. The result is a vector whose size reflects the remaining elements.

In C++20, vectors also provide `std::erase()` and `std::erase_if()` through the appropriate standard-library headers, which can express these operations more directly.

For example:
```cpp
std::erase(numbers, 10);
```
removes occurrences of `10` from a vector.
### Removing Elements That Satisfy a Condition
What if we want to remove all grades below 10 rather than removing one particular value?

We can use `std::remove_if()` with a condition.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {5, 12, 8, 17, 9, 15};

    grades.erase(
        remove_if(
            grades.begin(),
            grades.end(),
            [](int grade) {
                return grade < 10;
            }
        ),
        grades.end()
    );

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << '\n';

    return 0;
}
```
The condition:
```cpp
[](int grade) {
    return grade < 10;
}
```
returns `true` for grades that should be removed.

`std::remove_if()` rearranges the elements so that the values that do not satisfy the condition appear at the beginning. The returned iterator identifies the end of that logical range. The subsequent `erase()` call removes the remaining elements from the vector.

This demonstrates how algorithms and lambdas can work together to express complex operations with relatively little code.
### Numerical Operations with `std::accumulate()`
Suppose we want to calculate the total of all grades in a vector. We could use a loop:
```cpp
int total = 0;

for (int grade : grades) {
    total += grade;
}
```
This is perfectly valid. However, the standard library also provides `std::accumulate()` in the `<numeric>` header.
```cpp
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {10, 12, 14, 16};

    int total = accumulate(
        grades.begin(),
        grades.end(),
        0
    );

    cout << "Total: " << total << '\n';

    return 0;
}
```
The algorithm receives the beginning and ending iterators and an initial value.
```cpp
accumulate(first, last, initialValue);
```
It processes the range while accumulating a result. In this example, the initial value is zero, and each grade is added to the running total.

#### Choosing the Initial Value Carefully
The type of the initial value influences the type used for the accumulated result.

Consider:
```cpp
vector<double> values = {1.5, 2.5, 3.5};

auto total = accumulate(
    values.begin(),
    values.end(),
    0
);
```
Here, the initial value is an `int`.

The accumulation type is therefore `int`, and each addition is performed using that type. The floating-point values are converted during the operation, so the result does not preserve the intended decimal total.

A better version is:
```cpp
double total = accumulate(
    values.begin(),
    values.end(),
    0.0
);
```
Now the initial value is a `double`, so the accumulation preserves the floating-point result.
## Lambda Expressions and Function Objects
### Introduction
In the previous section, we used expressions such as:
```cpp
[](int grade) {
    return grade >= 10;
}
```
and:
```cpp
[](int a, int b) {
    return a > b;
}
```
These expressions allowed us to customize the behavior of standard algorithms without writing separate named functions. They are called **lambda expressions**.
### Understanding Lambda Expressions
A lambda expression creates a callable object, which means an object that can be invoked like a function.

The general syntax is:
```cpp
[captures](parameters) -> return_type {
    // Function body
};
```
Each part has a specific purpose.
- **Captures:** Specify which variables from the surrounding scope the lambda can access.
- **Parameters:** Define the values the lambda receives.
- **Return type:** Optionally specifies the type of value returned.
- **Function body:** Contains the instructions to execute.

The return type can often be deduced by the compiler, so we do not need to specify it explicitly.

For example:
```cpp
auto square = [](int number) {
    return number * number;
};
```
Here, `square` is a variable that stores the lambda object. We can call it as we would call an ordinary function:
```cpp
cout << square(5) << '\n';
```
Let's examine the expression:
```cpp
[](int number) {
    return number * number;
}
```
The empty capture list `[]` means that the lambda does not capture any variables from the surrounding scope.

The parameter list:
```cpp
(int number)
```
declares one integer parameter.

The body:
```cpp
{
    return number * number;
}
```
calculates and returns the square of that number.

The `auto` keyword allows the compiler to determine the lambda's type automatically. Lambda types are generated by the compiler and are generally not written explicitly.

### Using Lambdas with STL Algorithms
Lambdas become particularly useful when combined with standard algorithms. Suppose we want to count how many grades are greater than or equal to 10.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {5, 12, 8, 17, 9, 15};

    int passed = count_if(
        grades.begin(),
        grades.end(),
        [](int grade) {
            return grade >= 10;
        }
    );

    cout << "Number of passing grades: "
         << passed << '\n';

    return 0;
}
```
The lambda receives each grade considered by the algorithm and returns `true` if the grade is at least 10. The algorithm counts how many times the condition is satisfied.

Notice that we did not need to define a separate named function.

We could write:
```cpp
bool isPassingGrade(int grade) {
    return grade >= 10;
}
```
and pass that function to `count_if()` instead.

Both approaches are valid. A lambda is particularly convenient when the operation is short and used in one place.
### Understanding Lambda Captures
So far, our lambdas have used parameters without accessing variables from their surrounding scope. But what if a lambda needs information that already exists outside it?

Suppose we want to count grades above a threshold that the user can choose.
```cpp
int threshold = 15;
```
We want the lambda to compare each grade against `threshold`. This is where **captures** become important.

A capture allows a lambda to access variables from the surrounding scope. C++ provides several capture forms, including:
- `[]`: Capture nothing.
- `[=]`: Capture variables used from the surrounding scope by value.
- `[&]`: Capture variables used from the surrounding scope by reference.

#### Capturing Nothing: `[]`
An empty capture list means that the lambda does not capture local variables from the surrounding scope.
```cpp
#include <iostream>

using namespace std;

int main() {
    auto add = [](int a, int b) {
        return a + b;
    };

    cout << add(10, 20) << '\n';

    return 0;
}
```
The lambda does not need any external variables because all the information it uses comes from its parameters.

However, it can still use variables that do not need capturing, such as local variables declared within its own body, function parameters, and appropriate global or static variables.

For example, this would not compile:
```cpp
int threshold = 10;

auto check = [](int grade) {
    return grade >= threshold;
};
```
The lambda attempts to access a local variable from the surrounding scope without capturing it.
#### Capturing by Value: `[=]`
Capturing by value allows the lambda to access the values of local variables from the surrounding scope.
```cpp
#include <iostream>

using namespace std;

int main() {
    int threshold = 15;

    auto check = [=](int grade) {
        return grade >= threshold;
    };

    cout << check(18) << '\n';
    cout << check(12) << '\n';

    return 0;
}
```
The first call returns `true` because 18 is greater than or equal to 15. The second call returns `false` because 12 is less than 15.

The lambda captures the value of `threshold` when the lambda object is created. If we subsequently change the original variable, the captured copy does not automatically change.

For example:
```cpp
int threshold = 15;

auto check = [=](int grade) {
    return grade >= threshold;
};

threshold = 10;

cout << check(12) << '\n';
```
The result is still based on the captured value of 15, so the lambda returns `false`.

An important detail is that capturing by value does not make every captured variable immutable in every sense. It means the lambda holds its own captured copy. 

Also, `[=]` captures by value only the local variables actually used by the lambda; it does not necessarily copy every local variable in the surrounding scope.
#### Capturing by Reference: `[&]`
Sometimes we want a lambda to access the original variable rather than a copy. We can capture by reference using `[&]`.
```cpp
#include <iostream>

using namespace std;

int main() {
    int threshold = 15;

    auto check = [&](int grade) {
        return grade >= threshold;
    };

    threshold = 10;

    cout << check(12) << '\n';

    return 0;
}
```
The lambda refers to the original `threshold` variable. When the variable changes from 15 to 10, the lambda observes the updated value.

This is useful when a lambda needs to read or modify existing variables without copying them.

For example:
```cpp
int total = 0;

auto addToTotal = [&](int value) {
    total += value;
};

addToTotal(10);
addToTotal(20);

cout << total << '\n';
```
The lambda modifies the original `total` variable because it captures that variable by reference.

However, reference captures require care. The referenced variables must remain alive whenever the lambda uses them. If a lambda outlives a local variable it captured by reference, using that reference can result in undefined behavior.
#### Explicit Captures
Although `[=]` and `[&]` are convenient, they can sometimes capture more variables than we intended.

C++ allows us to specify captures explicitly.

For example:
```cpp
int threshold = 15;

auto check = [threshold](int grade) {
    return grade >= threshold;
};
```
This captures `threshold` by value.

Similarly:
```cpp
int total = 0;

auto add = [&total](int value) {
    total += value;
};
```
This captures `total` by reference.

Explicit captures make it clear which external variables a lambda depends on.

They are especially useful when a lambda is complex enough that understanding its dependencies matters.

We can also combine capture modes:
```cpp
int threshold = 10;
int total = 0;

auto process = [threshold, &total](int grade) {
    if (grade >= threshold) {
        total += grade;
    }
};
```
Here, `threshold` is captured by value, while `total` is captured by reference.
### Mutable Lambdas
By default, a lambda that captures a variable by value cannot modify its captured copy directly because its call operator is `const`. The `mutable` keyword changes this behavior.

Consider:
```cpp
#include <iostream>

using namespace std;

int main() {
    int value = 10;

    auto increase = [value]() mutable {
        value++;
        return value;
    };

    cout << increase() << '\n';
    cout << increase() << '\n';
    cout << value << '\n';

    return 0;
}
```
The lambda captures a copy of `value`, which initially contains 10, the `mutable` keyword allows the lambda to modify that captured copy. On the first call, the captured value changes from 10 to 11. On the second call, it changes from 11 to 12.
### Generic Lambdas
Until now, we have used lambdas with explicitly declared parameter types, But what if we want the same operation to work with different types?

C++14 introduced **generic lambdas**, which allow us to use `auto` in lambda parameter declarations.
```cpp
#include <iostream>

using namespace std;

int main() {
    auto doubleValue = [](auto value) {
        return value + value;
    };

    cout << doubleValue(10) << '\n';
    cout << doubleValue(2.5) << '\n';
    cout << doubleValue(string("Hello")) << '\n';

    return 0;
}
```
The lambda:
```cpp
[](auto value) {
    return value + value;
}
```
can work with different types as long as the operation `value + value` is valid for the type being used.
### Function Objects
Lambda expressions are closely related to another C++ concept: **function objects**, also known as functors. A function object is an object of a class or structure that defines the function-call operator, `operator()`.

This allows the object to be called as if it were a function. Let's create a function object that checks whether a grade is at least 10.
```cpp
#include <iostream>

using namespace std;

struct PassingGrade {
    bool operator()(int grade) const {
        return grade >= 10;
    }
};

int main() {
    PassingGrade check;

    cout << check(15) << '\n';
    cout << check(7) << '\n';

    return 0;
}
```
The structure defines:
```cpp
bool operator()(int grade) const {
    return grade >= 10;
}
```
The `operator()` function allows an object of `PassingGrade` to be called using ordinary function-call syntax.

For example:
```cpp
PassingGrade check;

check(15);
```
The expression:
```cpp
check(15)
```
is equivalent to calling:
```cpp
check.operator()(15);
```
The `const` after the parameter list indicates that the function does not modify the object's state through the ordinary member access available in that function.
#### Function Objects with State
Suppose we want to check whether a number is greater than a configurable threshold.

We could create a function object that stores the threshold.
```cpp
#include <iostream>

using namespace std;

class GreaterThan {
private:
    int threshold;

public:
    GreaterThan(int value) : threshold(value) {}

    bool operator()(int number) const {
        return number > threshold;
    }
};

int main() {
    GreaterThan check(10);

    cout << check(15) << '\n';
    cout << check(5) << '\n';

    return 0;
}
```
The object stores the threshold:
```cpp
GreaterThan check(10);
```
When we call:
```
check(15);
```
the function-call operator compares 15 against the stored threshold of 10.

This demonstrates that function objects can contain state and use that state when called.
#### Passing Function Objects to Algorithms
Function objects can be passed to standard algorithms in the same way as lambdas.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class GreaterThan {
private:
    int threshold;

public:
    GreaterThan(int value) : threshold(value) {}

    bool operator()(int number) const {
        return number > threshold;
    }
};

int main() {
    vector<int> numbers = {5, 12, 8, 20, 15};

    int count = count_if(
        numbers.begin(),
        numbers.end(),
        GreaterThan(10)
    );

    cout << "Numbers greater than 10: "
         << count << '\n';

    return 0;
}
```
The algorithm calls the supplied function object for the elements in the range, the object returns `true` for values greater than 10, and `count_if()` counts those values.

This approach separates the condition from the traversal logic. 

### Working with `std::function`
Now suppose we want to store different callable objects in the same variable or pass them through an interface that requires a consistent type.

This is where **`std::function`** becomes useful. Declared in the `<functional>` header, `std::function` is a general-purpose wrapper that can store and invoke compatible callable objects.

For example:
```cpp
std::function<int(int, int)> operation;
```
This declaration creates a wrapper capable of storing a callable that accepts two `int` arguments and produces a result compatible with `int`.

The wrapper can store different callable types as long as they are compatible with its specified function signature.
#### Storing a Lambda in `std::function`
Consider the following example:
```cpp
#include <functional>
#include <iostream>

int main() {
    std::function<int(int, int)> operation =
        [](int a, int b) {
            return a + b;
        };

    std::cout << operation(10, 20) << '\n';

    return 0;
}
```
The lambda implements the addition operation, while `std::function<int(int, int)>` provides a consistent interface for calling it.

We invoke the stored callable using ordinary function-call syntax:
```
operation(10, 20);
```
The wrapper forwards the arguments to the callable it contains and returns its result.
#### Storing Function Pointers
A function pointer stores the address of a function.

Consider an ordinary function:
```cpp
int multiply(int a, int b) {
    return a * b;
}
```
We can store a pointer to this function inside `std::function`:
```cpp
#include <functional>
#include <iostream>

int multiply(int a, int b) {
    return a * b;
}

int main() {
    std::function<int(int, int)> operation = multiply;

    std::cout << operation(4, 5) << '\n';

    return 0;
}
```
The same `std::function<int(int, int)>` interface can store a compatible function pointer or lambda.
#### Storing Function Objects
Recall that a function object is an object whose class defines `operator()`.

For example:
```cpp
#include <functional>
#include <iostream>

struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};

int main() {
    std::function<int(int, int)> operation = Multiply{};

    std::cout << operation(6, 7) << '\n';

    return 0;
}
```
The `Multiply` object can be stored because its call operator is compatible with the required signature.

Notice that the same wrapper type can store three different kinds of callable:
```cpp
std::function<int(int, int)> first = multiply;

std::function<int(int, int)> second =
    [](int a, int b) {
        return a + b;
    };

std::function<int(int, int)> third = Multiply{};
```
Here, `multiply` is an ordinary function, the second callable is a lambda, and the third is a function object.
#### Understanding Type Erasure
An important concept behind `std::function` is **type erasure**. Each lambda expression has its own unique compiler-generated type. Different function objects also have different types, and function pointers have pointer types.

Without a common wrapper, storing these different callable types in the same ordinary variable would generally require a different variable type for each callable.

`std::function` hides the concrete callable type behind a common interface.

For example:
```cpp
#include <functional>
#include <iostream>

int main() {
    std::function<int(int)> operation;

    operation = [](int x) {
        return x * 2;
    };

    std::cout << operation(5) << '\n';

    operation = [](int x) {
        return x * x;
    };

    std::cout << operation(5) << '\n';

    return 0;
}
```
The type of `operation` remains `std::function<int(int)>`, even though the concrete callable stored inside it changes.
#### Empty `std::function` Objects
A `std::function` object can exist without containing a callable.
```cpp
#include <functional>
#include <iostream>

int main() {
    std::function<int(int)> operation;

    if (operation) {
        std::cout << operation(10) << '\n';
    } else {
        std::cout << "No callable is stored\n";
    }

    return 0;
}
```
An empty `std::function` converts to `false` when used in a Boolean context. Attempting to invoke an empty wrapper throws `std::bad_function_call`.

Therefore, when a wrapper might be empty, check it before invoking it.
### `std::bind`
Sometimes, a function accepts several parameters, but we want to create a new callable with some arguments already specified.

For example, consider a function that subtracts two integers:
```cpp
int subtract(int a, int b) {
    return a - b;
}
```
Suppose we want to create an operation that always subtracts `3` from its first argument.

Instead of repeatedly supplying both arguments, we can create a new callable that stores the second argument.

C++ provides `std::bind` for this purpose. `std::bind` is declared in the `<functional>` header.
#### Binding Arguments
The general syntax is:
```cpp
std::bind(callable, boundArguments...);
```
The result is a callable object that invokes the original callable using the arguments supplied when binding and the arguments supplied later.

Consider this example:
```cpp
#include <functional>
#include <iostream>

int subtract(int a, int b) {
    return a - b;
}

int main() {
    auto subtractThree = std::bind(subtract, std::placeholders::_1, 3);

    std::cout << subtractThree(10) << '\n';
    std::cout << subtractThree(20) << '\n';

    return 0;
}
```
Let's examine the binding expression:
```
std::bind(subtract, std::placeholders::_1, 3);
```
It specifies three things:
1. `subtract` is the callable to invoke.
2. `std::placeholders::_1` represents the first argument supplied when the new callable is invoked.
3. `3` is the fixed second argument.

When we write:
```cpp
subtractThree(10);
```
the bound callable effectively invokes:
```cpp
subtract(10, 3);
```
The second argument is bound to `3`, while the first argument remains configurable.
#### Understanding Placeholders
Placeholders determine how arguments supplied to the resulting callable are passed to the original callable. They are available in the `std::placeholders` namespace.

The most common placeholders are:

| Placeholder             | Meaning                                        |
| ----------------------- | ---------------------------------------------- |
| `std::placeholders::_1` | First argument supplied to the bound callable  |
| `std::placeholders::_2` | Second argument supplied to the bound callable |
| `std::placeholders::_3` | Third argument supplied to the bound callable  |

Consider a function that divides two numbers:
```cpp
double divide(double a, double b) {
    return a / b;
}
```
We can bind the first argument to `100.0` and leave the second argument configurable:
```cpp
#include <functional>
#include <iostream>

double divide(double a, double b) {
    return a / b;
}

int main() {
    auto divideHundredBy = std::bind(divide,100.0,std::placeholders::_1);

    std::cout << divideHundredBy(4.0) << '\n';
    std::cout << divideHundredBy(5.0) << '\n';

    return 0;
}
```
We can also use multiple placeholders to rearrange argument order.

For example:
```cpp
auto reversedSubtract = std::bind(
    subtract,
    std::placeholders::_2,
    std::placeholders::_1
);
```
Calling:
```
reversedSubtract(3, 10);
```
effectively invokes:
```cpp
subtract(10, 3);
```
The placeholders reverse the order in which the two supplied arguments are passed to the original function.

#### Binding Member Functions
`std::bind` can also be used with member functions.

Consider a class that represents a sensor:
```cpp
#include <functional>
#include <iostream>

class Sensor {
public:
    void displayValue(int value) const {
        std::cout << "Sensor value: " << value << '\n';
    }
};

int main() {
    Sensor sensor;

    auto display = std::bind(
        &Sensor::displayValue,
        &sensor,
        std::placeholders::_1
    );

    display(42);

    return 0;
}
```
Here:
- `&Sensor::displayValue` identifies the member function.
- `&sensor` identifies the object on which the member function is called.
- `std::placeholders::_1` represents the argument supplied later.

The bound callable invokes `displayValue()` on the specified sensor object. Because this example binds a pointer to a local object, the bound callable must not be used after that object has been destroyed.

## Tasks
### Task 1:
Write a C++ program to analyze sensor measurements using STL algorithms.

The program should:
1. Ask the user to enter the number of measurements and their values.
2. Store the measurements in a `std::vector<double>`.
3. Use `std::find()` to search for a measurement entered by the user.
4. Use `std::find_if()` to find the first measurement greater than a specified threshold.
5. Use `std::count_if()` to count how many measurements are below a minimum acceptable value.
6. Use `std::sort()` to sort the measurements in ascending order.
7. Use `std::accumulate()` to calculate the total of all measurements.
8. Display the results of each operation.

**Additional challenge:** Sort the measurements in descending order using a lambda expression.

**Hint:** Use `std::vector`, `std::find`, `std::find_if`, `std::count_if`, `std::sort`, and `std::accumulate`. Include `<algorithm>` and `<numeric>`.
### Task 2:
Write a C++ program to process a collection of product prices using STL algorithms.
The program should:
1. Ask the user to enter the number of products and their prices.
2. Store the prices in a `std::vector<double>`.
3. Use `std::count()` to count how many products have a price equal to a specified value.
4. Use `std::copy()` to copy the original prices into another vector.
5. Use `std::transform()` to calculate a new price for each product after applying a discount percentage entered by the user.
6. Use `std::remove_if()` and the erase-remove idiom to remove products whose discounted prices are below a minimum value entered by the user.
7. Use `std::sort()` to sort the remaining prices in ascending order.
8. Display the original prices, discounted prices, and final collection.

**Additional challenge:** Use `std::accumulate()` to calculate the total price before and after applying the discount.

**Hint:** Use `std::copy`, `std::transform`, `std::count`, `std::remove_if`, `std::sort`, and `std::accumulate`. Use a lambda expression to calculate discounted prices.

### Task 3: 
Write a C++ program to evaluate students' examination results using lambda expressions and STL algorithms.

The program should:
1. Ask the user to enter the number of students and their grades.
2. Store the grades in a `std::vector<int>`.
3. Ask the user to enter a passing grade threshold.
4. Create a lambda expression that determines whether a grade meets the passing threshold.
5. Use `std::count_if()` to calculate the number of students who passed.
6. Use `std::find_if()` to find the first student grade that meets the threshold.
7. Use `std::transform()` to create a new vector containing grades increased by one point.
8. Use `std::remove_if()` with a lambda expression to remove grades below a minimum acceptable value from a separate copy of the vector.
9. Display the original grades, adjusted grades, and number of passing students.

**Additional challenge:** Create two lambdas that capture the passing threshold differently: one by value and one by reference. Change the threshold after creating both lambdas and compare their behavior.

**Hint:** Use `std::vector`, `std::count_if`, `std::find_if`, `std::transform`, `std::remove_if`, and lambda expressions. Use `[threshold]` for value capture and `[&threshold]` for reference capture.

### Task 4: 
Write a C++ program to filter and analyze numerical data using function objects.

The program should:
1. Ask the user to enter the number of values and their values.
2. Store the values in a `std::vector<int>`.
3. Create a function object named `GreaterThan` that stores a threshold provided through its constructor.
4. Overload `operator()` to return `true` when a value is greater than the stored threshold.
5. Use `std::count_if()` with a `GreaterThan` object to count the values above the threshold.
6. Use `std::find_if()` with the same function object to find the first value above the threshold.
7. Create another function object with a different threshold and compare the results.
8. Display the number of qualifying values and the first qualifying value, if one exists.

**Additional challenge:** Implement the same filtering operations using lambda expressions and compare the two approaches.

**Hint:** Use `std::vector`, `std::count_if`, `std::find_if`, a class or structure, a constructor, and `operator()`.

### Task 5:
Write a C++ program to clean and analyze a collection of numerical measurements using STL algorithms and lambda expressions.

The program should:

1. Ask the user to enter the number of measurements and their values.
2. Store the measurements in a `std::vector<double>`.
3. Use `std::copy()` to create a separate copy of the measurements.
4. Use `std::remove_if()` and the erase-remove idiom to remove negative measurements and zeros from the copy.
5. Use `std::transform()` to create a new vector in which each remaining measurement is multiplied by a correction factor entered by the user.
6. Use `std::sort()` to sort the corrected measurements in ascending order.
7. Use `std::reverse()` to reverse the order of the original measurements.
8. Use `std::accumulate()` to calculate the sum of the corrected measurements.
9. Use `std::count_if()` with a lambda expression to count corrected measurements greater than a threshold entered by the user.
10. Display the original measurements, cleaned measurements, corrected measurements, total, and number of measurements above the threshold.

**Additional challenge:** Create a generic lambda that doubles a value and test it with both integer and floating-point values. Also, implement a function object that checks whether a measurement exceeds a configurable threshold.

**Hint:** Use `std::copy`, `std::remove_if`, `std::transform`, `std::sort`, `std::reverse`, `std::accumulate`, and `std::count_if`. Include `<algorithm>`, `<numeric>`, and `<vector>`.