# Enumerations, Structures, and Error Handling

## Learning Objectives
- Represent named states with enumerations and group related data with structures.
- Choose between `struct` and `class` based on the required interface and encapsulation.
- Recognize compile-time, runtime, and logic errors.
- Handle failures with exceptions, assertions, `std::optional`, and  `std::expected`.

## Enumerations, Structures, and Type Aliases
In the previous lecture, we learned how to create our own types using classes. We saw how a class groups data and functions into a single unit, allowing us to represent real-world entities such as students, cars, and other objects. We also explored how constructors initialize objects, how encapsulation protects their data, and how inheritance and polymorphism help us build more flexible programs.

However, classes are not the only way to define our own types in C++. Sometimes, we simply need to represent a value chosen from a predefined set of possibilities. In other situations, we want to group a few related values together without necessarily needing all the features of a class.

C++ provides several features for these situations. In this lecture, we will explore **enumerations**, **structures**, and **type aliases**, and learn when each one is useful.
### Enumerations
Let's suppose we want to create program that help use to make decision based on coin flip, a coin has two possible sides: heads or tails. to build this we need variable that represent **one value from a predefined set of possibilities**.

We could represent these states using integers. For example, `0` could mean head, `1` could mean tails.

But consider the following code:
```cpp
int coin = 1;
```
What does `1` represent? We cannot tell without remembering what each integer means.

We could use strings instead, but that introduces other problems, such as spelling mistakes and unnecessary comparisons.

C++ provides a better solution: **enumerations**. An enumeration defines a type whose values represent a fixed set of named possibilities.
#### Defining an Enumeration
To define an enumeration, we use the `enum` keyword, followed by the enumeration's name and a list of enumerators enclosed in curly braces `{}`.  
```cpp  
enum Coin {  
Heads,  
Tails  
};  
```  
Here:  
- `Coin` is the name of the enumeration type.  
- `Heads` and `Tails` are its enumerators.  
- The semicolon `;` terminates the declaration.

Once we have defined the enumeration, we can declare variables of type `Coin`.  
```cpp  
#include <iostream>

enum Coin {  
Heads,  
Tails  
};

int main() {  
Coin result = Heads;  
std::cout << result << '\n';  
return 0;  
}  
```  
**Output:**  
```  
0  
```  
Why does the program print `0` instead of `Heads`?

By default, an unscoped enumeration assigns integer values to its enumerators, starting at `0` and increasing by `1`. Therefore, the values in our enumeration are:

| Enumerator | Integer value |
| ---------- | ------------- |
| `Heads`    | `0`           |
| `Tails`    | `1`           |

The default values can be changed by assigning explicit integer values to the enumerators.  
#### Assigning Values to Enumerators
Consider an enumeration representing the faces of a dice.  
```cpp  
enum Dice {  
One = 1,  
Two,  
Three,  
Four,  
Five,  
Six  
};  
```  
In this example, we explicitly assign the value `1` to `One`.

The following enumerators receive consecutive values automatically.

| Enumerator | Integer value |
| ---------- | ------------- |
| `One`      | `1`           |
| `Two`      | `2`           |
| `Three`    | `3`           |
| `Four`     | `4`           |
| `Five`     | `5`           |
| `Six`      | `6`           |

We can also assign values individually.  
```cpp  
enum Status {  
Success = 0,  
Warning = 10,  
Error = 20  
};  
```  
#### Using Enumerations with `switch`
Enumerations are particularly useful with `switch` statements because they allow us to write code that handles each possible value explicitly.

Consider a program that simulates a dice roll. The player wins when the result is six and loses otherwise.  
```cpp  
#include <iostream>

enum Dice {  
	One = 1,  
	Two,  
	Three,  
	Four,  
	Five,  
	Six  
};

int main() {  
	Dice result = Six;

	switch (result) {  
		case One:  
		case Two:  
		case Three:  
		case Four:  
		case Five:  
		std::cout << "You lost :(\n";  
		break;
	
		case Six:  
		std::cout << "You won!\n";  
		break;  
	}
	
	return 0;  
}  
```
#### Scoped Enumerations: `enum class`
Although ordinary enumerations are useful, they have some limitations.

Consider the following example:  
```cpp  
enum Coin {  
Heads,  
Tails  
};

enum TrafficLight {  
Red,  
Yellow,  
Green  
};  
```  
Both enumerations declare their enumerators in the surrounding scope. As a result, names such as `Heads`, `Red`, and `Green` can be used directly.

This can cause problems when different enumerations contain enumerators with the same name.

For example:  
```cpp  
enum First {  
Value  
};

enum Second {  
Value  
};  
```  
This code is invalid because both enumerations declare an enumerator named `Value` in the same scope.

