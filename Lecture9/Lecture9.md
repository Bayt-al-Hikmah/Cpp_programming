## Objectives
- Understand generic programming and use function and class templates to write reusable code.
- Apply template argument deduction, default parameters, specialization, and variadic templates to build flexible generic abstractions.
- Inspect and transform types at compile time using type traits, conditional types, and `static_assert`.
- Constrain templates with SFINAE, concepts, and `requires` clauses to ensure that generic code accepts appropriate types.
- Use `constexpr`, `consteval`, `if constexpr`, and template metaprogramming to perform computations and make decisions at compile time.

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
We are not limited only to Function templates in C++ we can also use Class templates while Function templates generalize operations. Class templates generalize the types of objects and data structures.

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

Function templates cannot be partially specialized. When a function template needs different behavior for particular argument types, we normally use function overloading, constraints, or explicit specialization.
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

In this example, the comma operator sequences the output operations from left to right.
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
Templates allow one implementation to work with different types, but not every type supports the same operations.

Consider a generic function that divides a value by two:
```cpp
template <typename T>
T halve(T value) {
    return value / 2;
}
```
This function works for many numeric types, but it may not make sense for every type. A pointer, for example, cannot be divided by an integer.

We could allow the compiler to report an error when an unsupported type is used. However, when designing a generic library, it is often better to inspect types explicitly, select suitable implementations, and provide meaningful compile-time diagnostics.

C++ provides **type traits** for examining type properties and **type transformations** for constructing modified types.
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

The `_v` forms, such as `std::is_integral_v<int>`, are convenient variable templates that expose the Boolean result directly. These traits do not inspect runtime values. They describe types known to the compiler.
#### Type Transformations
Sometimes the original type contains reference or qualifier information that is inconvenient for a generic operation.

For example:
```cpp
int value = 10;
int& reference = value;
```
The type `int&` is different from `int`. A template that needs to reason about the underlying value type may want to remove the reference.

C++ provides `std::remove_reference`:
```cpp
#include <iostream>
#include <type_traits>

int main() {
    using ReferenceType = int&;
    using ValueType = std::remove_reference_t<ReferenceType>;

    std::cout << std::is_same_v<ValueType, int> << '\n';
}
```
Here, `std::remove_reference_t<int&>` produces `int`. The `_t` suffix provides the resulting type directly.

Another useful transformation is `std::decay`. It approximates the type transformations that occur when an argument is passed by value: references and top-level cv-qualifiers are removed, and arrays and functions are converted to corresponding pointer types.
```cpp
#include <type_traits>

int main() {
    using A = std::decay_t<const int&>;
    using B = std::decay_t<int[5]>;

    static_assert(std::is_same_v<A, int>);
    static_assert(std::is_same_v<B, int*>);
}
```
`std::decay_t` is useful when a generic utility needs to determine the type that would typically be stored from an argument passed by value.

However, decay is not always desirable. If a function must preserve references, constness, or array information, applying decay indiscriminately can lose information.
#### Compile-Time Validation with `static_assert`
Type traits become particularly useful when combined with `static_assert`.

A `static_assert` checks a compile-time Boolean condition. If the condition is false, the program fails to compile.

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
The function is intended for arithmetic types, such as integers and floating-point values. If someone instantiates it with an unsupported type, the assertion provides a diagnostic explaining the requirement.

A `static_assert` does not make an unsupported operation valid. It provides an explicit compile-time check that communicates the intended restriction.
#### Selecting Types with `std::conditional_t`
Sometimes a template needs to select one of two types depending on a compile-time condition.

For this purpose, C++ provides `std::conditional_t`.
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
The condition determines which type is selected:
- `NumberType<true>::type` is `int`.
- `NumberType<false>::type` is `double`.

This is type selection rather than runtime selection. The chosen type must be determined during compilation.

Type traits and conditional types allow generic code to inspect types and adapt its implementation. However, selecting a type does not automatically guarantee that every operation on that type is valid. We still need a way to control which template implementations can be instantiated.

### Template Constraints and Conditional Instantiation
Consider the following template:
```cpp
template <typename T>
auto calculate(T value) {
    return value.size();
}
```
This function works for types that provide a suitable `size()` member, such as `std::string` and `std::vector`. It does not work for an ordinary integer.

When an unsupported type is supplied, the compiler attempts to instantiate the function and encounters an invalid expression.

**Template constraints make the requirements of generic code explicit.** They help control which implementations participate in overload resolution and provide clearer diagnostics when an argument does not satisfy the intended interface.
#### Template Substitution and SFINAE
SFINAE stands for **Substitution Failure Is Not An Error**. When the compiler tries to use a template with specific types, it may find that those types do not work with the template's declaration. Instead of producing an error, the compiler simply ignores that template as a possible match. This allows us to make templates available only for certain types.

For example, consider a template that should accept only integral types:
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
The expression:
```cpp
std::enable_if_t<std::is_integral_v<T>>
```
provides a valid type when the condition is true. When the condition is false, the substitution fails.

For example, an attempt to call `process(3.14)` would not find a viable overload in this program and it will fail to compile.
#### The Detection Idiom
Sometimes the requirement is not a built-in type property. Instead, we want to determine whether an expression is valid for a particular type.

For example, we may want to detect whether a type provides a `size()` member.

In modern C++, this can be expressed directly using a `requires` expression. Before C++20, libraries commonly used detection idioms based on `std::void_t` and substitution.

Here is a traditional implementation:
```cpp
#include <type_traits>
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
`std::declval` allows us to form an expression involving a hypothetical value of type `T` without constructing an actual object.

`decltype` obtains the type of the expression. If the expression is valid, `std::void_t` becomes `void`, allowing the specialization to match. If substitution fails, the primary template remains applicable.

The result is a trait that detects the existence of a suitable `size()` expression.
### Concepts and `requires` Clauses
A **concept** names a set of requirements that a type or expression must satisfy. Instead of encoding a condition indirectly through `enable_if`, we can describe the requirement directly.

For example:
```cpp
#include <concepts>
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
The concept `Arithmetic` describes the permitted category of types.

