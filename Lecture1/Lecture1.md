# C++ Foundations: Variables, Types, and Input/Output

## Learning Objectives
- Understand the basic roles of the CPU, memory, source code, and compiler.
- Write, compile, and run a small C++ program.
- Declare variables and choose suitable built-in and standard-library types.
- Perform arithmetic and convert between compatible types safely.
- Read input and display formatted output.
## How a Computer Works
We all have computers, and we use them for a variety of purposes, including watching videos, playing games, performing mathematical calculations, communicating with friends, and many other applications. But the fundamental question is: how do these devices actually work?

The answer lies in their electrical nature. Computers are essentially electrical devices that perform all calculations using electrical signals. The central processing unit (CPU), often referred to as the "brain" of the computer, executes these calculations. To temporarily store data while the computer is in operation, it relies on memory, specifically Random Access Memory (RAM).  
Crucially, all information within a computer is represented by electrical signals. This includes data stored in memory and the instructions that the CPU executes. These electrical signals can have only two distinct states: presence, typically represented by the digit "1," and absence, represented by "0."  
With this binary representation in mind, we can understand that CPU instructions are essentially sequences of 1s and 0s. This sequence of binary digits is known as machine code, which is the most fundamental level of programming language that the CPU can directly understand

## Introduction to Programming Languages
A **programming language** provides rules and symbols for expressing instructions in a form that people can write and understand. Languages such as C++ make it easier to build, read, test, and maintain programs than writing machine code directly.

A **compiler** translates source code into lower-level code and reports many errors before the program runs. A **linker** combines the compiled parts of a program and the libraries it uses to create an executable. When the executable runs, the operating system loads it and begins execution at the program's entry point, usually `main()` in a C++ program.
## C++ Programming
### Introduction
C++ is a powerful, general-purpose programming language widely used for developing high-performance and resource-efficient software. It originated as an extension of the C programming language, but over time it evolved into a distinct language with its own features, standard library, and programming paradigms.

C++ supports multiple programming paradigms, including procedural programming, object-oriented programming (OOP), generic programming, and functional programming. This flexibility allows developers to choose the programming techniques that best fit a particular problem.

C++ is used in a wide range of applications, including game engines, operating systems, web browsers, databases, desktop applications, embedded systems, robotics, and high-performance computing. It is particularly valuable when performance, memory control, and direct interaction with hardware are important.

One of the major strengths of C++ is its ability to provide low-level control over system resources while still offering high-level abstractions. Developers can directly manage memory, work with pointers and references, interact with hardware interfaces, and control how data is represented and processed.

However, C++ programs are normally compiled into machine code for a specific target platform. The resulting executable is therefore generally not portable across different processor architectures or operating systems. For example, an executable compiled for an x86-64 processor will generally not run directly on an ARM processor. The C++ source code itself, however, can often be recompiled for different platforms with little or no modification, provided the program does not depend on platform-specific features.

This combination of high-level abstractions, low-level control, performance, and flexibility is what makes C++ an important language for systems and performance-critical software.
### Text Editor and IDE
To write and develop C++ programs, we need a program that allows us to create and edit our source code. There are two common approaches: using a **text editor** or using an **IDE (Integrated Development Environment)**.
#### Text Editor
**A text editor** is a program used to create and edit text files. We can use a text editor to write C++ source code and save it in files such as `.cpp` files.

However, a text editor usually does not compile or execute C++ programs by itself. To run our C++ program, we need a **C++ compiler**, which translates our C++ source code into machine code that the computer can execute.

For example, we could write our code using a text editor and then use a compiler such as **GCC** or **Clang** from the command line to compile it.
#### IDE
**An IDE (Integrated Development Environment)** is a software application that brings together several tools needed for software development. A typical C++ IDE provides a **code editor, compiler/build tools, debugger, project management tools, and other development features** in a single environment.

An IDE can make development easier because we can write our code, compile it, run it, and debug it from the same application. However, an IDE does not necessarily include its own compiler. Depending on the IDE, a compiler may need to be installed separately and configured for the IDE to use it.