C++ provides scoped enumerations, declared using `enum class`, to avoid this problem.  
```cpp  
enum class Coin {  
Heads,  
Tails  
};

enum class TrafficLight {  
Red,  
Yellow,  
Green  
};  
```  
With `enum class`, the enumerators belong to their enumeration's scope.

To access an enumerator, we use the scope resolution operator `::`.  
```cpp
#include <iostream>

enum class Coin {  
Heads,  
Tails  
};

int main() {  
Coin result = Coin::Heads;  
std::cout << "Coin result: " << (result == Coin::Heads) << '\n';  
return 0;  
}  
```  
The important difference is that we must qualify the enumerators with their enumeration names:  
```cpp
Coin::Heads  
```  
We can also use scoped enumerations with `switch` statements.  
```cpp  
#include <iostream>

enum class TrafficLight {  
	Red,  
	Yellow,  
	Green  
};

int main() {  
	TrafficLight light = TrafficLight::Yellow;
	
	switch (light) {  
		case TrafficLight::Red:  
		std::cout << "Stop\n";  
		break;
		
		case TrafficLight::Yellow:  
		std::cout << "Prepare to stop\n";  
		break;
		
		case TrafficLight::Green:  
		std::cout << "Go\n";  
		break;  
	}
	
	return 0;  
}  
```  
#### Underlying Types
An enumeration has an underlying type, which is the integer type used to represent its values.

By default, the underlying type of an ordinary enumeration is implementation-defined, subject to the requirements of the C++ standard. A scoped enumeration without an explicitly specified underlying type uses `int`. we can explicitly specify the underlying type when we define an enumeration.

For example:  
```cpp  
enum class Direction : unsigned char {  
North,  
South,  
East,  
West  
};  
```  
Here, `Direction` uses `unsigned char` as its underlying type. 

We can also specify an underlying type for an ordinary enumeration.  
```cpp  
enum Status : int {  
Success = 0,  
Warning = 1,  
Error = 2  
};  
```  
We can retrieve an enumerator's underlying value using `static_cast`.  
```cpp  
#include <iostream>

enum class Direction : unsigned char {  
	North,  
	South,  
	East,  
	West  
};

int main() {  
	Direction direction = Direction::East;
	
	unsigned char value =  static_cast<unsigned char>(direction);
	
	std::cout << static_cast<int>(value) << '\n';
	
	return 0;  
}  
```  
We convert the value to `unsigned char` to obtain its underlying representation. We then convert it to `int` for printing because a character type is typically printed as a character rather than as a number.
### Structures
Imagine that we need to store information about a student. Each student has a name, an age, a student ID, and a grade.

These values describe the same entity, but they have different data types.

We could declare separate variables:
```cpp
std::string name;
int age;
int studentID;
double grade;
```
But this becomes inconvenient when we need to manage several students. We would have to maintain separate variables for each student and ensure that the correct values remain associated with one another.

Instead, we can define a new type that groups all these values together. C++ provides **structures**, declared using the `struct` keyword, for this purpose.
#### Defining and Using a Structure
Let's define our `Student` type:
```cpp
#include <string>

struct Student {
    std::string name;
    int age;
    int studentID;
    double grade;
};
```
Here, `Student` is a new type containing four member variables: `name`, `age`, `studentID`, and `grade`. Each object of type `Student` has its own values for these members.

Once the structure is defined, we can create objects of that type just as we create objects of a class.
```cpp
#include <iostream>
#include <string>

struct Student {
    std::string name;
    int age;
    int studentID;
    double grade;
};

int main() {
    Student student1;

    student1.name = "Ali";
    student1.age = 23;
    student1.studentID = 1001;
    student1.grade = 16.5;

    std::cout << "Name: " << student1.name << '\n';
    std::cout << "Age: " << student1.age << '\n';
    std::cout << "ID: " << student1.studentID << '\n';
    std::cout << "Grade: " << student1.grade << '\n';

    return 0;
}
```
The variable `student1` is an object of type `Student`. To access one of its members, we use the **member access operator**, represented by a dot `.`.

We can create another student in exactly the same way:
```cpp
Student student2;

student2.name = "Sara";
student2.age = 21;
student2.studentID = 1002;
student2.grade = 18.0;
```
Although both variables have the same type, each object maintains its own member values.
#### Structures and Classes: What's the Difference?
Before going further, let's connect structures directly to what we learned about classes.

In C++, a `struct` and a `class` are almost the same. Both can contain data members, member functions, constructors, destructors, access specifiers, static members, and other features we discussed in the previous lecture.

The main differences are their **default member access** and **default inheritance access**.

In a structure, members are `public` by default. In a class, members are `private` by default.

