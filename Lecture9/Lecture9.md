# Templates and Compile-Time Programming

## Learning Objectives
- Write reusable function and class templates.
- Use specialization, variadic templates, and fold expressions.
- Inspect and transform types with type traits and `static_assert`.
- Constrain templates with concepts and `requires` expressions.
- Understand `constexpr`, `consteval`, `constinit`, and `if constexpr`.

## Template Fundamentals
### Introduction to Generic Programming
Consider a function that adds two integers:
```cpp
int add(int a, int b) {
    return a + b;
}
```
This function works well for integers, but what if we want to add two floating-point numbers, two strings, or objects of a custom type that supports `operator+`?

One solution is to write a separate function for each type. However, the implementations would often be nearly identical. Only the types would change.

**Generic programming** addresses this problem by separating an operation from the specific types on which it operates. Instead of writing one function for every type, we describe a general implementation that the compiler can instantiate for different types.
### Function Templates
A function template describes a family of functions whose types are determined when the template is instantiated.

Consider a generic version of `add()`:
```cpp
#include <iostream>
#include <string>

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(10, 20) << '\n';
    std::cout << add(2.5, 3.5) << '\n';
    std::cout << add(
        std::string("Hello "),
        std::string("World")
    ) << '\n';
}
```
The declaration:
```cpp
template <typename T>
```
introduces a template parameter named `T`. The compiler determines its type when it instantiates the function.

For example:
```cpp
add(10, 20);
```
deduces `T` as `int`, while:
```
add(2.5, 3.5);
```
deduces `T` as `double`.

The compiler generates the required specializations of the function template. The string example also works because `std::string` supports addition through concatenation.

However, the template is not valid for every conceivable type. The operation `a + b` must be supported for the types used.

This leads to an important principle: templates provide general implementations, but each instantiation must still satisfy the operations required by that implementation.
#### Template Argument Deduction and Explicit Arguments
In most function calls, the compiler can deduce template arguments from the function arguments.
```cpp
add(10, 20);       // T is int
add(2.5, 3.5);     // T is double
```
Sometimes, we may want to specify the template argument explicitly:
```cpp
add<double>(10, 20);
```
Here, `T` is explicitly specified as `double`, so the integer arguments are converted to `double` before the function is called.

Deduction also explains why the following call fails:
```cpp
add(10, 2.5);
```
The compiler attempts to deduce one `T` from both arguments. The first suggests `int`, while the second suggests `double`. These deductions conflict.

We can resolve the problem by specifying the intended type:
```cpp
add<double>(10, 2.5);
```
#### Multiple Template Parameters
Not every operation requires its arguments to have the same type. For example, a generic function could accept two different types:
```cpp
template <typename T, typename U>
auto add(T a, U b) {
    return a + b;
}
```
Now:
```cpp
auto result = add(10, 2.5);
```
allows `T` to be `int` and `U` to be `double`. The return type is deduced from the expression `a + b`, which produces a `double` in this example.

Template parameters can also have default arguments, particularly in class templates:
```cpp
template <typename T, typename U = int>
struct Pair {
    T first;
    U second;
};

Pair<double> p{3.14, 10};
```
Because `U` defaults to `int`, we only need to specify `T`.
### Class Templates and Generic Data Structures
We are not limited only to Function templates, in C++ we can also use Class templates while Function templates generalize operations. Class templates generalize the types of objects and data structures.

Suppose we want a simple container that stores a value of any supported type.
```cpp
#include <iostream>
#include <string>

template <typename T>
class Box {
private:
    T value;

public:
    explicit Box(T v) : value(v) {}

    const T& get() const {
        return value;
    }
};

int main() {
    Box<int> number(42);
    Box<std::string> text("Generic programming");

    std::cout << number.get() << '\n';
    std::cout << text.get() << '\n';
}
```
The declaration:
```cpp
template <typename T>
class Box
```
defines a family of classes. `Box<int>` and `Box<std::string>` are distinct class-template specializations, each storing its own chosen type.

The same idea underlies standard-library types such as `std::vector<int>` and `std::vector<double>`.

Templates can also define member functions that are themselves templates, known as member templates. This allows a class to have a fixed type while providing operations that accept other types.