Examples of popular environments used for C++ development include **Visual Studio, Visual Studio Code, CLion, Qt Creator, and Code::Blocks**.
### Running Our First C++ Program
Now that we understand the difference between a text editor, an IDE, and a compiler, let's create and run our first C++ program.

A C++ program commonly contains a few important elements, such as **preprocessor directives, declarations and definitions, and functions**. The most important function is the `main()` function, where program execution begins.

```cpp
#include <iostream>

using namespace std;

int main(){
    cout << "Hello, Reader\n";

    return 0;
}
```
This program simply displays **"Hello, Reader"** on the screen. Before we learn how to run it, let's first understand the main parts that make up the program.

The first line:
```cpp
#include <iostream>
```
is a **preprocessor directive**. It tells the preprocessor to include the `iostream` header, which provides the declarations needed for standard input and output, including `cout` and `cin`.

Next:
```cpp
using namespace std;
```
allows us to use names from the `std` namespace without writing `std::` every time. For example, `cout` is actually `std::cout`. A namespace is used to organize names and help prevent naming conflicts.    

The next part is the `main()` function:
```cpp
int main()
{
    // ...
}
```
The `main()` function is the **entry point of a C++ program**. When the program starts, execution begins inside this function. The `int` specifies that `main()` returns an integer, while the empty parentheses indicate that this version of `main()` takes no parameters.

The statements inside the curly braces `{}` form the body of the function. This is where we place the instructions that should be executed when the program runs.

Inside `main()`, we have:
```cpp
cout << "Hello, Reader\n";
```
Here, `cout` is used to send text to the standard output, usually the terminal or console. The `<<` operator inserts the text into the output stream. The `\n` represents a **newline**, so anything printed afterward will appear on the next line.

Finally:
```cpp
return 0;
```
ends the `main()` function and returns the value `0` to the operating system. By convention, a return value of `0` indicates that the program finished successfully. In modern C++, reaching the closing `}` of `main()` automatically returns `0`, so writing `return 0;` is optional.
#### Running the Program
Writing the C++ source code is not enough for the computer to execute it directly. The source code must first be **compiled** into an executable program.

First, we save our source code in a file with the `.cpp` extension, for example:
```
main.cpp
```
We then use a C++ compiler such as GCC, Clang, or MSVC to compile this source file. The compiler processes the C++ code, checks it for errors, and translates it into machine code that the computer can execute.

For example, using GCC, we can compile the program with:
```shell
g++ main.cpp -o main
```
Here, `g++` invokes the C++ compiler. `main.cpp` is the source file we want to compile, and `-o main` tells the compiler to name the resulting executable `main`.

If the compilation succeeds, an executable file is created. On Linux and macOS, we can run it with:
```shell
./main
```
On Windows, the executable will normally have an `.exe` extension, so it can be run as:
```shell
main.exe
```
When we run the executable, the operating system loads the program and begins its execution at the `main()` function. The `cout` statement then sends the message to the console:
```
Hello, Reader
```
When using an IDE, these steps are usually handled for us. Instead of manually typing the compiler command, we can use options such as **Build**, **Compile**, or **Run**. The IDE invokes the compiler in the background and then starts the resulting executable.
### Variables:
So far, we have created and run a simple C++ program that displays a message on the screen. However, real programs do much more than display fixed text. They need to store, process, and manipulate data.

For example, a program might need to store a user's age, the price of a product, the number of items in a shopping cart, or a person's name. To work with this information, we need a way to store data in the computer's memory while the program is running.

In C++, we use **variables** to store and work with data.

A variable is a named location in memory used to store a value, We can think of a variable as a labeled container. The container has a name, and it holds a value that the program can read, modify, and use in calculations.

For example:
```cpp
int age = 25;
```
Here, `age` is a variable that stores the value `25`. The value stored in a variable can also change while the program is running:
```cpp
int age = 25;

age = 26;
```
### Data Types in C++
A variable allows us to store data, but not all data is the same. A program may need to work with whole numbers, decimal numbers, characters, text, or logical values such as `true` and `false`.

C++ does not treat all these values in the same way. Different kinds of data require different representations in memory and support different operations.

For example, we can perform arithmetic operations on numbers:
```cpp
int age = 25;
int nextAge = age + 1;
```
But it would not make sense to perform the same operations on a piece of text:
```cpp
string name = "Alice";
```
This is where **data types** come in.

