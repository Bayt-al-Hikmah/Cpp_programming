# Resource Management, Ownership, and Move Semantics
## Learning Objectives
- Understand RAII and why resource ownership should be explicit.
- Choose between `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.
- Distinguish lvalues, xvalues, and prvalues at a practical level.
- Understand move construction, move assignment, and moved-from objects.
- Represent optional and alternative values with `std::optional`, `std::variant`, and `std::any`.
## Modern C++ Resource Management

### Introduction

A C++ program may use different resources, such as dynamically allocated memory, files, network connections, mutex locks, or hardware handles. These resources must be released when they are no longer needed. Forgetting to release a resource can cause a resource leak. Releasing the same resource more than once, or trying to use it after it has been released, can also lead to errors or undefined behavior.

In older C++ code, resources were often managed manually using `new` and `delete`, or `new[]` and `delete[]`. Although this approach works, the programmer must make sure that every resource is released correctly, even when a function exits early or an exception occurs. Modern C++ provides safer ways to manage resources by assigning their ownership to objects that handle their lifetime automatically.

To understand modern resource management, we need to consider a few important ideas. 
- **Ownership** determines which object is responsible for managing a resource. 
- **Lifetime** describes when a resource becomes available and when it is released. 
- **Observation** allows code to access a resource without taking ownership of it. 
- **Transfer** allows ownership to move from one object to another without copying the resource. 
- Finally, **representation** refers to using types that clearly express the possible states and valid operations of a value.
### RAII: Resource Acquisition Is Initialization
**RAII** is a C++ technique that connects a resource's lifetime to the lifetime of an object. The object acquires the resource, or takes responsibility for it, when it is constructed. When the object is destroyed, its destructor automatically releases the resource. This also works when an exception occurs, because local objects are destroyed automatically during stack unwinding.

The C++ standard library uses RAII in many of its types. For example, `std::vector` manages a dynamically allocated array. It automatically allocates memory when needed and releases it when the vector is destroyed:
```cpp
#include <iostream>
#include <vector>

void processData() {
    std::vector<int> numbers(1000, 42);

    std::cout << "First element: " << numbers[0] << '\n';

    // Memory is released automatically when numbers leaves scope.
}

int main() {
    processData();
}
```
In this example, `numbers` allocates memory to store 1000 integers. When `processData()` finishes, `numbers` goes out of scope, and its destructor automatically releases the allocated memory. The programmer does not need to use `delete` manually.

Smart pointers follow the same principle. They are objects that manage dynamically allocated memory and automatically release it when their ownership ends.
### Smart Pointers and Ownership
Smart pointers are objects that manage the ownership and lifetime of dynamically allocated memory. They follow the RAII principle: when a smart pointer is destroyed, it automatically releases the resource it owns. This makes memory management safer and reduces the need to use `new` and `delete` manually.

Smart pointers are defined in the `<memory>` header. C++ provides three main types, each with a different ownership model. 
- `std::unique_ptr<T>` provides exclusive ownership, meaning only one smart pointer can own an object at a time. 
- `std::shared_ptr<T>` allows multiple smart pointers to share ownership of the same object. 
- `std::weak_ptr<T>` provides a non-owning reference to an object managed by a `shared_ptr`.

These types serve different purposes, so you should choose the one that best describes how an object is owned and used.
#### `std::unique_ptr`: Exclusive Ownership
A `std::unique_ptr<T>` owns an object exclusively. This means that only one `unique_ptr` can own that object at a time. It cannot be copied, because copying would create multiple owners. However, it can be moved, which transfers ownership from one `unique_ptr` to another.

The recommended way to create a `unique_ptr` is to use `std::make_unique<T>(...)`:
```cpp
#include <iostream>
#include <memory>
#include <string>