For example:
```cpp
#include <iostream>

class Printer {
public:
    template <typename T>
    void print(const T& value) const {
        std::cout << value << '\n';
    }
};

int main() {
    Printer printer;

    printer.print(42);
    printer.print(3.14);
    printer.print("Hello");
}
```
The class itself is not a template, but its `print()` member function is.
### Template Specialization
A general template is useful when one implementation works for many types. However, sometimes a particular type requires different behavior.

For example, consider a generic class that identifies the type it stores:
```cpp
#include <iostream>

template <typename T>
struct TypeInfo {
    static void describe() {
        std::cout << "General type\n";
    }
};
```
We can provide a **full specialization** for `bool`:
```cpp
template <>
struct TypeInfo<bool> {
    static void describe() {
        std::cout << "Boolean type\n";
    }
};
```
The describe function will output `"Boolean type\n"` for boolean and `"General type\n"` for other types:
```cpp
TypeInfo<int>::describe();
TypeInfo<bool>::describe();
```
Here the program selects the general implementation for `int` and the specialized implementation for `bool`. 

We can also have **partial specialization**, which is available for class and variable templates, it handles a family of types matching a particular pattern.

For example, we can recognize pointer types:
```cpp
#include <iostream>

template <typename T>
struct TypeInfo {
    static void describe() {
        std::cout << "Non-pointer type\n";
    }
};

template <typename T>
struct TypeInfo<T*> {
    static void describe() {
        std::cout << "Pointer type\n";
    }
};

int main() {
    TypeInfo<int>::describe();
    TypeInfo<int*>::describe();
    TypeInfo<double*>::describe();
}
```
The specialization `TypeInfo<T*>` matches pointer types such as `int*` and `double*`, regardless of the pointed-to type.
### Variadic Templates and Parameter Packs
Our previous templates accept a fixed number of arguments. But some operations must work with an arbitrary number of values.

For example, a function that prints its arguments should ideally accept one value, three values, or ten values without requiring a separate overload for every argument count.

C++11 introduced **variadic templates**, which allow templates to accept a variable number of template arguments.

A variadic template declares a parameter pack using `...`.
```cpp
template <typename... Types>
void process(Types... values);
```
Here, `Types` is a template parameter pack, and `values` is a function parameter pack. Each can represent zero or more elements.

The challenge is that a parameter pack cannot simply be treated as one ordinary value. We need a way to expand its elements.
#### Expanding Parameter Packs
Consider a function that prints an arbitrary number of arguments:
```cpp
#include <iostream>

template <typename... Args>
void printAll(const Args&... args) {
    ((std::cout << args << ' '), ...);
    std::cout << '\n';
}

int main() {
    printAll(10, 3.14, "Hello");
    printAll(1, 2, 3, 4, 5);
}
```
The expression:
```cpp
((std::cout << args << ' '), ...);
```
Is a **fold expression**. It expands the parameter pack into a sequence of output operations.
#### Fold Expressions
Fold expressions allow us to apply an operator repeatedly across a parameter pack. For example, we can calculate the sum of an arbitrary number of arguments:
```cpp
#include <iostream>

template <typename... Args>
auto sum(const Args&... args) {
    return (args + ...);
}

int main() {
    std::cout << sum(1, 2, 3, 4) << '\n';
    std::cout << sum(1.5, 2.5, 3.0) << '\n';
}
```
The expression:
```
(args + ...)
```
expands into an addition chain equivalent to:
```
1 + 2 + 3 + 4
```
The operator must be valid for the supplied arguments.

An empty parameter pack requires special attention. For example, an addition fold without an initial value cannot be used with zero arguments.

We can provide an initial value:
```cpp
template <typename... Args>
auto sum(const Args&... args) {
    return (0 + ... + args);
}
```
This expression produces `0` when the pack is empty, although the initial value also influences the result type and should be chosen appropriately.
#### Generic Utilities with Variable Numbers of Arguments
Variadic templates are particularly useful for wrappers that need to pass an arbitrary number of arguments to another function.

For example:
```cpp
template <typename... Args>
void logValues(const Args&... args) {
    printAll(args...);
}
```
The expression `args...` expands the function parameter pack into the arguments of `printAll()`.
### Compile-Time Type Inspection and Transformation
Templates allow us to write one function that works with different types. However, not all types support the same operations.

Consider a function that divides a value by two:
```cpp
template <typename T>
T halve(T value) {
    return value / 2;
}
```
This function works with many numeric types, such as integers and floating-point numbers. However, it does not work with every type. For example, we cannot divide a pointer by an integer.