Consider these definitions:
```cpp
struct Student {
    std::string name;  // public by default
    int age;           // public by default
};

class StudentRecord {
    std::string name;  // private by default
    int age;           // private by default
};
```
With `Student`, we can access the members directly:
```cpp
Student student;
student.name = "Ali";
```
However, direct access to the members of `StudentRecord` is not allowed because those members are private. We would need to provide public member functions, such as setters and getters, to access them from outside the class.

The same distinction applies to inheritance: a structure uses `public` inheritance by default, while a class uses `private` inheritance by default..
#### Initialization of Structures
In our previous example, we created a `Student` object and assigned values to its members afterward.

C++ also allows us to initialize a structure when creating an object.

Consider the following definition:
```cpp
struct Student {
    std::string name;
    int age;
};
```
We can initialize an object using braces:
```cpp
Student student1{"Ali", 23};
```
The values are assigned to the members in the order in which they are declared.

In this example, `"Ali"` initializes `name`, and `23` initializes `age`.
#### Default Member Initializers
Sometimes, we want members to have sensible default values when an object is created without explicit initial values.

We can specify these defaults directly in the structure definition.
```cpp
struct Student {
    std::string name = "Unknown";
    int age = 0;
};
```
Now, we can create an object without providing any values:
```cpp
Student student1{};
```
Its `name` will be `"Unknown"` and its `age` will be `0`.

We can still override these defaults when creating an object:
```cpp
Student student2{"Ali", 23};
```
Here, `student2` has the name `"Ali"` and age `23`.
### Designated Initializers
When a structure contains many members, initializing it by position can become difficult to read.

For example:
```cpp
struct Student {
    std::string name;
    int age;
    int studentID;
    double grade;
};
```
We could initialize a student as follows:
```cpp
Student student1{"Ali", 23, 1001, 16.5};
```
This works, but we must remember the order of the members.

Modern C++ provides **designated initializers**, introduced in C++20, which allow us to specify members by name.
```cpp
Student student1{
    .name = "Ali",
    .age = 23,
    .studentID = 1001,
    .grade = 16.5
};
```
This makes the initialization more descriptive, especially when a structure contains several members of similar types.

There is one important restriction: in C++, designated initializers must follow the declaration order of the members.

For example, if `name` is declared before `age`, then `.name` must appear before `.age`.
#### Nested Structures
Our `Student` structure has contained only simple values. But a structure can also contain members of other user-defined types.

For example, a student may have an address consisting of a city and a street.

Instead of storing the city and street directly inside `Student`, we can define a separate structure to represent an address.
```cpp
#include <string>

struct Address {
    std::string city;
    std::string street;
};

struct Student {
    std::string name;
    int age;
    Address address;
};
```
Here, `Student` contains an `Address` member. The `address` member is itself an object with two members: `city` and `street`.

We can initialize a student, including the address, as follows:
```cpp
Student student1{
    "Ali",
    23,
    {"Algiers", "Didouche Mourad"}
};
```
We can then access the nested members using the dot operator:
```cpp
#include <iostream>
#include <string>

struct Address {
    std::string city;
    std::string street;
};

struct Student {
    std::string name;
    int age;
    Address address;
};

int main() {
    Student student1{
        "Ali",
        23,
        {"Algiers", "Didouche Mourad"}
    };

    std::cout << "Name: " << student1.name << '\n';
    std::cout << "City: " << student1.address.city << '\n';
    std::cout << "Street: " << student1.address.street << '\n';

    return 0;
}
```
Consider the expression:
```
student1.address.city
```
We first access the `address` member of `student1`. Then, we access the `city` member of that address.
#### Pointers to Structures
We have already studied pointers and object addresses. The same principles apply to structures because a structure defines an ordinary object type.

A pointer can store the address of a structure object, allowing us to access that object indirectly.

Consider the following example:
```cpp
#include <iostream>
#include <string>

struct Student {
    std::string name;
    int age;
};

int main() {
    Student student1{"Ali", 23};

    Student* ptr = &student1;

    std::cout << ptr->name << '\n';
    std::cout << ptr->age << '\n';

    return 0;
}
```
Let's examine the important statement:
```cpp
Student* ptr = &student1;
```
`Student*` declares a pointer to a `Student` object, while `&student1` obtains the address of `student1`. The pointer `ptr` now stores that address.

When accessing a member through a pointer, C++ provides the **arrow operator**, written as `->`.