int main() {
    auto sensorName = std::make_unique<std::string>("Pressure sensor");

    std::cout << *sensorName << '\n';
    std::cout << "Characters: " << sensorName->size() << '\n';

    return 0;
}
```
In this example, `std::make_unique<std::string>(...)` creates a string and returns a `unique_ptr` that owns it. We can use `*sensorName` to access the string or `sensorName->size()` to call one of its member functions.

When `sensorName` goes out of scope, its destructor automatically destroys the string and releases the allocated memory. No manual call to `delete` is needed.

Since a `unique_ptr` cannot be copied, ownership must be transferred using `std::move`:
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <utility>

int main() {
    auto source = std::make_unique<std::string>("Pump A");
    auto destination = std::move(source);

    if (!source) {
        std::cout << "source owns nothing now\n";
    }

    std::cout << "destination owns: " << *destination << '\n';
    return 0;
}
```
After the move, `destination` owns the string, while `source` becomes empty. The string itself is not copied. Instead, ownership of the allocated memory is transferred to `destination`.

Trying to copy a `unique_ptr` will result in a compilation error:
```cpp
// auto secondOwner = source; // Error: unique_ptr cannot be copied.
```
This exclusive ownership model is also important when passing smart pointers to functions. When a function only needs to access an object without taking ownership, you can pass a reference or a raw pointer. When the function needs to take ownership, pass a `unique_ptr` by value.

For example:
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <utility>

void inspect(const std::string& name) {
    std::cout << "Inspecting " << name << '\n';
}

void takeOwnership(std::unique_ptr<std::string> name) {
    std::cout << "Now owned here: " << *name << '\n';
}

int main() {
    auto name = std::make_unique<std::string>("Flow sensor");

    inspect(*name);                  // Access without transferring ownership.
    takeOwnership(std::move(name));  // Transfer ownership to the function.
}
```
Here, `inspect()` receives a reference to the string, so `name` keeps owning it. However, `takeOwnership()` receives a `unique_ptr` by value. Using `std::move` transfers ownership to that function.

A `unique_ptr` also provides several useful operations. You can use `if (ptr)` or `ptr != nullptr` to check whether it owns an object. The `get()` function returns a raw pointer to the managed object without transferring ownership. The `reset()` function destroys the currently owned object and can optionally take ownership of another one.

Another operation is `release()`, which gives up ownership and returns the raw pointer without deleting the object. This means the programmer becomes responsible for releasing it. Use this operation only when another owner will take responsibility; otherwise, it can cause a memory leak.
#### `std::shared_ptr`: Shared Ownership
Unlike `std::unique_ptr`, which allows only one owner, `std::shared_ptr<T>` allows multiple pointers to own the same object. It uses a shared control block to keep track of how many owners exist. Each time a `shared_ptr` is copied, the ownership count increases. When an owner is destroyed or reset, the count decreases. The managed object is automatically destroyed when the last owner releases it.

Use `std::make_shared<T>(...)` to create a shared object:
```cpp
#include <iostream>
#include <memory>

int main() {
    auto firstOwner = std::make_shared<int>(100);
    std::cout << "Owners: " << firstOwner.use_count() << '\n';

    {
        auto secondOwner = firstOwner;

        *secondOwner = 125;

        std::cout << "Owners in scope: "
                  << firstOwner.use_count() << '\n';

        std::cout << "Value through first owner: "
                  << *firstOwner << '\n';
    }

    std::cout << "Owners after scope: "
              << firstOwner.use_count() << '\n';
}
```
Here, both pointers share ownership of the same integer. Copying `firstOwner` into `secondOwner` creates another owner, not another integer. Therefore, changing the value through `secondOwner` also changes the value seen through `firstOwner`.

When `secondOwner` leaves its scope, it is destroyed and the ownership count decreases. The integer remains alive because `firstOwner` still owns it.

The `use_count()` function returns the current number of shared owners. It is useful for understanding shared ownership and occasional diagnostics, but program logic should not depend on a specific count because ownership can change as the program runs.
#### `std::weak_ptr`: Non-owning Observation
A `std::weak_ptr<T>` provides a way to observe an object managed by `std::shared_ptr<T>` without sharing its ownership. It does not increase the ownership count or extend the object's lifetime.

To access the object, use the `.lock()` function. It returns a `shared_ptr` if the object is still alive, or an empty `shared_ptr` if it has already been destroyed. This allows you to check whether the object still exists before using it.
```cpp
#include <iostream>
#include <memory>
#include <string>