The compiler will report an error if we use an unsupported type. However, in generic programming, we may want to check the type before using an operation and provide a clear error message.

C++ provides **type traits** to inspect the properties of a type and **type transformations** to modify types during compilation.
#### Type Traits
A type trait is a compile-time facility that provides information about a type. The standard library defines many traits in the `<type_traits>` header.

For example:
```cpp
#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::boolalpha;

    std::cout << std::is_integral_v<int> << '\n';
    std::cout << std::is_integral_v<double> << '\n';

    std::cout << std::is_pointer_v<int*> << '\n';
    std::cout << std::is_pointer_v<int> << '\n';

    std::cout << std::is_same_v<int, int> << '\n';
    std::cout << std::is_same_v<int, double> << '\n';
}
```
The traits answer different questions:
- `std::is_integral<T>` determines whether `T` is an integral type.
- `std::is_pointer<T>` determines whether `T` is a pointer type.
- `std::is_same<T, U>` determines whether two types are identical.

The `_v` forms, such as `std::is_integral_v<int>`, are convenient variable templates that expose the Boolean result directly. 
#### Type Transformations
Sometimes, a type contains extra information, such as references or qualifiers, that we do not need. C++ provides type transformations to modify a type and make it easier to use in generic programming.

For example, `int&` is a reference to an integer, while `int` is a regular integer type. We can use `std::remove_reference` to remove the reference and get the original type.
```cpp
#include <iostream>
#include <type_traits>

int main() {
    using ReferenceType = int&;
    using ValueType = std::remove_reference_t<ReferenceType>;

    std::cout << std::is_same_v<ValueType, int> << '\n';
}
```
Here, `std::remove_reference_t<int&>` produces `int`. The `_t` suffix gives us the resulting type directly.

Another useful transformation is `std::decay`. It removes references and `const` or `volatile` qualifiers. It also converts arrays and functions into pointers.
```cpp
#include <type_traits>

int main() {
    using A = std::decay_t<const int&>;
    using B = std::decay_t<int[5]>;

    static_assert(std::is_same_v<A, int>);
    static_assert(std::is_same_v<B, int*>);
}
```
Here, `const int&` becomes `int`, while `int[5]` becomes `int*`. `std::decay_t` is useful when we want to determine the type that would normally be obtained when storing an argument by value.
#### Compile-Time Validation with `static_assert`
Type traits become more useful when combined with `static_assert`. It allows us to check a condition during compilation. If the condition is false, the compiler stops and reports an error.

For example:
```cpp
#include <type_traits>

template <typename T>
T doubleValue(T value) {
    static_assert(
        std::is_arithmetic_v<T>,
        "T must be an arithmetic type"
    );

    return value * 2;
}
```
Here, `static_assert` checks whether `T` is an arithmetic type, such as an integer or a floating-point type. If we try to use the function with an unsupported type, compilation fails and the compiler displays the provided error message.

This allows us to set clear rules for template types and catch invalid types before the program runs.
#### Selecting Types with `std::conditional_t`
Sometimes, we need a template to choose between two types depending on a condition. C++ provides `std::conditional_t` to make this selection during compilation.

```cpp
#include <type_traits>

template <bool UseInteger>
struct NumberType {
    using type = std::conditional_t<
        UseInteger,
        int,
        double
    >;
};

int main() {
    NumberType<true>::type a = 10;
    NumberType<false>::type b = 3.14;
}
```
Here, if the condition is `true`, the selected type is `int`. If it is `false`, the selected type is `double`. The selection happens during compilation, not while the program is running.

Type traits and conditional types help us inspect types and adapt templates to different types. However, selecting a type does not guarantee that every operation on it is valid. We also need a way to control which types are allowed to use a template.

### Template Constraints and Conditional Instantiation
Consider a generic function that calls the `size()` member function on the given value. Since templates can accept different types, we need to make sure that the provided type supports the operations used inside the function.
```cpp
template <typename T>
auto calculate(T value) {
    return value.size();
}
```
This function works with types that provide a `size()` member function, such as `std::string` and `std::vector`. However, it does not work with types like `int`, because integers do not have a `size()` function.

When we use an unsupported type, the compiler encounters an invalid expression during template instantiation and reports an error.