A **data type** specifies what kind of value a variable can store. It also determines how that value is represented and which operations can be performed on it.   
For example:
```cpp
int age = 25;
double price = 19.99;
char grade = 'A';
bool isOnline = true;
```
#### Integer Types
Integer types are used to store **whole numbers**, meaning numbers without a fractional part.

The most commonly used integer type is `int`:
```cpp
int age = 25;
int score = 100;
int temperature = -10;
```
An `int` can store both positive and negative whole numbers.

C++ also provides other integer types with different ranges and storage requirements, including:
```cpp
short
int
long
long long
```
C++ also provides unsigned versions:
```cpp
unsigned int count = 100;
```
An unsigned integer cannot represent negative values, but it can represent a larger range of non-negative values using the same number of bits.
#### Floating-Point Types
Floating-point types are used to represent numbers that can contain a fractional part.

The two commonly used types are:
```cpp
float
double
```
For example:
```cpp
float temperature = 36.5f;
double price = 19.99;
```
`double` generally provides more precision than `float`, so it is commonly preferred when greater precision is needed.

C++ also provides `long double` for implementations that offer additional precision.
```cpp
long double value = 3.141592653589793238L;
```
The exact size and precision of these types can depend on the C++ implementation and platform.
#### Character Types
The `char` type is used to store a **single character**.
```cpp
char grade = 'A';
char symbol = '#';
char digit = '7';
```
Character literals are written using **single quotes**:
```cpp
'A'
'B'
'7'
```
A `char` represents a character using an underlying integer value according to the character encoding used by the implementation.

C++ also provides character types designed for wider or Unicode-related character representations, including:
```cpp
wchar_t
char8_t
char16_t
char32_t
```
These types become more relevant when working with different character encodings and Unicode text.
#### Boolean Type
The `bool` type represents a logical value. It can have one of two values:
```cpp
true
false
```
For example:
```cpp
bool isLoggedIn = true;
bool hasPermission = false;
```
Boolean values are commonly used with conditions and decision-making:
```cpp
if (isLoggedIn){
    cout << "Welcome!";
}
```
#### Void
The `void` type represents the **absence of a value**. It is commonly used with functions that do not return a value:
```cpp
void sayHello()
{
    cout << "Hello!";
}
```
Here, `void` tells C++ that `sayHello()` does not return a value.
#### Strings
A **string** is a sequence of characters used to represent text, such as a word, a sentence, or a name. For example, `"Hello"` is a string containing five characters.    
C++ does not have a built-in fundamental `string` data type in the same way that it has `int`, `double`, or `bool`. Instead, the standard library provides `std::string` through the `<string>` header.

A `std::string` represents a sequence of characters:
```cpp
#include <string>

std::string name = "Alice";
```
If we use:
```cpp
using namespace std;
```
we can write:
```cpp
string name = "Alice";
```
Strings are extremely common because programs frequently need to work with names, sentences, commands, and other text.
### Type Conversion and Type Casting
We have seen that variables have different data types. But sometimes, we need to convert a value from one data type to another. For example, we may need to convert an `int` into a `double`, or a `double` into an `int`.

C++ provides several ways to perform these conversions.

There are two important concepts to understand:
- **Type conversion** a value is converted from one type to another, sometimes automatically by C++.
- **Type casting** the programmer explicitly tells C++ to convert a value to a specific type.

#### Implicit Type Conversion
An **implicit conversion** happens automatically when C++ converts a value from one type to another without us explicitly requesting it.
```cpp
int age = 25;

double value = age;
```
Here, `age` is an `int`, but `value` is a `double`. C++ automatically converts `25` from an integer to a floating-point value.

This type of conversion is generally safe when converting from a type that can represent fewer values or less precision to a type that can represent them more broadly.

#### Explicit Type Conversion
Sometimes we want to explicitly convert a value to another type. This is called explicit type conversion or type casting.

One simple form is:
```cpp
double price = 19.99;

int value = (int)price;
```
The `double` value is converted to an `int`, resulting in:
```
19
```
The fractional part is discarded; it is **not rounded**.