int main() {
    std::weak_ptr<std::string> observer;

    {
        auto owner = std::make_shared<std::string>("Temperature sensor");
        observer = owner;

        if (auto temporaryOwner = observer.lock()) {
            std::cout << "Object is alive: " << *temporaryOwner << '\n';
        }
    } // The last shared owner is destroyed here.

    if (auto temporaryOwner = observer.lock()) {
        std::cout << *temporaryOwner << '\n';
    } else {
        std::cout << "Object has expired\n";
    }
}
```
In this example, `observer` is a `weak_ptr` that references the string without owning it or extending its lifetime. While `owner` keeps the string alive, calling `observer.lock()` successfully returns a `shared_ptr`, stored in `temporaryOwner`. This temporarily adds another owner, ensuring the object remains alive while it is being accessed.

When `owner` goes out of scope, the last shared owner is destroyed, and the string is automatically released. The `weak_ptr` remains, but its reference has expired. Therefore, the second call to `observer.lock()` returns an empty `shared_ptr`, causing the condition to evaluate to `false` and the `else` block to execute.

This is the main purpose of `weak_ptr`: it allows you to observe an object managed by `shared_ptr` without affecting its lifetime, while `.lock()` provides a safe way to access it when it still exists.
#### Reference Counting and Ownership Cycles
Shared ownership has an important limitation: two or more objects can accidentally keep each other alive through a cycle of `shared_ptr` references. For example, if object A owns object B through a `shared_ptr`, and B also owns A through another `shared_ptr`, neither object's ownership count can reach zero. Even after the rest of the program releases its references, both objects remain allocated, causing a memory leak.

A common solution is to use `shared_ptr` for the main ownership relationship and `weak_ptr` for references that should not own the object. Consider a parent-child relationship where the parent owns its child, while the child only needs to observe its parent:
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Node {
    std::string name;
    std::shared_ptr<Node> child; // Owning relationship.
    std::weak_ptr<Node> parent;  // Non-owning reference.

    explicit Node(std::string nodeName) : name(std::move(nodeName)) {}
};

int main() {
    auto root = std::make_shared<Node>("root");
    auto leaf = std::make_shared<Node>("leaf");

    root->child = leaf;
    leaf->parent = root;

    if (auto parent = leaf->parent.lock()) {
        std::cout << leaf->name << " belongs to " << parent->name << '\n';
    }
}
```
In this example, `root` owns `leaf` through its `shared_ptr` child. The `leaf` node references its parent through a `weak_ptr`, allowing it to access the parent without extending its lifetime. This creates a clear ownership direction and prevents a reference cycle.

#### Custom Deleters and Resource Cleanup
Smart pointers normally use `delete` to destroy the objects they manage. However, some resources require a different cleanup operation. For example, a file opened using the C function `std::fopen()` must be closed using `std::fclose()`, not `delete`.

C++ allows us to provide a **custom deleter** that tells a smart pointer how to release its resource:
```cpp
#include <cstdio>
#include <iostream>
#include <memory>

struct FileCloser {
    void operator()(std::FILE* file) const noexcept {
        if (file != nullptr) {
            std::fclose(file);
        }
    }
};

int main() {
    using FilePtr = std::unique_ptr<std::FILE, FileCloser>;

    FilePtr file(std::fopen("measurements.txt", "r"));

    if (!file) {
        std::cerr << "Could not open measurements.txt\n";
        return 1;
    }

    std::cout << "File opened successfully\n";

    // FileCloser calls std::fclose when file is destroyed.
}
```
Here, `FileCloser` is a function object that defines how the file should be closed. It is provided as the second template argument of `std::unique_ptr`, making it the smart pointer's custom deleter.

The `unique_ptr` takes ownership of the file handle returned by `std::fopen()`. When `file` goes out of scope, it automatically calls `FileCloser`, which uses `std::fclose()` to release the resource.
### Value Categories and References
In C++, expressions are classified according to their **value categories**. These categories describe how an expression relates to an object, particularly whether it identifies an existing object or produces a value.
#### Lvalues and Rvalues
The two main categories to understand initially are **lvalues** and **rvalues**.