**Template constraints allow us to define what a type must support before a template can be used.** They help control which functions are available for different types and prevent templates from being used with unsupported types.
#### Template Substitution and SFINAE
When working with templates, we may want to allow a function to accept only certain types. C++ provides a technique called **SFINAE**, which stands for **Substitution Failure Is Not An Error**. It allows the compiler to ignore a template when the provided type does not satisfy its requirements, instead of immediately producing an error.

For example, consider a function that should accept only integral types, such as `int`, `char`, and `long`.
```cpp
#include <type_traits>
#include <iostream>

template <
    typename T,
    typename = std::enable_if_t<
        std::is_integral_v<T>
    >
>
void process(T value) {
    std::cout << value << '\n';
}

int main() {
    process(42);
}
```
Here, `std::enable_if_t` checks the condition `std::is_integral_v<T>`. If the condition is true, it provides a valid type and the template can be used. If the condition is false, substitution fails and the compiler ignores this template as a possible match.

For example, calling `process(3.14)` will fail because `double` is not an integral type. Since no suitable function is available, the compiler reports an error.
#### The Detection Idiom
A template may need to check whether a type supports a specific operation rather than checking a built-in property. For example, we may want to know whether a type provides a `size()` member function before using it.

Before C++20, this was commonly done using the detection idiom with `std::void_t`. Consider the following example:
```cpp
#include <type_traits>
#include <utility>
#include <vector>

template <typename T, typename = void>
struct HasSize : std::false_type {};

template <typename T>
struct HasSize<
    T,
    std::void_t<
        decltype(std::declval<const T&>().size())
    >
> : std::true_type {};

int main() {
    static_assert(HasSize<std::vector<int>>::value);
    static_assert(!HasSize<int>::value);
}
```
The important expression is:
```cpp
decltype(std::declval<const T&>().size())
```
`std::declval` allows us to use a hypothetical value of type `T` without creating an actual object. This lets us check whether calling `size()` on that type is valid.

`decltype` obtains the type of the expression, while `std::void_t` converts a valid type into `void`. If the expression is valid, the specialization is selected and `HasSize` inherits from `std::true_type`. Otherwise, the primary template is used and `HasSize` inherits from `std::false_type`.

#### Concepts and `requires` Clauses
C++20 introduced **concepts** to make template constraints easier to write and understand. A concept defines a set of requirements that a type must satisfy before it can be used with a template.

For example, we can define a concept that accepts only arithmetic types:
```cpp
#include <concepts>
#include <type_traits>
#include <iostream>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
T doubleValue(T value) {
    return value * 2;
}

int main() {
    std::cout << doubleValue(10) << '\n';
    std::cout << doubleValue(2.5) << '\n';
}
```
Here, `Arithmetic` is a concept that checks whether a type is arithmetic, such as `int`, `float`, or `double`. The declaration `template <Arithmetic T>` requires the type `T` to satisfy this concept before the function can be used.

We can write the same constraint using a `requires` clause:
```cpp
template <typename T>
    requires Arithmetic<T>
T doubleValue(T value) {
    return value * 2;
}
```
Both forms express the same requirement. They prevent the function from being used with types that do not satisfy the `Arithmetic` concept.

Concepts can also check whether a type supports specific operations, not just built-in properties. For example, consider a function that requires its arguments to support addition:
```cpp
#include <concepts>

template <typename T>
concept Addable = requires(T a, T b) {
    a + b;
};

template <typename T>
    requires Addable<T>
auto addValues(T a, T b) {
    return a + b;
}
```
Here, the `requires` expression checks whether the expression `a + b` is valid for the given type. If the operation is supported, the type satisfies the `Addable` concept and can be used with the function.
#### Combining and Composing Concepts
Concepts can be combined using logical operators to define more specific requirements. For example, we can create a concept that accepts both integral and floating-point types.
```cpp
#include <concepts>

template <typename T>
concept Numeric =
    std::integral<T> ||
    std::floating_point<T>;

template <Numeric T>
T square(T value) {
    return value * value;
}
```
Here, the `Numeric` concept accepts types that satisfy either `std::integral` or `std::floating_point`. We can also use a `requires` expression to check whether a type supports multiple operations.
```cpp
template <typename T>
concept NumericLike =
    requires(T a, T b) {
        a + b;
        a * b;
    };
```
Here, the type must support both addition and multiplication. The expressions inside `requires` are only checked during compilation. They are not executed when the program runs.
#### Constrained Overloads
Concepts can also be used with function overloading to provide different implementations depending on the type of the arguments. For example, we can create one function for integral types and another for floating-point types.
```cpp
#include <concepts>
#include <iostream>

template <std::integral T>
void describe(T) {
    std::cout << "Integral value\n";
}

template <std::floating_point T>
void describe(T) {
    std::cout << "Floating-point value\n";
}

int main() {
    describe(10);
    describe(3.14);
}
```
Both functions have the same name, but their concepts define different requirements. When we call `describe(10)`, the integral version is selected. When we call `describe(3.14)`, the floating-point version is selected.