C++ also provides a more modern and safer syntax for explicit conversions called `static_cast`:
```cpp
double price = 19.99;

int value = static_cast<int>(price);
```
`static_cast<int>` explicitly tells C++ to convert `price` to an `int`. For modern C++ code, `static_cast` is generally preferred over the older C-style syntax `(int)` because the conversion is more explicit and easier to identify when reading the code.
#### Narrowing Conversions
Some conversions can result in a loss of information. These are often called narrowing conversions.

For example:
```cpp
double value = 10.75;

int number = static_cast<int>(value); // The result is 10
```
The fractional part `.75` is lost.

Similarly, converting a larger integer type to a smaller type can potentially lose information if the value cannot be represented by the destination type.
#### Converting Between `char` and Numbers
Because `char` is an integral type, it can also participate in numeric conversions.
```cpp
char letter = 'A';

int value = letter;
```
The character is converted to its underlying integer value according to the character encoding.

We can also convert an integer to a `char`:
```cpp
int value = 65;

char letter = static_cast<char>(value);
```
#### String and Number Conversion
Sometimes we need to convert between a `std::string` and a numeric type. For example, input from a user is often stored as a string, but we may need to convert it into an `int` or `double` so that we can perform calculations.
#### String to Number
C++ provides functions such as `std::stoi`, `std::stol`, `std::stoll`, `std::stof`, `std::stod`, and `std::stold` for converting strings to numbers.
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string text = "42";

    int number = std::stoi(text);

    std::cout << number + 8 << '\n';

    return 0;
}
```
Here, `std::stoi()` converts the string `"42"` into the integer `42`.

Common functions include:

| Function       | Resulting type |
| -------------- | -------------- |
| `std::stoi()`  | `int`          |
| `std::stol()`  | `long`         |
| `std::stoll()` | `long long`    |
| `std::stof()`  | `float`        |
| `std::stod()`  | `double`       |
| `std::stold()` | `long double`  |


The conversion functions can throw exceptions if the string does not contain a valid number or if the resulting value is outside the range of the target type.
```cpp
std::string text = "hello";

int number = std::stoi(text); // throws an exception
```
#### Number to String
To convert a number into a `std::string`, C++ provides `std::to_string()`.
```cpp
#include <iostream>
#include <string>

int main()
{
    int age = 25;

    std::string text = std::to_string(age);

    std::cout << "Age: " << text << '\n';

    return 0;
}
```
`std::to_string()` supports several numeric types:

```cpp
int a = 42;
double b = 3.14;
float c = 2.5f;

std::string x = std::to_string(a);
std::string y = std::to_string(b);
std::string z = std::to_string(c);
```

### Working with Numbers
Programs frequently need to perform calculations, whether we are calculating a total price, converting units, keeping track of scores, or processing measurements.

C++ provides several arithmetic operators that allow us to perform mathematical operations on numeric values.
#### Arithmetic Operators
The basic arithmetic operators are:

| Operator | Name           | Description                               | Example |
| -------- | -------------- | ----------------------------------------- | ------- |
| `+`      | Addition       | Adds two values                           | `a + b` |
| `-`      | Subtraction    | Subtracts the second value from the first | `a - b` |
| `*`      | Multiplication | Multiplies two values                     | `a * b` |
| `/`      | Division       | Divides the first value by the second     | `a / b` |
| `%`      | Modulo         | Returns the remainder of integer division | `a % b` |
| `++`     | Increment      | Increases a value by `1`                  | `a++`   |
| `--`     | Decrement      | Decreases a value by `1`                  | `a--`   |

#### Addition
The `+` operator adds two values:
```cpp
int a = 4;
int b = 5;

int result = a + b; // result is 9
```
The `+` operator can also be used with other types. For example, when used with `char`, the characters participate in **integral promotion**, so their underlying integer values are used in the calculation.
```cpp
char a = 'A';
char b = 'B';

int result = a + b;
```
The result is an `int`, not a `char`.
### Subtraction
The `-` operator subtracts the right-hand operand from the left-hand operand:
```cpp
int a = 10;
int b = 4;

int result = a - b; // result is 6
```
### Multiplication
The `*` operator multiplies two values:
```cpp
int a = 4;
int b = 5;