An **lvalue** is an expression that identifies an existing object. For example, the name of a variable is an lvalue because it refers to a specific object in memory.
```cpp
int count = 10;

count = 20; // count is an lvalue.
```
An **rvalue** represents a value that can be used to initialize another object or an object whose resources may be reused. Literals such as `42`, arithmetic expressions such as `a + b`, and temporary objects such as `std::string("ready")` are common examples.

Common examples include literals, arithmetic expressions, and temporary objects:
```cpp
int x = 42;                          // 42 is an rvalue.
int result = 10 + 20;                // 10 + 20 is an rvalue.

std::string text = std::string("ready"); // Temporary object.
```
This distinction is important because C++ treats lvalues and rvalues differently, particularly when binding references and selecting between copy and move operations.
#### Understanding the Value Categories
The distinction between lvalues and rvalues is useful, but C++ defines a more precise classification by dividing expressions into three categories:
- **lvalue (left value):** Identifies an existing object. For example, `count` is an lvalue because it refers to a specific variable.
- **prvalue (pure rvalue):** Produces a value rather than identifying an existing object. Examples include `42`, `10 + 20`, and `std::string("ready")`.
- **xvalue (expiring value):** Identifies an existing object but treats it as an expiring value, allowing its resources to be reused. A common example is `std::move(object)`.

Consider the following example:
```cpp
std::string text = "Hello";

text;             // lvalue
std::string("Hi"); // prvalue
std::move(text);  // xvalue
```
Notice that `text` and `std::move(text)` refer to the same object, but their expressions have different value categories. The first is an lvalue, while the second is an xvalue.

This is the key distinction between prvalues and xvalues: a **prvalue produces a value**, whereas an **xvalue identifies an existing object that can potentially be moved from**.

#### Lvalue References and Rvalue References
C++ provides two main reference types, written as `T&` and `T&&`. An **lvalue reference** (`T&`) normally binds to a compatible lvalue, while an **rvalue reference** (`T&&`) binds to a compatible rvalue. A `const T&` is more flexible because it can bind to both.

This distinction allows functions to behave differently depending on the value category of their arguments:
```cpp
#include <iostream>
#include <string>
#include <utility>

void describe(const std::string& text) {
    std::cout << "Read-only reference: " << text << '\n';
}

void describe(std::string&& text) {
    std::cout << "Rvalue-reference overload: " << text << '\n';
}

int main() {
    std::string name = "Pump";

    describe(name);                 // Selects const std::string&.
    describe(std::string("Fan"));   // Selects std::string&&.
    describe(std::move(name));      // Also selects std::string&&.
}
```
The first call passes a named variable, so the `const std::string&` overload is selected. The second passes a temporary string, so the rvalue-reference overload is selected. The third uses `std::move()` to make the expression an xvalue, allowing it to bind to the rvalue reference.


#### Named Variables and Value Categories
An important rule is that **a named variable is always an lvalue expression, even when its declared type is an rvalue reference**.
```cpp
#include <iostream>
#include <string>
#include <utility>

void accept(std::string&& text) {
    std::cout << text << '\n';
}

int main() {
    std::string original = "Compressor";
    std::string&& reference = std::move(original);

    // accept(reference); // Error: reference is an lvalue expression.

    accept(std::move(reference)); // Valid: casts it to an xvalue.
}
```
Although `reference` is declared as `std::string&&`, using its name produces an lvalue expression. Therefore, it cannot bind directly to another rvalue reference. Applying `std::move()` casts the expression to an xvalue, allowing it to bind.

This rule is particularly important when implementing move constructors and move assignment operators, where named objects often need to be explicitly cast to allow their resources to be moved.

#### How Value Categories Affect Copying and Moving
Value categories also influence how objects are initialized. When an object is initialized from an lvalue, a copy constructor is generally selected. When initialized from an xvalue, a move constructor can be selected if the type provides one.