For example:
```cpp
ptr->name
ptr->age
```
These expressions are equivalent to:
```
(*ptr).name
(*ptr).age
```
#### Dynamically Allocating a Structure
We can also create a structure object dynamically using `new`, just as we can dynamically allocate other objects.
```cpp
#include <iostream>
#include <string>

struct Student {
    std::string name;
    int age;
};

int main() {
    Student* student1 = new Student{"Ali", 23};

    std::cout << student1->name << '\n';
    std::cout << student1->age << '\n';

    delete student1;

    return 0;
}
```
The expression:
```cpp
new Student{"Ali", 23}
```
dynamically creates a `Student` object and initializes its members. The returned pointer stores the address of that object.

After we finish using it, we release the dynamically allocated object with:
```cpp
delete student1;
```
### `typedef` and `using`
We have now seen how enumerations define named values and how structures group related data into a single type.

As programs grow, we may also encounter situations where a type has a long or inconvenient name. Sometimes, we want to give an existing type a shorter name, or provide an alternative name that better describes its purpose.

C++ allows us to do this through **type aliases**: `typedef` and `using`..

A type alias introduces another name for an existing type. It does not create a completely new type.
#### Using `typedef`
The `typedef` keyword creates an alias for an existing type.

For example:
```cpp
typedef unsigned int UInt;
```
Now, `UInt` can be used as an alternative name for `unsigned int`.
```cpp
#include <iostream>

typedef unsigned int UInt;

int main() {
    UInt number = 100;

    std::cout << number << '\n';

    return 0;
}
```
The important point is that `UInt` and `unsigned int` refer to the same type. We have not defined a new type with different behavior; we have simply introduced another name for an existing one.
#### Using `using` to Create Type Aliases
Modern C++ provides the `using` keyword as an alternative to `typedef`.

For example:
```cpp
using UInt = unsigned int;
```
This creates the same type alias as our earlier example.
```cpp
#include <iostream>

using UInt = unsigned int;

int main() {
    UInt number = 100;

    std::cout << number << '\n';

    return 0;
}
```
The main advantage of `using` is readability. Its syntax makes the relationship between the new name and the existing type easier to recognize.
#### Type Aliases for Pointers and More Complex Types
Type aliases become particularly useful when the original type is long or difficult to read.

Suppose we frequently work with pointers to students:
```cpp
struct Student {
    std::string name;
    int age;
};
```
We could declare a pointer like this:
```cpp
Student* studentPtr;
```
Alternatively, we could introduce an alias:
```cpp
using StudentPtr = Student*;
```
Then we can write:
```cpp
StudentPtr studentPtr;
```
Both declarations mean the same thing: `studentPtr` is a pointer to a `Student` object.

Type aliases can also be useful for more complex types, including function pointers, container types, and template specializations. We will encounter these situations as our programs become more advanced.
```c++
#include <iostream>

using Operation = int (*)(int, int);

int add(int a, int b){
    return a + b;
}

int multiply(int a, int b){
    return a * b;
}

int main(){
    Operation op = add;

    std::cout << op(5, 3) << std::endl;

    op = multiply;

    std::cout << op(5, 3) << std::endl;

    return 0;
}
```
In this example, we use `using` to create an alias called `Operation` for a function pointer that takes two integers as arguments and returns an integer.

We then declare two functions, `add()` and `multiply()`, which perform addition and multiplication, respectively.

Inside `main()`, we declare a function pointer `op` of type `Operation` and assign it to `add`. When we call `op(5, 3)`, it executes `add(5, 3)` and returns `8`.

Next, we assign `multiply` to the same pointer. Now, calling `op(5, 3)` executes `multiply(5, 3)` and returns `15`.
## Handling Errors
### Introduction
When we write programs, we usually focus on what the program should do: calculate a result, process some data, communicate with a device, or interact with a user. However, a program must also deal with situations in which something goes wrong. The user might enter an invalid value, a file might not exist, a resource might be unavailable, or a calculation might receive unexpected input.

Consider a program that divides two numbers. Under normal conditions, the program reads the values and calculates their quotient. But what should happen if the second number is zero? Or imagine a program that opens a configuration file before starting a system. What should happen if the file cannot be found?

We could write conditions to check every possible problem before performing an operation. This is often a good approach, but as programs become larger, handling every failure directly inside the normal execution path can make the code difficult to read and maintain.

C++ provides several mechanisms for dealing with errors. We can detect problems using conditions, report failures through error codes, represent optional results with `std::optional`, communicate either a result or an error using `std::expected`, or use exceptions to transfer control to code responsible for handling a failure. We also have assertions to verify assumptions and debugging tools to investigate unexpected behavior.
### Types of Errors
Before looking at the mechanisms C++ provides, it is useful to distinguish the different problems we may encounter while developing a program. Not every error can be handled in the same way, and some should be prevented rather than handled at runtime.
#### Compilation errors
**Compilation errors** occur when the compiler cannot translate the program into an executable. For example, attempting to use an undeclared variable or passing an argument of an incompatible type may produce a compilation error. These problems must be corrected in the source code before the program can be built successfully.