int result = a * b; // result is 20
```
Like the other arithmetic operators, `*` can also operate on character values after the appropriate integral promotions.
#### Division
The `/` operator divides one value by another. The result depends on the types of the operands.

When both operands are integers, C++ performs integer division:
```cpp
int a = 7;
int b = 2;

int result = a / b; // result is 3
```
The fractional part is discarded. The result is not rounded.

If at least one operand is a floating-point type, the division produces a floating-point result:
```cpp
double a = 7.0;
double b = 2.0;

double result = a / b; // result is 3.5
```
#### Modulo
The `%` operator calculates the **remainder** of integer division.
```cpp
int a = 7;
int b = 2;

int result = a % b; // result 1
```
because `7 / 2` gives an integer quotient of `3` with a remainder of `1`.

The modulo operator is commonly used when checking whether a number is divisible by another number:
```cpp
if (number % 2 == 0)
{
    // number is even
}
```
The `%` operator requires integral operands; it is not used for ordinary floating-point values such as `float` or `double`.
#### Increment and Decrement
The increment operator `++` increases a variable by `1`:
```cpp
int count = 5;

count++;
```
`count` is now `6`.

The decrement operator `--` decreases a variable by `1`:
```cpp
int count = 5;

count--;
```
`count` is now `4`.

Both operators have **prefix** and postfix forms:
```cpp
++count; // prefix
count++; // postfix
```
When the operator is used by itself as a statement, both forms increase the value by `1`. The difference becomes important when the expression itself is used as part of a larger expression.
#### Compound Assignment Operators
C++ also provides compound assignment operators, which combine an arithmetic operation with assignment.

For example:
```cpp
a += 4;
```
is equivalent to:
```cpp
a = a + 4;
```
Compound assignment operators provide a shorter way to modify an existing variable. The main arithmetic compound assignment operators are:

| Operator | Equivalent to | Meaning             |
| -------- | ------------- | ------------------- |
| `+=`     | `a = a + b`   | Add and assign      |
| `-=`     | `a = a - b`   | Subtract and assign |
| `*=`     | `a = a * b`   | Multiply and assign |
| `/=`     | `a = a / b`   | Divide and assign   |
| `%=`     | `a = a % b`   | Modulo and assign   |

Each operation takes the current value of the variable, performs the specified arithmetic operation, and stores the result back in that same variable.

### Constants
Constant represent value that must not change after it has been initialized.

A value that is not allowed to change is called a **constant**.
#### The `const` Keyword
The `const` keyword is used to declare a variable whose value cannot be changed after it has been initialized.
```cpp
const double pi = 3.141592653589793;
```
Here, `pi` is a constant. Once it has been initialized, we cannot assign another value to it:
```cpp
const double pi = 3.141592653589793;

pi = 3.14; // Error
```
The compiler will reject this because `pi` is `const`.
#### The `constexpr` Keyword
C++ also provides `constexpr`, which stands for **constant expression**. Like `const`, a `constexpr` variable cannot be modified after initialization:
```cpp
constexpr double pi = 3.141592653589793;
```
However, `constexpr` adds another requirement: the value must be something that can be evaluated at compile time.
```cpp
constexpr int secondsPerMinute = 60;
constexpr int minutesPerHour = 60;
constexpr int secondsPerHour = secondsPerMinute * minutesPerHour;
```
The compiler can determine the value of `secondsPerHour` during compilation. This makes `constexpr` useful when a value is known at compile time and needs to be usable in contexts that require a compile-time constant.

The main difference between `const` and `constexpr` is when their values are required to be known.

A `const` variable can be initialized at **runtime**, which means its value can come from a runtime calculation. On the other hand, a `constexpr` variable must be initialized with a value that can be evaluated at compile time, before the program runs.
#### Using `#define`
Finally we can use `#define` to create a preprocessor macro. Before the actual compilation takes place, the preprocessor replaces occurrences of `PI` with `3.141592653589793`.

For example:
```cpp
#define PI 3.14159

double circumference = 2 * PI * radius;
```
The preprocessor effectively replaces `PI` with its value before the compiler processes the resulting code.