Consider this example:
```cpp
#include <iostream>
#include <string>
#include <utility>

int main() {
    std::string original = "A long string that may allocate memory";

    std::string copy = original;             // Copy construction.
    std::string moved = std::move(original); // Move construction.

    std::cout << "Copy: " << copy << '\n';
    std::cout << "Moved: " << moved << '\n';
}
```
In the first initialization, `copy` receives a copy of `original`, so both strings have their own contents. In the second, `std::move()` allows the move constructor to be selected, which can transfer the string's internal resources instead of copying its contents.

After being moved from, `original` remains a valid object, but its value is unspecified. It can still be assigned a new value or destroyed normally.

Moving can be more efficient than copying, especially for objects that manage dynamically allocated resources. However, `std::move()` only enables moving; the actual behavior depends on the constructors and assignment operators provided by the type.
### Move Semantics
As we have seen, an xvalue identifies an existing object that can be treated as expiring. C++ uses this concept to support **move semantics**, which allow resources to be transferred from one object to another instead of copying them.

This is particularly useful for objects that manage dynamically allocated memory, large buffers, or other resources.
#### Why Move Semantics Exist
Consider a `std::vector` containing thousands of elements. Copying it generally requires allocating new memory and copying all its elements. Moving it, however, can transfer ownership of its internal buffer to another vector without copying every element.
```cpp
std::vector<int> source(1000, 42);

std::vector<int> destination = std::move(source);
```
Instead of duplicating the vector's elements, its move constructor can take over the allocated storage. This makes moving significantly more efficient for many resource-owning types.

Move semantics are particularly useful when:
- Transferring ownership of dynamically allocated resources.
- Passing large objects between functions.
- Returning objects from functions when copy elision does not apply.
- Building containers that need to move their elements efficiently.

Although modern compilers eliminate many unnecessary copies through copy elision, move semantics remain important whenever resources need to be transferred between distinct objects.
#### What `std::move` Actually Does
The function `std::move`, declared in `<utility>`, is what allows us to use move semantics with existing objects.

Despite its name, `std::move` **does not move anything by itself**. It casts its argument to an rvalue reference, producing an xvalue when applied to a named object. This allows the compiler to select a move constructor or move-assignment operator when an appropriate one is available.
```cpp
#include <string>
#include <utility>

int main() {
    std::string source = "sensor data";

    std::string destination = std::move(source);
}
```
Here, `std::move(source)` produces an xvalue referring to the existing `source` object. The compiler can therefore select `std::string`'s move constructor to initialize `destination`.

Think of `std::move(x)` as **allowing an operation to treat** `x` **as an expiring object**. The actual move happens in the constructor or assignment operator that receives it.

One important detail: moving from an object does not mean you should continue relying on its original value. Also, applying `std::move` to a `const` object generally does not enable an efficient move because move operations typically require a non-const rvalue reference.
#### Move Constructors
A **move constructor** initializes a new object by transferring resources from an existing object. Its common signature is:
```cpp
TypeName(TypeName&& other);
```
The `&&` indicates an rvalue reference, which allows the constructor to receive an object that can be moved from.

Consider a class that stores a message:
```cpp
#include <string>
#include <utility>

class Message {
private:
    std::string text_;

public:
    Message(std::string text)
        : text_(std::move(text)) {}

    Message(Message&& other) noexcept
        : text_(std::move(other.text_)) {}
};
```
We can use it as follows:
```cpp
Message first("Hello");

Message second(std::move(first));
```
The move constructor transfers the string from `first` to `second` instead of copying it. The original object remains valid, but its string is left in a valid but unspecified state.

The key idea is that **move semantics allow objects to transfer ownership of resources instead of creating copies.**
#### Move-Assignment Operators
While a move constructor initializes a new object, a move-assignment operator transfers resources into an object that already exists.

Its common signature is:
```cpp
TypeName& operator=(TypeName&& other);
```
Consider our `Message` class with a move-assignment operator:
```cpp
#include <string>
#include <utility>

class Message {
private:
    std::string text_;

public:
    Message(std::string text)
        : text_(std::move(text)) {}

    Message(Message&& other) noexcept
        : text_(std::move(other.text_)) {}

    // Move-assignment operator
    Message& operator=(Message&& other) noexcept {
        if (this != &other) {
            text_ = std::move(other.text_);
        }
        return *this;
    }
};
```
We can use it as follows:
```cpp
Message first("Hello");
Message second("Goodbye");

second = std::move(first);
```
Unlike move construction, `second` already exists and contains a string. The move-assignment operator replaces its existing contents by moving the string from `first`.