Syntax errors are a common category of compilation errors. They occur when the source code does not follow the language's grammar, such as when a required semicolon is missing or parentheses are incorrectly placed. Modern C++ compilers also detect many type-related errors, helping us identify mistakes before the program runs.
#### Runtime errors
**Runtime errors** occur during execution. A program might fail to open a file, receive invalid input, run out of memory, or encounter a situation that prevents an operation from completing. Some runtime failures can be detected and handled, while others, such as certain forms of undefined behavior, cannot be reliably recovered from.
#### Arithmetic Errors 
Arithmetic operations also require attention. Integer division by zero, for example, results in undefined behavior in C++, whereas floating-point division by zero generally follows the rules of the floating-point environment and may produce infinity or NaN. These cases should not be treated as identical.
#### Logic Errors
**Logic errors** are different because the program may compile and execute without reporting any problem, yet produce the wrong result. A condition might be reversed, a loop might execute too many times, or a control algorithm might use an incorrect equation. These errors often require testing, careful inspection, and debugging rather than exception handling.
#### Resource Errors
Finally, **resource-related errors** occur when the program cannot obtain or use a required resource. Examples include a failed file operation, an unsuccessful memory allocation, or an unavailable hardware resource. The appropriate response depends on the resource and the operation: we might retry, report the failure, select an alternative, or terminate the operation safely.
### Catching and Handling Errors
One approach to handling a failure is to detect it where it occurs and respond immediately. For example, before dividing two numbers, we can check whether the divisor is zero. Before using a file, we can check whether it opened successfully.

This approach is appropriate when failure is expected and easy to handle locally. However, sometimes the code that detects a problem is far away from the code that knows how to respond to it. A low-level function might discover that an operation failed, while a higher-level function decides whether to retry, notify the user, or cancel the current task.

C++ exceptions provide a way to connect these two parts without forcing every intermediate function to return an error code. The mechanism uses three keywords: `try`, `throw`, and `catch`.

#### The `try`, `throw`, and `catch` Keywords
The `try` keyword marks a region in which exceptions may be handled by associated handlers. It does not prevent exceptions from occurring, nor does it guarantee that an exception will be caught.

The `catch` keyword declares a handler for an exception of a particular type.
```cpp
catch (const std::runtime_error& e) {
    std::cerr << e.what() << '\n';
}
```
Here, `e` refers to the exception object, and `e.what()` provides a description of the failure.

The `throw` keyword raises an exception. We can throw a standard exception object, a custom exception object, or another permitted type.
```cpp
throw std::runtime_error("The operation failed.");
```
When this statement executes, the current function does not continue normally from that point. Instead, control transfers toward a matching exception handler. If a matching handler is found, execution continues inside that handler. If no matching handler exists, the program eventually calls `std::terminate`, which normally terminates the program.

We can use several handlers to respond differently to different exception types:
```cpp
try {
    // An operation that may throw
}
catch (const std::invalid_argument& e) {
    // Handle an invalid argument
}
catch (const std::out_of_range& e) {
    // Handle an out-of-range value
}
catch (const std::exception& e) {
    // Handle other standard exceptions
}
```
The order matters because a handler for a base class can also match exceptions of its derived classes. For example, `std::invalid_argument` and `std::out_of_range` both derive from `std::logic_error`, which derives from `std::exception`. If we place `catch (const std::exception& e)` first, the more specific handlers that follow it will never be reached.

A catch-all handler is also available:
```cpp
catch (...) {
    // Handle an exception without inspecting its type
}
```
This handler can catch exceptions of different types, including types that do not derive from `std::exception`. However, it does not provide an exception object that we can inspect directly. 
### Raising Errors with Standard Exceptions
The C++ standard library already provides exception types for many common situations. To use the standard exception classes discussed here, we include `<stdexcept>`.

Some useful types are:
- `std::invalid_argument` indicates that an argument does not satisfy the function's requirements.
- `std::out_of_range` indicates that an index, value, or other quantity is outside an allowed range.
- `std::runtime_error` represents a runtime failure that does not fit a more specific category.
- `std::logic_error` represents a problem associated with the program's logic or with violating an operation's requirements.

These types form part of an inheritance hierarchy, so we can catch a specific type when we need to distinguish a failure or catch a common base class when several failures can be handled in the same way.