This allows us to use the same function name while providing different implementations for different types.
## Compile-Time Programming and Metaprogramming

### Introduction
Normally, functions execute when the program runs. Their instructions operate on values during execution.

C++ also allows us to perform computations during compilation, before the program starts. This can reduce runtime work and allow the compiler to detect errors earlier.

For example, fixed values and mathematical calculations can be computed during compilation instead of waiting until the program runs.
### Constant Expressions and `constexpr`
A constant expression is an expression whose value can be determined during compilation. C++ provides the `constexpr` keyword to allow variables and functions to be used in constant expressions.

Consider the following example:
```cpp
#include <iostream>

constexpr int square(int value) {
    return value * value;
}

int main() {
    constexpr int result = square(5);

    std::cout << result << '\n';
}
```
Here, `square()` is declared with `constexpr`, which allows it to be evaluated during compilation. Since `result` is also declared `constexpr`, its value must be known at compile time. The compiler evaluates `square(5)` and stores the result.

However, a `constexpr` function can also execute at runtime when its arguments are not constant expressions.
```cpp
int value ;
cin >> value;
int result = square(value);
```
Here, `value` is determined during execution, so the function call is evaluated at runtime.
### Static Initialization with `constinit`
C++20 introduced `constinit` to guarantee that a variable with static or thread storage duration is initialized during static initialization, before normal program execution begins.

Consider the following example:
```cpp
constinit int counter = 0;

int main() {
    counter = 10; // OK
}
```
Here, `counter` is initialized before `main()` starts. However, it can still be modified while the program runs. Unlike `constexpr`, `constinit` does not make a variable constant.

Consider another example:
```cpp
int getValue() {
    return 42;
}

// constinit int value = getValue(); // Ill-formed
```
The function `getValue()` is not a constant expression because it is not declared `constexpr` or `consteval`. Therefore, its result cannot be used to satisfy the initialization requirement of `constinit`.

Use `constinit` when a variable must be initialized statically but still needs to be modified at runtime. Use `constexpr` when a variable must also be a compile-time constant.
### Immediate Functions with `consteval`
A function may need to be evaluated exclusively during compilation rather than at runtime. C++20 introduced the `consteval` keyword to enforce this requirement.

Consider the following example:
```cpp
consteval int cube(int value) {
    return value * value * value;
}

int main() {
    constexpr int result = cube(3);
}
```
Here, `cube()` is an immediate function. Every call to this function must be evaluated at compile time.

For example:
```cpp
int value = 3;

// int result = cube(value); // Ill-formed
```
This call is not allowed because `value` is determined at runtime. The compiler requires the arguments to be constant expressions so that the function can be evaluated during compilation.

The main difference is that `constexpr` allows both compile-time and runtime evaluation, while `consteval` requires compile-time evaluation.

### Compile-Time Dispatch with `if constexpr`
In generic programming, we may want a function to behave differently depending on the type it receives. C++17 introduced `if constexpr` to select a branch during compilation.

Consider an ordinary conditional statement:
```cpp
if (condition) {
    // ...
} else {
    // ...
}
```
A normal `if` checks its condition at runtime. Even when the condition is known during compilation, both branches must be valid when a template is instantiated.

`if constexpr` solves this problem by evaluating the condition during compilation and discarding the branch that is not selected.
```cpp
#include <iostream>
#include <type_traits>

template <typename T>
void describe(T value) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integral: " << value << '\n';
    } else {
        std::cout << "Other type: " << value << '\n';
    }
}

int main() {
    describe(42);
    describe(3.14);
}
```
Here, the compiler checks whether `T` is an integral type. When `T` is `int`, the first branch is selected. When `T` is `double`, the second branch is selected. The unused branch is discarded during template instantiation.

