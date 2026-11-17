# C++ Programming Course

A twelve-lecture course that starts with basic C++ syntax and gradually introduces memory, functions, object-oriented design, the standard library, generic programming, resource management, file handling, and concurrency.

The notes are intended for guided learning and hands-on practice. Each lecture contains explanations and examples; most lectures also include practice tasks and separate solution files.

## Course map

| Lecture                      | Topic                       | Main ideas                                                                                          |
| ---------------------------- | --------------------------- | --------------------------------------------------------------------------------------------------- |
| [01](Lecture1/Lecture1.md)   | C++ foundations             | Program structure, compilation, variables, types, conversions, arithmetic, input, and output        |
| [02](Lecture2/Lecture2.md)   | Operators and control flow  | Comparisons, logical and bitwise operators, decisions, and loops                                    |
| [03](Lecture3/Lecture3.md)   | Pointers and data           | Pointers, references, arrays, dynamic storage, C++ strings, and vectors                             |
| [04](Lecture4/Lecture4.md)   | Functions                   | Parameters, return values, scope, overloads, recursion, lambdas, headers, and multiple source files |
| [05](Lecture5/Lecture5.md)   | Object-oriented programming | Classes, encapsulation, constructors, operator overloading, inheritance, and polymorphism           |
| [06](Lecture6/Lecture6.md)   | Data modelling and errors   | Enumerations, structures, aliases, exceptions, assertions, `optional`, and `expected`               |
| [07](Lecture8/Lecture7.md)            | Containers and iterators    | Sequence, associative, and unordered containers; adaptors; iterator safety                          |
| [08](Lecture7/Lecture8.md)            | Algorithms and callables    | Standard algorithms, lambdas, captures, function objects, and `std::function`                       |
| [09](Lecture9/Lecture9.md)   | Templates                   | Function and class templates, type traits, concepts, and compile-time programming                   |
| [10](Lecture10/Lecture10.md) | Resource management         | RAII, smart pointers, value categories, move semantics, and type-safe alternatives                  |
| [11](Lecture11/Lecture11.md) | File I/O                    | File streams, string streams, binary data, and output formatting                                    |
| [12](Lecture12/Lecture12.md) | Concurrency                 | Threads, mutexes, condition variables, asynchronous tasks, futures, and promises                    |

## Prerequisites

No previous programming experience is required. You should be comfortable using a computer, editing text files, and working with folders and a terminal. A basic understanding of algebra is helpful for some exercises.

## Compiler and C++ standard

Use a recent C++ compiler:

- **Windows:** Visual Studio 2022 or a recent MinGW-w64/GCC installation.
- **Linux:** GCC or Clang installed through your distribution's package manager.
- **macOS:** Apple Clang or an up-to-date LLVM Clang toolchain.

The course uses **C++20 as its main language baseline**. A few examples discuss older or newer features explicitly. In particular, `std::expected` is a **C++23** library feature and requires a standard library that implements it. If your compiler does not support that section yet, continue with the `std::optional` and exception-handling material.

Check your compiler version:

```sh
g++ --version
clang++ --version
```

Compile a single-file example with GCC:

```sh
g++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

Or with Clang:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o app
./app
```

On Windows, run the generated executable as `app.exe` from the appropriate terminal. IDEs can perform the same build and run steps through their project settings.

### Compiling a multi-file example

When a lecture demonstrates a header and multiple source files, compile all required `.cpp` files together. For example:

```sh
g++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp math_utils.cpp -o app
```

Do not compile every `.cpp` file in the course into one executable. Most examples and solutions contain their own `main()` function and are intended to be built separately.

## Repository layout

```text
Cpp_programming/
├── README.md
├── Lecture1/
│   ├── Lecture1.md
│   ├── Examples/
│   └── Solutions/
├── Lecture2/
│   ├── Lecture2.md
│   ├── Examples/
│   └── Solutions/
└── ...
```

Each lecture folder contains:

- `LectureN.md` — the lesson notes.
- `Examples/` — small programs that demonstrate the concepts.
- `Solutions/` — worked solutions to the practice tasks, where provided.
- `attachments/` — diagrams or images used by the notes, where required.

## Recommended study method
1. Read one section at a time and type the examples yourself rather than only copying them.
2. Compile each example independently with warnings enabled.
3. Change values and inputs to see how the program behaves, including invalid inputs and boundary cases.
4. Attempt the practice tasks before opening the solution files.
5. Explain the result in your own words. If you cannot explain why the code works, revisit the relevant section.
6. Keep a small project that uses ideas from earlier lectures as you progress.

A reasonable pace is one or two lectures per week, with additional time for coding and review. The advanced lectures may need more time than the introductory ones.
## Important learning notes
- Prefer `std::string`, `std::vector`, and smart pointers for ordinary application code. Raw pointers and `new`/`delete` are introduced to explain memory and ownership, not as the default way to manage data.
- Use `const` to communicate which values should not be modified, and validate input before using it.
- Do not assume that a program which compiles is necessarily correct. Check edge cases, object lifetimes, iterator invalidation, file errors, and thread synchronization.
- Raw binary writes of C++ structures are generally not portable between different compilers, platforms, or program versions. The Lecture 11 notes explain the limitations.

## Contributing and reuse
Corrections, clearer explanations, and additional tests are welcome. Please preserve the lesson sequence and make sure new examples compile with the stated language standard.

## Contact
Questions? Open an issue or reach out via:

- GitHub: [@Bayt-al-Hikmah](https://github.com/Bayt-al-Hikmah)
- Email: [alitigui](mailto:alitighiouart2001@gmail.com) 