After the assignment, `second` owns the transferred string, while `first` remains valid but its string is in a valid but unspecified state.

Notice that the self-assignment check (`this != &other`) prevents an object from being moved into itself.
#### Moved-From Objects
After a move operation, the source object still exists, but its original value may no longer be available.

For standard-library types, a moved-from object is generally valid but in an unspecified state, unless the type specifies otherwise.

This means the object can still be safely destroyed or used in operations permitted by its current state, but you should not assume it retains its original value.

For example:
```cpp
std::string source = "sensor data";
std::string destination = std::move(source);
```
After this operation, `destination` contains the transferred value. However, you should not assume that `source` is empty or contains any particular value.

A good practice is to assign a new value to an object before using it again when its previous state is no longer relevant.
#### Rule of Five
Move semantics are closely related to how C++ manages resources and generates special member functions.

The **Rule of Five** states that when a class needs to define custom resource-management behavior, you should consider all five special member functions together:
1. Destructor.
2. Copy constructor.
3. Copy-assignment operator.
4. Move constructor.
5. Move-assignment operator.

Defining one of these functions can affect which others the compiler generates automatically. For example, declaring a move constructor causes the implicitly declared copy operations to be deleted.

However, manually implementing all these operations is often unnecessary.
#### Rule of Zero
The **Rule of Zero** is the preferred approach whenever possible: use existing resource-managing types such as `std::string`, `std::vector`, and `std::unique_ptr` as class members, allowing them to handle copying, moving, and resource management automatically.

Use `= default` when the compiler-generated implementation is appropriate, and `= delete` when an operation must be prohibited.
### Type-Safe Alternatives to Sentinels and Unstructured Values
Sometimes a program needs to represent a value that may be missing, choose between several possible types, or store a value whose type is only known at runtime. C++17 provides three useful types for these situations: `std::optional`, `std::variant`, and `std::any`.
#### `std::optional`: A value that may be absent
`std::optional<T>` represents either a value of type `T` or no value at all. It is declared in `<optional>` and is useful when the absence of a value is a normal result, such as when a sensor reading is unavailable.

Consider a function that reads a temperature:
```cpp
#include <iostream>
#include <optional>

std::optional<double> readTemperature(bool sensorReady) {
    if (!sensorReady) {
        return std::nullopt;
    }

    return 25.5;
}

int main() {
    auto temperature = readTemperature(true);

    if (temperature) {
        std::cout << *temperature << '\n';
    } else {
        std::cout << "No reading available\n";
    }
}
```
When the sensor is unavailable, the function returns `std::nullopt`. Otherwise, it returns the temperature. The caller checks whether a value exists before accessing it.

An optional value can be accessed using `*opt` or `opt.value()`. The difference is that `value()` throws `std::bad_optional_access` when the optional is empty, while `*opt` requires the optional to contain a value. You can also use `opt.value_or(fallback)` to provide a default value, `opt.has_value()` to check its state, and `opt.reset()` to make it empty.

For example:
```cpp
#include <iostream>
#include <optional>

int main() {
    std::optional<int> calibrationOffset;

    std::cout << calibrationOffset.value_or(0) << '\n'; // Uses fallback 0.

    calibrationOffset = 7;
    std::cout << calibrationOffset.value() << '\n';

    calibrationOffset.reset();
}
```
The main advantage of `std::optional` is that it represents the absence of a value directly. Instead of using a special number such as `-1` to indicate a missing reading, the function makes that possibility part of its return type.
#### `std::variant`: One of several known types
`std::variant<Types...>` stores a value of one type from a fixed set of alternatives. It is declared in `<variant>` and is useful when a value can have several known types.

For example, a configuration setting might be an integer, a floating-point number, or a string:
```cpp
#include <iostream>
#include <string>
#include <variant>

int main() {
    using Setting = std::variant<int, double, std::string>;

    Setting value = 42;

    value = 3.14;
    value = std::string("automatic");

    std::cout << std::get<std::string>(value) << '\n';
}
```
A variant holds only one active alternative at a time. `std::get<T>()` retrieves the value when the requested type is active; otherwise, it throws `std::bad_variant_access`.