This becomes particularly useful when different types support different operations.

For example:
```cpp
#include <iostream>
#include <type_traits>

template <typename T>
void inspect(T value) {
    if constexpr (std::is_pointer_v<T>) {
        std::cout << "Pointer address: " << value << '\n';
    } else {
        std::cout << "Value: " << value << '\n';
    }
}
```
Here, the compiler checks whether `T` is a pointer. If it is, the pointer-specific branch is selected. Otherwise, the second branch is used.

This allows us to write one generic function with different implementations for different types without requiring every branch to be valid for every type.
### Template Metaprogramming
**Template metaprogramming** is a technique that uses C++ templates to perform computations during compilation. Templates can recursively instantiate other templates to calculate values or generate types.

A classic example is calculating a factorial using recursive template instantiation:
```cpp
template <unsigned int N>
struct Factorial {
    static constexpr unsigned long long value =
        N * Factorial<N - 1>::value;
};

// Base case
template <>
struct Factorial<0> {
    static constexpr unsigned long long value = 1;
};

int main() {
    static_assert(Factorial<5>::value == 120);
}
```
The `Factorial` template calculates the result by multiplying `N` by the factorial of `N - 1`. This continues until the compiler reaches the specialization `Factorial<0>`, which provides the base value `1` and stops the recursion.

The compiler instantiates the required templates and calculates the result during compilation. The `static_assert` then checks that the result is equal to `120`.

Although this technique demonstrates how templates can perform compile-time calculations, modern C++ provides a simpler alternative for many computations: `constexpr` functions.
```cpp
constexpr unsigned long long factorial(unsigned int n) {
    unsigned long long result = 1;

    for (unsigned int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

static_assert(factorial(5) == 120);
```
Here, the `constexpr` function calculates the factorial using a loop. Since the argument is a constant expression, the compiler evaluates the function during compilation. The `static_assert` checks the result.

This approach is easier to read and maintain than recursive template instantiation. Loop-based `constexpr` functions require C++14 or later.
### Type-Level Programming
Templates can perform computations on types, not just values. This is called **type-level programming**. Instead of calculating a number, the compiler selects or transforms a type during compilation.

For example, `std::conditional_t` selects between two types, while `std::remove_reference_t` removes a reference from a type.

We can combine these facilities to create a type-level decision:
```cpp
#include <type_traits>

template <typename T>
struct StorageType {
    using type = std::conditional_t<
        std::is_pointer_v<T>,
        T,
        T*
    >;
};

int main() {
    using A = StorageType<int>::type;
    using B = StorageType<double*>::type;

    static_assert(std::is_same_v<A, int*>);
    static_assert(std::is_same_v<B, double*>);
}
```
Here, the compiler checks whether `T` is a pointer type. If it is, the original type is selected. Otherwise, a pointer to that type is selected.

For example, `StorageType<int>::type` produces `int*`, while `StorageType<double*>::type` remains `double*`.

## Tasks
### Task 1: 
Write a C++ program to implement a generic data-processing utility using function templates, multiple template parameters, and template argument deduction.

The program should:
1. Create a function template named `convertAndCombine()` that accepts two arguments of potentially different types.
2. Use `auto` as the return type to deduce the type of the result.
3. Test the function with integers and floating-point values, such as `convertAndCombine(10, 2.5)`.
4. Create another function template named `displayValue()` that accepts a single value of any type and displays it.
5. Implement a class template named `Measurement<T>` that stores a measurement of type `T`.
6. Add a member function template that allows the stored measurement to be compared with a value of another type.
7. Create a class template with a default template argument and demonstrate its use without explicitly specifying every type.
8. Display the results for several combinations of types.

**Additional challenge:** Create a function template that accepts two arguments of the same type, then demonstrate why calling it with an `int` and a `double` may fail during template argument deduction. Resolve the issue using explicit template arguments.

**Hint:** Use `template<typename T>`, multiple template parameters, `auto`, class templates, member templates, and default template arguments.
### Task 2:
Write a C++ program to build a type-classification utility using template specialization and type traits.