The declaration:
```cpp
template <Arithmetic T>
```
requires `T` to satisfy that concept.

An equivalent spelling is:
```cpp
template <typename T>
    requires Arithmetic<T>
T doubleValue(T value) {
    return value * 2;
}
```
Both forms constrain the template.

Concepts are more than named Boolean checks. They can also express requirements on the operations a type supports.

Consider a generic function that requires addition:
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
The `requires` expression checks whether `a + b` is a valid expression for the supplied type.

This is particularly useful when designing generic algorithms because the constraint describes the actual operation the implementation needs.
#### Combining and Composing Concepts
Concepts can be combined to describe more specific requirements.
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
The `Numeric` concept accepts integral and floating-point types. Concepts can also express multiple simultaneous requirements:
```cpp
template <typename T>
concept NumericLike =
    requires(T a, T b) {
        a + b;
        a * b;
    };
```
Here, the type must support both addition and multiplication.

The expressions inside a `requires` expression are checked for validity; they are not executed as runtime operations.
### Constrained Overloads
Sometimes different types need different implementations. Consider a function that distinguishes integral types from other arithmetic types:
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
Both templates have the same function name, but their constraints distinguish the intended argument categories.
## Compile-Time Programming and Metaprogramming
### Introduction
Normally, a function executes when the program runs. Its instructions operate on values available during execution.

However, some computations can be performed during compilation.

For example, a mathematical constant or a fixed configuration value may be known before the program starts. Computing such values at compile time can eliminate unnecessary runtime work and enable compile-time validation.
### Constant Expressions and `constexpr`
A constant expression is an expression that can be evaluated during compilation where the language requires or permits one.

The `constexpr` keyword allows a function to be evaluated at compile time when its arguments and operations satisfy the constant-expression rules.

Consider:
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
Because `result` is declared `constexpr`, its initializer must be a constant expression. The compiler evaluates `square(5)` at compile time.

However, a `constexpr` function is not restricted to compile-time execution.
```cpp
int value = 10;
int result = square(value);
```
Here, `value` is not a constant expression, so the call is evaluated at runtime.
### Static Initialization with `constinit`
Sometimes, a variable must be initialized before program execution reaches `main()`, without relying on dynamic initialization.

C++20 introduced `constinit` to guarantee static initialization for variables with static or thread storage duration.
```cpp
constinit int counter = 0;

int main() {
    counter = 10; // OK
}
```
The variable `counter` is initialized statically, but it can still be modified at runtime. Unlike `constexpr`, `constinit` does not make the variable constant.

For example:
```cpp
int getValue() {
    return 42;
}

// constinit int value = getValue(); // Ill-formed
```
The initializer requires a function call that cannot be evaluated as a constant expression, so it cannot satisfy the static initialization requirement.

Use `constinit` when a variable must be initialized statically but still needs to remain mutable at runtime. Use `constexpr` when the variable must also be a constant expression.
### Immediate Functions with `consteval`
Sometimes compile-time evaluation is not merely an optimization. It is a requirement of the interface.

C++20 introduced `consteval` for immediate functions
```cpp
consteval int cube(int value) {
    return value * value * value;
}

int main() {
    constexpr int result = cube(3);
}
```
The call to `cube(3)` must be evaluated at compile time. Unlike `constexpr`, `consteval` does not permit an ordinary runtime call using a value known only during execution.

For example:
```cpp
int value = 3;

// int result = cube(value); // Ill-formed
```
The argument is not a constant expression suitable for this immediate invocation.

Use `constexpr` when compile-time evaluation is possible and runtime evaluation remains useful. Use `consteval` when the function must enforce compile-time evaluation.
### Compile-Time Dispatch with `if constexpr`
Consider a generic function that behaves differently depending on the type of its argument.

One approach is to use ordinary conditional logic:
```cpp
if (condition) {
    // ...
} else {
    // ...
}
```
However, a normal `if` does not generally discard either branch during template instantiation. Both branches must be valid for the instantiated function, even if the condition is a compile-time constant.

`if constexpr`, introduced in C++17, solves this problem by discarding the non-selected branch during instantiation when the condition is a constant expression.
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
When `T` is `int`, the integral branch is selected. When `T` is `double`, the other branch is selected.

The distinction becomes more important when the branches contain operations that are valid for different types.

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
The pointer-specific behavior is instantiated only when the condition selects that branch.
### Template Metaprogramming
**Template metaprogramming** uses C++ templates to perform computations at compile time. A classic example is calculating a factorial using recursive template instantiation:
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
**How it works:**
- **Recursive case:** `Factorial<N>` calculates `N * Factorial<N - 1>::value`.
- **Base case:** `Factorial<0>` returns `1`, stopping the recursion.
- **Compile-time evaluation:** The compiler instantiates the required templates until it reaches the base case, producing the result `120`.

This technique demonstrates how templates can express computations that are resolved during compilation.

However, modern C++ offers a simpler alternative for many compile-time calculations: `constexpr` functions.
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

Here, `constexpr` allows the function to be evaluated at compile time when its arguments permit it. The `static_assert` verifies the result during compilation.
### Type-Level Programming
Templates can compute types as well as values. For example, `std::conditional_t` selects a type based on a compile-time condition, while `std::remove_reference_t` transforms a type.

We can combine these facilities to define a type-level decision:
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
For a non-pointer type, the resulting type is a pointer to that type. For a pointer type, the original type is retained. The compiler performs this type selection without constructing runtime objects.

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