Let's look at a practical example:
```cpp
#include <iostream>
#include <stdexcept>

double divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        throw std::invalid_argument(
            "The denominator must not be zero."
        );
    }

    return numerator / denominator;
}

int main() {
    try {
        const double result = divide(10.0, 0.0);
        std::cout << "Result: " << result << '\n';
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "Operation failed: " << e.what() << '\n';
    }
}
```
The `divide` function is responsible for enforcing its own precondition. It does not decide how the entire application should react to the failure; it reports the problem by throwing an exception. The caller decides how to handle it.
### Creating Custom Exceptions
Standard exceptions cover many common errors, but sometimes an application needs more descriptive error types. For example, in a scientific application, we might want to report division by zero using a specific exception named `DivisionByZeroError` rather than a general exception such as `std::invalid_argument`.

C++ allows us to create custom exceptions using classes. A common approach is to derive them publicly from `std::exception` and override its virtual `what()` function to provide an error message.

Here is an example:
```cpp
#include <exception>
#include <iostream>
#include <string>

class DivisionByZeroError : public std::exception {
private:
    std::string message;

public:
    explicit DivisionByZeroError(std::string msg)
        : message(std::move(msg)) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

double divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        throw DivisionByZeroError(
            "Cannot divide by zero."
        );
    }

    return numerator / denominator;
}

int main() {
    try {
        std::cout << divide(10.0, 0.0) << '\n';
    }
    catch (const DivisionByZeroError& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
```
Let's examine the most important parts of this example.

First, `DivisionByZeroError` inherits publicly from `std::exception`. Public inheritance allows our custom exception to use the standard exception interface, making it compatible with common exception-handling practices.

The constructor initializes the error message using a **member initializer list**:
```cpp
explicit DivisionByZeroError(std::string msg)
    : message(std::move(msg)) {}
```
The `std::move` operation allows the string to be moved into `message` when possible, avoiding an unnecessary copy. It requires the `<utility>` library to be included. The `explicit` keyword prevents unintended implicit conversions from a string to a `DivisionByZeroError`.

The most important function is `what()`:
```cpp
const char* what() const noexcept override {
    return message.c_str();
}
```
This function provides the error message through the standard exception interface. Its declaration contains several important elements:
- **`const char*`** specifies that the function returns a pointer to constant characters, matching the return type required by `std::exception::what()`.
- **`const`** after the parameter list means the function does not modify the exception object's state.
- **`noexcept`** guarantees that the function will not allow an exception to escape, matching the base class's contract.
- **`override`** tells the compiler that this function overrides an inherited virtual function. If its signature is incompatible, the compiler reports an error.
- **`message.c_str()`** returns a pointer to the string's null-terminated character data, allowing the message to be accessed as a C-style string.

### Stack Unwinding
So far, we have focused on how to throw an exception and how to catch it. But what happens to the program between those two operations?

Consider a function that calls another function, which then calls a third function. If the third function throws an exception, execution cannot simply continue from the statement following the function call. C++ must locate a suitable handler, potentially in one of the calling functions.  To do this, the language uses a process called **stack unwinding**.

Consider the following example:
```cpp
#include <iostream>
#include <stdexcept>

void third() {
    std::cout << "Entering third()\n";

    throw std::runtime_error("Something went wrong");

    std::cout << "Leaving third()\n";
}

void second() {
    std::cout << "Entering second()\n";
    third();
    std::cout << "Leaving second()\n";
}

void first() {
    std::cout << "Entering first()\n";
    second();
    std::cout << "Leaving first()\n";
}

int main() {
    try {
        first();
    }
    catch (const std::exception& e) {
        std::cerr << "Caught: " << e.what() << '\n';
    }
}
```
When `main()` calls `first()`, which calls `second()`, which calls `third()`, the program runs normally until an exception is thrown. At that point, the remaining statements in these functions are skipped, and C++ searches for a matching `catch` block, moving back through the function calls.

As the exception moves outward, local objects are destroyed as their scopes are exited. This process is called **stack unwinding**. 
### RAII and Exceptions
Imagine that a function opens a file, acquires a mutex, or allocates a resource that must eventually be released. If the function exits normally, we can release the resource at the end. But what happens if an exception is thrown before execution reaches that cleanup code?

Consider this example:
```cpp
void process() {
    Resource* resource = acquire_resource();

    perform_operation(); // May throw

    release_resource(resource);
}
```
If `perform_operation()` throws, the call to `release_resource()` is skipped. The resource may remain allocated or locked, leading to a resource leak or another serious problem.

We could attempt to fix this by placing cleanup operations inside every possible `catch` block. However, as a function becomes more complex, this approach becomes difficult to maintain and easy to get wrong.

C++ provides a better solution through **Resource Acquisition Is Initialization (RAII)**.