You can check the active type before accessing it using `std::holds_alternative<T>()`. Another option is `std::get_if<T>()`, which returns a pointer to the value if the type matches, or `nullptr` otherwise.    
For example:
```cpp
#include <iostream>
#include <string>
#include <variant>

int main() {
    using Reading = std::variant<int, double, std::string>;
    Reading reading = 18.75;

    if (std::holds_alternative<double>(reading)) {
        std::cout << "Floating-point reading: " << std::get<double>(reading) << '\n';
    }

    if (const auto* text = std::get_if<std::string>(&reading)) {
        std::cout << "Text reading: " << *text << '\n';
    } else {
        std::cout << "The active alternative is not a string\n";
    }
}
```
#### Processing alternatives with `std::visit`
When different alternatives need to be processed, `std::visit` provides a convenient way to handle the active value without checking its type manually.
```cpp
#include <iostream>
#include <string>
#include <variant>

int main() {
    using Setting = std::variant<int, double, std::string>;

    Setting value = 3.14;

    std::visit([](const auto& item) {
        std::cout << item << '\n';
    }, value);
}
```
`std::visit` calls the given function with the currently stored value. Here, the generic lambda works with all three alternatives because they can all be printed using `std::cout`.

Use `std::variant` when the possible types are known in advance. Its alternatives are explicitly declared, making the types a value can hold clear from its definition.

###  `std::any`: A value of a runtime-selected type
`std::any`, declared in `<any>`, can hold a value of a type selected at runtime, subject to its requirements. It was introduced in C++17. Unlike `variant`, the set of possible contained types is not listed in the `any` type itself.
```cpp
#include <any>
#include <iostream>
#include <string>

int main() {
    std::any metadata = 42;
    std::cout << std::any_cast<int>(metadata) << '\n';

    metadata = std::string("calibration profile A");
    std::cout << std::any_cast<std::string>(metadata) << '\n';
}
```
The stored value must meet `std::any`'s copy-constructibility requirements. It is therefore not a general container for arbitrary move-only types.

#### `std::any`: A value of an unknown type
Unlike `std::variant`, which requires a predefined list of alternatives, `std::any` can store values of different types without declaring those types in advance. It is declared in `<any>` and is useful when the stored type is only determined at runtime.

For example:
```cpp
#include <any>
#include <iostream>
#include <string>

int main() {
    std::any value = 42;

    std::cout << std::any_cast<int>(value) << '\n';

    value = std::string("Hello");

    std::cout << std::any_cast<std::string>(value) << '\n';
}
```
The stored value can be retrieved using `std::any_cast<T>()`. The requested type must match the actual stored type; otherwise, the function throws `std::bad_any_cast`.

To check the type safely without throwing, use the pointer form of `std::any_cast`:
```cpp
if (const auto* text = std::any_cast<std::string>(&value)) {
    std::cout << *text << '\n';
}
```
You can also use `value.has_value()` to check whether a value is stored and `value.reset()` to remove it. The `value.type()` member returns information about the stored type.

Because the possible types are not declared in `std::any`, retrieving a value requires knowing its actual type at runtime. Use it when that flexibility is necessary, but prefer `std::variant` when the possible types are known in advance.
## Tasks
The tasks below are designed to be completed after studying the examples. Use C++20 and compile each program with warnings enabled. The `std::optional`, `std::variant`, and `std::any` examples also work in C++17.
### Task 1:
Write a C++ program that:

1. Defines a `Sensor` class with a name and a current reading.
2. Creates a sensor using `std::make_unique<Sensor>(...)`.
3. Implements an observation function that receives `const Sensor&` and prints the sensor data without taking ownership.
4. Implements a function that receives `std::unique_ptr<Sensor>` by value, demonstrating ownership transfer.
5. Transfers the sensor to that function using `std::move`.
6. Checks whether the original `unique_ptr` is empty after the transfer.
7. Explains why copying the `unique_ptr` is rejected by the compiler.