The program should:
1. Create a class template named `TypeClassifier<T>` that identifies a type as a general type.
2. Provide a full specialization for `bool` that identifies Boolean types separately.
3. Provide a partial specialization for pointer types to distinguish them from non-pointer types.
4. Use `std::is_integral_v<T>` to determine whether a type is integral.
5. Use `std::is_floating_point_v<T>` to determine whether a type is floating-point.
6. Use `std::remove_reference_t<T>` to obtain the underlying type of a reference.
7. Use `std::conditional_t` to select `int` or `double` according to a compile-time condition.
8. Use `static_assert` to verify that the selected types match the expected types.
9. Test the utility with `int`, `double`, `bool`, `int*`, and `int&`.

**Additional challenge:** Create a variable template that determines whether a type is arithmetic, then use it to validate several types at compile time.

**Hint:** Include `<type_traits>`. Use full and partial specialization, `std::is_integral_v`, `std::is_floating_point_v`, `std::remove_reference_t`, `std::conditional_t`, and `static_assert`.
### Task 3: 
Write a C++ program to implement a generic logging utility using variadic templates and fold expressions.

The program should:
1. Create a variadic function named `logValues()` that accepts an arbitrary number of arguments of different types.
2. Use a fold expression to display all arguments on one line.
3. Create a variadic function named `sumValues()` that calculates the sum of a variable number of numerical arguments.
4. Use an initial value in the fold expression so that `sumValues()` also handles an empty argument pack.
5. Create a function named `countArguments()` that returns the number of arguments passed to it.
6. Implement a function named `allPositive()` that uses a fold expression to determine whether all supplied numerical arguments are positive.
7. Test the functions with integers, floating-point values, and strings where appropriate.
8. Demonstrate how parameter packs expand when forwarding arguments to another function.

**Additional challenge:** Implement a variadic function that calculates the product of its arguments. Define the behavior for an empty argument pack and test it explicitly.

**Hint:** Use `template<typename... Args>`, parameter packs, `sizeof...(Args)`, fold expressions, and `<iostream>`. Ensure that each operation is valid for the argument types supplied.

### Task 4:
Write a C++ program to implement a set of generic mathematical utilities using SFINAE, concepts, and `requires` clauses.

The program should:

1. Create a function template named `calculateSquare()` that accepts only arithmetic types.
2. Implement an initial version using `std::enable_if_t` and `std::is_arithmetic_v<T>`.
3. Implement an equivalent version using a C++20 concept named `Arithmetic`.
4. Create a concept named `Multipliable` that checks whether two values of the same type support multiplication.
5. Implement a generic function named `calculateProduct()` that requires the `Multipliable` concept.
6. Create a concept named `HasSize` that checks whether a type provides a valid `size()` member function.
7. Implement a generic function named `getSize()` that accepts only types satisfying `HasSize`.
8. Test `getSize()` with `std::string` and `std::vector<int>`.
9. Create two constrained overloads of a function named `describeType()`: one for integral types and another for floating-point types.
10. Demonstrate that unsupported types do not satisfy the relevant constraints.

**Additional challenge:** Create a concept named `NumericContainer` that requires a type to provide `size()` and support indexed access returning a numeric value. Use it to implement a function that calculates the sum of the elements of a compatible container.

**Hint:** Use `<type_traits>`, `<concepts>`, `<vector>`, and `<string>`. Compile the C++20 concept-based implementations with a C++20-compatible compiler. Use `std::enable_if_t` for SFINAE and `requires` expressions for operation-based constraints.

### Task 5: 
Write a C++ program to implement a configurable mathematical utility using `constexpr`, `consteval`, `if constexpr`, and template metaprogramming.

The program should:
1. Create a `constexpr` function named `power()` that calculates an integer base raised to a non-negative integer exponent.
2. Use `static_assert` to verify several results of `power()` during compilation.
3. Create a `consteval` function named `compileTimeFactorial()` that calculates the factorial of a non-negative integer.
4. Demonstrate valid compile-time calls to `compileTimeFactorial()`.
5. Declare a mutable global configuration variable using `constinit` and initialize it with a constant expression.
6. Create a function template named `inspectValue()` that uses `if constexpr` to distinguish integral, floating-point, and pointer types.
7. Implement a template metaprogram named `Factorial<N>` that computes factorial values using recursive template instantiation and a base-case specialization.
8. Verify the result of `Factorial<6>` using `static_assert`.
9. Compare the template-based factorial implementation with the `constexpr` implementation.
10. Display the runtime results of the mathematical utilities and demonstrate how the compile-time checks validate the program.