The central idea is simple: associate the lifetime of a resource with the lifetime of an object. The object acquires the resource during construction and releases it during destruction. When the object goes out of scope, its destructor automatically performs the cleanup, including during stack unwinding.

Modern C++ provides many RAII types in the standard library, including `std::vector`, `std::string`, `std::unique_ptr`, `std::lock_guard`, and `std::scoped_lock`.

For example:
```cpp
#include <iostream>
#include <memory>
#include <stdexcept>

void process() {
    auto value = std::make_unique<int>(42);
    std::cout << "Resource acquired\n";
    throw std::runtime_error("Processing failed");

    // The unique_ptr destructor still releases the resource.
}

int main() {
    try {
        process();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
```
Here, `std::make_unique<int>(42)` creates an integer managed by a `std::unique_ptr`. The pointer has exclusive ownership of the allocated object.

When `process()` throws an exception, stack unwinding destroys the local `unique_ptr`. Its destructor releases the allocated integer automatically.
### Exception Safety
Now that we understand stack unwinding and RAII, we can ask another important question: **what happens to an object's state when an exception occurs?**

Even if all resources are released correctly, an object might be left partially modified. For example, imagine transferring money between two bank accounts. If we subtract money from the first account but fail to add it to the second, the total balance becomes incorrect.

To prevent such problems, C++ defines three common levels of exception safety: the basic guarantee, the strong guarantee, and the no-throw guarantee.
#### The Basic Guarantee
The basic guarantee means that after an exception, objects remain in a valid state and resources are not leaked. However, their values may have changed.

Consider a function that processes several values and updates a container one element at a time. If processing the fourth element fails, the first three elements might already have been updated. Under the basic guarantee, those changes are allowed, provided the container and all involved objects remain valid.
#### The Strong Guarantee
The strong guarantee goes further: if an operation fails, the program state covered by the guarantee remains unchanged. The operation either succeeds or has no effect.

One way to achieve this is to perform the work on temporary data and apply the changes only after everything succeeds.

Consider this example:
```cpp
#include <stdexcept>
#include <string>

void update_name(std::string& name, std::string new_name) {
    if (new_name.empty()) {
        throw std::invalid_argument("Name cannot be empty.");
    }

    name.swap(new_name);
}
```
The function first checks the new name. If it is empty, an exception is thrown, and the original name remains unchanged. Otherwise, the function swaps the strings to apply the update.
#### The No-Throw Guarantee
The no-throw guarantee means that a function will not allow an exception to escape.

For example, destructors should normally release resources without throwing exceptions, especially during stack unwinding. We can also declare our own functions as non-throwing using `noexcept`:
```cpp
void cleanup() noexcept {
    // Release resources safely.
}
```
However, `noexcept` is a contract, not a way to handle errors. If an exception escapes from a `noexcept` function, C++ calls `std::terminate`.
### Assertions:
Exceptions help us respond to failures that may occur during normal program execution. Assertions serve a different purpose: they help us verify assumptions that should already be true if the program is correct.

Suppose we write a function that calculates the square root of a value and expect its caller to provide a non-negative number. We might want to verify that assumption during development.

C++ provides the `assert()` macro through the `<cassert>` header.
```cpp
#include <cassert>

double square_root_input(double value) {
    assert(value >= 0.0);

    return value;
}
```
If assertions are enabled and the condition evaluates to `false`, the assertion reports a failure and terminates the program. 

However, assertions are not a substitute for validating user input. They can be disabled when `NDEBUG` is defined, so a program must not depend on an assertion to enforce a requirement that must always be checked.
#### Compile time Assertions
The `assert()` macro checks a condition at runtime. C++ also provides `static_assert`, which checks a condition at compile time.
```cpp
#include <iostream>

int main() {
    static_assert(10 > 5, "The condition must be true.");

    std::cout << "Program compiled successfully.\n";

    return 0;
}
```
Unlike `assert()`, `static_assert` does not wait for the program to execute. The compiler checks the condition when it can evaluate it, and a failed assertion prevents successful compilation of the relevant code.
### Handling Failures Without Exceptions
Exceptions are not the only way to report errors. In many systems, a function returns a status value indicating whether an operation succeeded.

For example, a function might return `true` when an operation succeeds and `false` when it fails. The caller can then inspect the result and decide what to do.
```cpp
#include <iostream>

bool divide(double a, double b, double& result) {
    if (b == 0.0) {
        return false;
    }

    result = a / b;
    return true;
}

int main() {
    double result{};

    if (divide(10.0, 2.0, result)) {
        std::cout << "Result: " << result << '\n';
    }
    else {
        std::cerr << "Division failed.\n";
    }
}
```
In this example, `divide()` returns `false` when the divisor is zero and `true` when the calculation succeeds. The output parameter `result` receives the calculated value only on success.