**Additional challenge:** Store a dynamically sized collection using `std::vector<std::unique_ptr<Sensor>>` and add several sensors to it.

**Hint:** Include `<memory>`, `<string>`, `<vector>`, and `<utility>`. Use `std::make_unique` rather than raw `new`.

### Task 2: 
Write a program for a small parent-child object model.

1. Define a `Node` class with a name, a `std::shared_ptr<Node>` child, and a `std::weak_ptr<Node>` parent.
2. Create a root node and a child node.
3. Make the root own the child and let the child observe the root.
4. Use `parent.lock()` before accessing the parent.
5. Reset the root's strong pointer and examine whether remaining strong owners keep the objects alive.
6. Explain how using a `shared_ptr` for both the child and parent relationships could create an ownership cycle.

**Additional challenge:** Add a function that safely reports whether a weak reference has expired.

**Hint:** Use `<memory>` and `<string>`. Remember that a `weak_ptr` does not keep an object alive.

### Task 3: 

Write a program that:

1. Defines overloaded functions taking `const std::string&` and `std::string&&`.
2. Calls them with a named string, a temporary string, and `std::move(namedString)`.
3. Declares a named `std::string&&` reference and tests which overload a call using its name selects.
4. Uses `std::move` explicitly when an rvalue expression is required.
5. Moves a `std::unique_ptr<int>` into another `unique_ptr` and checks both pointers.
6. Explains why a named rvalue-reference variable is an lvalue expression and why the moved-from string's old value must not be assumed.

**Hint:** Include `<string>`, `<memory>`, `<utility>`, and `<iostream>`.

### Task 4: Implement and examine move operations

Create a `MeasurementBatch` class that contains a `std::vector<double>`.

1. Give it a constructor that accepts a vector and stores its values.
2. Explicitly declare the copy constructor and copy-assignment operator.
3. Implement a move constructor and move-assignment operator using `std::move`.
4. Add a method that reports the number of readings.
5. Move-construct one batch from another, then move-assign into an already-constructed batch.
6. Explain the difference between move construction and move assignment.
7. State which operations could be omitted by following the Rule of Zero.

**Additional challenge:** Declare the move operations `noexcept` only when you can justify that guarantee for all members and relevant allocator behavior.

**Hint:** Include `<utility>` and `<vector>`. Do not add manual dynamic allocation when a vector already manages the storage.

### Task 5: 

Write a function `readTemperature(bool sensorAvailable)` that returns `std::optional<double>`.

1. Return `std::nullopt` when the sensor is unavailable.
2. Return a temperature value when a reading exists.
3. In `main`, check the optional before dereferencing it.
4. Display a fallback value with `value_or` for a separate reporting path.
5. Explain why `std::optional<double>` is clearer than using `-999.0` as a missing-value sentinel.

**Additional challenge:** Modify the design so the function reports both the reading and an error reason, rather than only presence or absence.

**Hint:** Include `<optional>` and `<iostream>`. This feature requires C++17.

### Task 6: 

Write a program where a configuration setting may be an integer, a floating-point number, or a string.

1. Define `using Setting = std::variant<int, double, std::string>`.
2. Store one value of each alternative in turn.
3. Use `std::holds_alternative` or `std::get_if` to check the active type.
4. Use `std::visit` to print the active value.
5. Deliberately request the wrong type with `std::get` in a separate experiment and explain the resulting exception.

**Additional challenge:** Use different behavior for each alternative, such as converting numeric alternatives to engineering units while printing strings unchanged.

**Hint:** Include `<variant>`, `<string>`, and `<iostream>`.

### Task 7: 

Write a program that uses `std::any` to store metadata values of different types.

1. Store an integer identifier.
2. Replace it with a string label.
3. Use the pointer form of `std::any_cast` to test each type safely.
4. Test an incorrect requested type and handle the mismatch without an exception.
5. Check `has_value()` and call `reset()`.
6. Explain when `std::variant` would be a better option than `std::any`.

**Hint:** Include `<any>`, `<string>`, and `<iostream>`. The stored type must satisfy `std::any`'s copy-constructibility requirements.