**Additional challenge:** Create a compile-time configuration template that uses `std::conditional_t` to select a numeric type according to a Boolean template parameter. Use `static_assert` to verify the selected type.

**Hint:** Use `constexpr`, `consteval`, `constinit`, `if constexpr`, `static_assert`, `std::conditional_t`, and class-template specialization. Remember that `constinit` guarantees static initialization but does not make a variable immutable. Compile the program using C++20.
### Task 6:
Write a C++ program to implement a generic storage system that combines class templates, type traits, concepts, and compile-time type selection.

The program should:

1. Create a class template named `Storage<T>` that stores a value of type `T`.
2. Provide a constructor and a member function named `get()` that returns the stored value.
3. Implement a member function template named `compareWith()` that compares the stored value with an argument of another type when the comparison is valid.
4. Create a concept named `Printable` that checks whether a value can be sent to `std::cout`.
5. Add a constrained member function named `display()` that displays the stored value only when `T` satisfies `Printable`.
6. Use `std::remove_cvref_t<T>` to obtain a normalized type for compile-time inspection.
7. Use `std::conditional_t` to select an appropriate storage type based on whether the supplied type is integral or non-integral.
8. Use `static_assert` to verify the selected types.
9. Create instances of `Storage<int>`, `Storage<double>`, and `Storage<std::string>`.
10. Demonstrate that the same generic class can store and process different types while respecting the constraints of each operation.

**Additional challenge:** Implement a constrained conversion function that allows conversion between arithmetic types but rejects conversions involving unsupported types at compile time.

**Hint:** Use class templates, member templates, concepts, `requires` clauses, `std::remove_cvref_t`, `std::conditional_t`, and `static_assert`. Compile with C++20.
### Task 7: 
Write a C++ program to develop a small generic numeric library that adapts its behavior to the types supplied.

The program should:

1. Create a function template named `minimumValue()` that returns the smaller of two values of the same type.
2. Create a second version that accepts two different types and uses a suitable common result type.
3. Use `std::common_type_t<T, U>` to determine the result type for mixed-type inputs.
4. Create a class template named `NumericCalculator<T>` that provides addition, subtraction, multiplication, and division operations.
5. Use a compile-time constraint to ensure that `NumericCalculator<T>` accepts arithmetic types only.
6. Implement a function template named `describeNumber()` that uses `if constexpr` to distinguish integral and floating-point types.
7. Create a `constexpr` function that calculates the absolute value of an integer.
8. Use `static_assert` to validate the results of the compile-time calculations.
9. Demonstrate the library with integer and floating-point calculations.
10. Explain through program output how template argument deduction and type selection affect the results.

**Additional challenge:** Create a constrained overload of `minimumValue()` that accepts only types supporting the comparison operator `<`. Test it with a custom class that defines this operator.

**Hint:** Use function templates, class templates, `std::common_type_t`, concepts, `if constexpr`, `constexpr`, and `static_assert`.
### Task 8: 
Write a C++ program to build a reusable type-validation framework using type traits, concepts, specialization, and compile-time checks.

The program should:

1. Create a template named `TypeValidator<T>` that determines whether a type satisfies a specified set of requirements.
2. Use `std::is_arithmetic_v<T>` to classify arithmetic types.
3. Use `std::is_pointer_v<T>` to identify pointer types.
4. Use `std::remove_cvref_t<T>` to normalize types before performing classification.
5. Create a full specialization of `TypeValidator<bool>` with Boolean-specific behavior.
6. Create a partial specialization that recognizes pointer types.
7. Define a concept named `ValidNumericType` that accepts integral and floating-point types but rejects pointers and strings.
8. Implement a function template constrained by `ValidNumericType`.
9. Use `std::conditional_t` to choose between two types based on a compile-time condition.
10. Use `static_assert` to verify the expected behavior of the validator and the selected types.

**Additional challenge:** Implement a compile-time trait that detects whether a type supports both addition and multiplication. Use a `requires` expression to define the trait and test it with a built-in numeric type and a custom class.

**Hint:** Use `<type_traits>`, `<concepts>`, `std::remove_cvref_t`, `std::conditional_t`, template specialization, `requires` expressions, and `static_assert`. Compile using C++20.