This is simple, but a Boolean does not explain why an operation failed. If a function can fail for several reasons, we might need a more descriptive error code.
```cpp
enum class DivideError {
    none,
    division_by_zero,
    invalid_input
};
```
A function can return one of these values, or use a result structure containing both a status and the calculated result.
#### When a Value Might Not Exist `std::optional`:
Sometimes an operation does not fail in the sense of an exceptional event. Instead, it simply might not produce a value.

Imagine a function that searches for a sensor by its identifier. If the sensor exists, the function returns it. If the sensor is not registered, there is no result to return.

C++17 introduced `std::optional` to represent a value that may or may not exist.
```cpp
#include <iostream>
#include <optional>

std::optional<int> find_sensor_id(bool found) {
    if (found) {
        return 42;
    }

    return std::nullopt;
}

int main() {
    const auto sensor = find_sensor_id(true);

    if (sensor.has_value()) {
        std::cout << "Sensor ID: " << *sensor << '\n';
    }
    else {
        std::cout << "Sensor not found.\n";
    }
}
```
The return type `std::optional<int>` means that the function may return an integer or no value at all. When the sensor is found, returning `42` constructs an optional containing that integer. When the sensor is absent, returning `std::nullopt` indicates that the optional contains no value.

The caller can use `has_value()` to check whether a result exists, or simply write:
```cpp
if (sensor) {
    std::cout << *sensor << '\n';
}
```
#### Returning Either a Value or an Error with `std::expected`
Sometimes, a function can fail for different reasons. For example, when reading a sensor, the sensor might be unavailable or return invalid data. Using `std::optional` tells us whether a value exists, but it does not explain why the operation failed.

C++23 introduced `std::expected` to handle this situation. It stores either a successful value or an error, making both outcomes explicit in the function's return type.

Consider a simple function that divides two numbers:
```cpp
#include <expected>
#include <iostream>

std::expected<double, const char*> divide(double a, double b) {
    if (b == 0) {
        return std::unexpected("Division by zero.");
    }

    return a / b;
}

int main() {
    auto result = divide(10, 2);

    if (result) {
        std::cout << "Result: " << *result << '\n';
    } else {
        std::cout << "Error: " << result.error() << '\n';
    }

    return 0;
}
```
If the division succeeds, the function returns the result. If the divisor is zero, it returns an error instead.

The expression `std::unexpected(...)` explicitly constructs the error alternative. The caller can test the result with `if (result)`, access the successful value using `*result`, or retrieve the error using `result.error()` when the result contains an error.
## Tasks
### Task 1:
Write a program in C++ to represent a collection of students. Each student should have the following details:
- Name (`string`)
- Age (`int`)
- Student ID (`int`)
- Grade (`double`)

The program should ask the user how many students they want to register. Afterward, the user should enter the details of each student, which should be stored in a vector. Once all the information has been entered, the program should display the details of every student.
### Task 2:
Write a program in C++ to manage a collection of sensors. Each sensor should have the following details:
- ID (`int`)
- Name (`string`)
- Measurement value (`double`)
- Status (`enum class` with values `Active`, `Inactive`, and `Faulty`)

The program should ask the user how many sensors they want to register, then request the details of each sensor. After storing the information in a vector, the program should display all sensors and their statuses.
### Task 3:
Write a program in C++ that implements a calculator supporting addition, subtraction, multiplication, and division.

The program should ask the user to enter two numbers and select an operation. It should calculate and display the result. If the user attempts to divide by zero or enters an invalid operation, the program should report the error without crashing unexpectedly.
### Task 4:
Write a program in C++ to monitor a sensor that measures temperature. The sensor accepts readings between `-40.0` and `125.0` degrees Celsius.

The program should repeatedly ask the user to enter a temperature reading. If the reading is within the permitted range, display it as valid. Otherwise, report an error explaining that the reading is outside the allowed range.

The program should continue until the user chooses to exit.
#### Hint:  
Create a custom exception class named `InvalidTemperatureError` derived publicly from `std::exception`. Override the `what()` function to provide an appropriate error message. Use RAII and standard library types to manage resources safely.
### Task 5:
Write a program in C++ to process numeric values entered by the user.

The program should ask the user to enter a number as a string and attempt to convert it into a numeric value. If the input is valid, display the converted number. If the input is empty or cannot be converted, report the appropriate error.

The program should also verify that the converted number falls within a specified range, such as `0` to `100`.
#### Hint:  
Use `std::optional` to represent a value that might be absent and `std::expected` (C++23) to represent either a successful conversion or an error. Use `assert()` to verify runtime assumptions and `static_assert` to check compile-time requirements.
  