Although `#define` is still supported and can be useful for certain preprocessor tasks, it is generally not the preferred way to define typed constants in modern C++.
### Comments
Comments are notes written in source code that are ignored by the compiler. They do not affect how the program runs and are mainly used to explain code, provide additional information, or make the source code easier to understand.

C++ provides two types of comments.
#### Single-Line Comments
A single-line comment begins with `//`. Everything after `//` on that line is treated as a comment.
```cpp
// This is a comment
int age = 25; // This is also a comment
```
The compiler ignores the comment and only processes the actual C++ code.
#### Multi-Line Comments
A multi-line comment begins with `/*` and ends with `*/`. Everything between these two markers is treated as a comment, even if it spans multiple lines.
```cpp
/*
   This is a multi-line comment.
   It can span several lines.
*/
int age = 25;
```
## Working with Input and Output
So far, our programs have used values that were written directly into the source code. For example:
```cpp
int age = 30;
```
This works, but it makes the program less flexible. A useful program should be able to display information to the user and receive information from the user.

C++ provides two standard stream objects for basic console interaction:
- `cout` used to send output to the console.
- `cin` used to receive input from the user.

Both are provided by the `<iostream>` header.
### Output and Printing in C++
We use `cout` to send information to the standard output, which is normally the terminal or console.

The `<<` operator, called the stream insertion operator, is used to send values into `cout`.

For example:
```cpp
cout << "Hello, Reader";
```
We can also print the value of a variable:
```cpp
int age = 30;

cout << age;
```
Multiple values can be sent to `cout` by chaining several `<<` operators:
```cpp
int age = 30;
string name = "Alice";

cout << "My name is " << name << " and I am " << age << " years old.";
```
The output is:
```text
My name is Alice and I am 30 years old.
```
Each `<<` takes the value on its right and inserts it into the output stream.

#### Creating New Lines
We can move to the next line using the newline escape sequence `\n`:
```cpp
cout << "Hello\n";
cout << "World\n";
```
Output:
```text
Hello
World
```
We can also use `endl`:
```cpp
cout << "Hello" << endl;
cout << "World" << endl;
```
Both `\n` and `endl` create a new line, but they are not exactly the same. `endl` also flushes the output stream, while `\n` simply inserts a newline character.
#### Escape Sequences
An **escape sequence** is a special character combination used inside a character or string literal to represent a character that may be difficult or impossible to write directly.

Escape sequences begin with a **backslash (`\`)**.
```cpp
cout << "Hello\nWorld";
```
Here, `\n` represents a newline.

Some commonly used escape sequences are:

|Escape sequence|Meaning|
|---|---|
|`\n`|Newline|
|`\t`|Horizontal tab|
|`\\`|Backslash|
|`\"`|Double quote|
|`\'`|Single quote|
|`\r`|Carriage return|
|`\b`|Backspace|
|`\a`|Alert / bell|

### Getting User Input
Output allows a program to communicate information to the user, but many programs also need to receive information from the user.

For example, instead of hardcoding:
```cpp
int age = 30;
```
we can ask the user to enter their age while the program is running. C++ provides `cin` for reading input from the standard input, which is normally the keyboard.

The basic syntax is:
```cpp
cin >> variable;
```
The `>>` operator, called the stream extraction operator, extracts data from the input stream and stores it in the specified variable.
```cpp
int age;

cin >> age;
```
When the program reaches `cin >> age`, it waits for the user to enter a value. If the user enters:
```text
25
```
the value `25` is stored in the variable `age`.

#### Reading Multiple Values
We can also read multiple values using several `>>` operators:
```cpp
int age;
double height;

cin >> age >> height;
```
For example, the user could enter:
```text
25 1.75
```
and the values will be stored in their corresponding variables.

#### Input and text note: 
`std::cin >> value` reads one token and stops at whitespace. Use `std::getline(std::cin, text)` for a full line. If formatted input fails, check the stream before using the destination variable.

## Tasks
### Task 1 :
Write a program that reads the radius of a circle from the user and then displays its surface area.
### Task 2 :
Write a C++ program that reads the name of a student, then reads three grades (as floating-point numbers) for the student, stores them in an array, and finally displays the student's name, their individual grades, and the average of their grades.
