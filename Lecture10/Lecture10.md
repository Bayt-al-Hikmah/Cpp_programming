## Objectives
- Understand resource ownership and the RAII principle.
- Work with `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr` based on ownership requirements.
- Understand reference counting, ownership cycles, custom deleters, and lifetime safety.
- Distinguish lvalues, xvalues, and prvalues, and understand the broader categories `glvalue` and `rvalue`.
- Understand move constructors, move assignment, moved-from objects, and the Rule of Five.
- Represent an optional value with `std::optional`, one of several alternative types with `std::variant`, and a value of a type determined at runtime with `std::any`.

## Modern C++ Resource Management
### Introduction
A C++ program may acquire resources such as dynamically allocated memory, files, sockets, mutex locks, or hardware handles. A resource must be released when it is no longer needed. If the release step is forgotten, the program may leak resources. If the same resource is released twice, or is used after release, the program may behave incorrectly or invoke undefined behavior.

Older C++ code often paired `new` with `delete` and `new[]` with `delete[]`. That approach can work, but every control-flow path must release the resource correctly including paths that exit early or throw an exception. Modern C++ normally represents ownership with resource-managing objects instead.

The key ideas in this lecture are:
- **Ownership:** which object or component is responsible for the resource's lifetime?
- **Lifetime:** when does the resource become valid, and when is it released?
- **Observation:** can code access a resource without owning it?
- **Transfer:** can ownership move from one object to another without copying the resource?
- **Representation:** how can a value's possible states and types be expressed directly in the type system?

### RAII: Resource Acquisition Is Initialization
**RAII** connects a resource's lifetime to an object's lifetime. The object acquires or takes responsibility for the resource during construction and releases it during destruction. When the object leaves scope, its destructor runs automatically, including during stack unwinding caused by an exception.

Standard-library types already use this principle. For example, `std::lock_guard` locks a mutex when constructed and unlocks it when destroyed:
```cpp
#include <iostream>
#include <mutex>

std::mutex deviceMutex;

void updateDevice() {
    std::lock_guard<std::mutex> lock(deviceMutex);
    std::cout << "Updating device safely\n";
    // The mutex is unlocked automatically when lock leaves scope.
}

int main() {
    updateDevice();
}
```
The same design principle underlies smart pointers: a smart-pointer object manages the lifetime of a dynamically allocated object and cleans it up when its ownership ends.
### Smart Pointers and Ownership
Smart pointers are defined in the `<memory>` header. The three principal types have different ownership semantics:
- `std::unique_ptr<T>`: one exclusive owner.
- `std::shared_ptr<T>`: shared ownership through reference counting.
- `std::weak_ptr<T>`: a non-owning observer of an object managed by `std::shared_ptr<T>`.

They are not interchangeable. Pick the type that accurately describes the lifetime relationship in the program.
#### `std::unique_ptr`: Exclusive ownership
A `std::unique_ptr<T>` owns one object. It cannot be copied, because copying would create two purported exclusive owners. It can be moved, which transfers ownership to another `unique_ptr`.

Use `std::make_unique<T>(...)` to create an object managed by a `unique_ptr`.
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
In this example:
- `std::make_unique<std::string>(...)` creates a `std::string` and returns a `unique_ptr` that owns it.
- `*sensorName` accesses the managed string.
- `sensorName->size()` calls a member function through the pointer.
- When `sensorName` is destroyed, the string is destroyed automatically.


Because `unique_ptr` is not copyable, an ownership transfer must be explicit. `std::move` allows the move operation to be selected:
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
After the move, `destination` owns the string and `source` is empty. For `std::unique_ptr`, an ordinary move leaves the source pointer empty. The managed string itself is not copied; ownership of the allocation is transferred.

This will not compile:
```cpp
// auto secondOwner = source; // Error: unique_ptr cannot be copied.
```
A useful interface guideline is:
- Take `std::unique_ptr<T>` by value when a function should receive and take ownership.
- Take `T&`, `const T&`, or `T*` when a function only needs to observe an object and should not take ownership.

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
    inspect(*name);                  // Borrow only; name still owns the string.
    takeOwnership(std::move(name));  // Ownership is transferred.
}
```
Other useful `unique_ptr` operations are:
- `if (ptr)` or `ptr != nullptr`: check whether it owns an object.
- `ptr.get()`: obtain a raw, non-owning pointer to the object. It does not transfer ownership.
- `ptr.reset()`: destroy the currently owned object and optionally begin owning another one.
- `ptr.release()`: give up ownership and return the raw pointer **without deleting it**. Use this only when another clearly defined owner will take responsibility; otherwise it can cause a leak.
- `std::make_unique<T[]>(count)`: create an array managed by `std::unique_ptr<T[]>` in C++14 and later.

A raw pointer obtained from `.get()` must not be deleted by the observer. The `unique_ptr` remains responsible for cleanup.
#### `std::shared_ptr`: Shared ownership
Sometimes several objects genuinely need to keep one resource alive. A `std::shared_ptr<T>` supports this model using a **shared control block** that tracks ownership. Copying a `shared_ptr` creates another owner; destroying or resetting an owner decreases the ownership count. The managed object is destroyed when the final shared owner releases it.

Prefer `std::make_shared<T>(...)` for ordinary creation. It commonly allocates the object and control block together.
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
        std::cout << "Value through first owner: " << *firstOwner << '\n';
    }

    std::cout << "Owners after scope: " << firstOwner.use_count() << '\n';
}
```
Both pointers refer to the same integer, so changing `*secondOwner` changes the value observed through `firstOwner` as well. When `secondOwner` leaves scope, it stops being an owner.

`use_count()` is useful for learning and occasional diagnostics, but program logic should usually not depend on a particular count. Ownership can change as code runs, and a count alone does not prove that concurrent access to the object is safe.
#### When should `shared_ptr` be used?

Use shared ownership only when multiple independent components must be able to extend the resource's lifetime. If one component clearly owns the object, prefer `unique_ptr`. If a function only needs temporary access, use a reference or non-owning pointer rather than copying a `shared_ptr` just to inspect the object.

The reference-count bookkeeping helps manage lifetime, but it does **not** automatically make the managed object's data thread-safe. Concurrent reads and writes to the object still need an appropriate synchronization design.

#### `std::weak_ptr`: Non-owning observation
A `std::weak_ptr<T>` observes an object managed by `std::shared_ptr<T>` without increasing its strong ownership count. A weak pointer does not keep the object alive. To access the object safely, call `.lock()`. It returns a `shared_ptr` if the object is still alive, or an empty `shared_ptr` if the object has already been destroyed.
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
 Calling `.lock()` and using the returned `shared_ptr` keeps the object alive for the duration of that shared owner.

#### Reference counting and ownership cycles
Reference counting has an important limitation: a cycle of `shared_ptr` objects can keep itself alive. Suppose object A owns B through a `shared_ptr`, while B owns A through another `shared_ptr`. Each object has an owner even after the rest of the program releases its references, so neither object's reference count reaches zero.

A common solution is to model the primary ownership direction with `shared_ptr` and the reverse observation with `weak_ptr`. For a parent-child relationship, the parent can own its child, while the child observes its parent:
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Node {
    std::string name;
    std::shared_ptr<Node> child; // Owning relationship.
    std::weak_ptr<Node> parent;  // Non-owning back-reference.

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
The parent-child ownership is clear: `root` strongly owns `leaf`, while `leaf` does not strongly own `root`. This prevents the back-reference from creating a strong ownership cycle.

#### Custom deleters and resource cleanup
Smart pointers normally destroy an object with its ordinary destructor and deallocation mechanism. Some resources use a different cleanup operation, such as a C file handle that must be closed with `std::fclose`. A **custom deleter** tells the smart pointer how to release that resource.
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
Here, `FileCloser` is a function object that provides the custom deleter. `file` owns the handle, and the smart pointer invokes `FileCloser` when the handle is released. In real programs, check the return value of cleanup operations when failure matters to the application.

Custom deleters are useful for C libraries, operating-system handles, device APIs, and other resources whose cleanup function is not an ordinary `delete` operation. The deleter is part of the `unique_ptr` type, so different deleter types produce different `unique_ptr` types.
### Value Categories and References
C++ expressions have **value categories**. These categories affect which functions can be called, which references can bind, and whether a move operation can be selected. The topic can feel abstract at first, so begin with the distinction between an object and an expression that refers to it.
#### Lvalues and rvalues
An **lvalue** is an expression that identifies an object or function and can appear in contexts that require an identifiable object. A named variable such as `count` is an lvalue expression:
```cpp
int count = 10;
count = 20; // count is an lvalue expression on the left side.
```
An **rvalue** is a broader category that includes expressions commonly used to initialize objects or represent values that can be moved from. Literals such as `42` and temporary strings such as `std::string("ready")` are common rvalues.
```cpp
int x = 42;                       // 42 is a prvalue.
std::string s = "ready";         // The string literal initializes s.
std::string t = std::string("go"); // Temporary string expression.
```
value often means “named object expression” and rvalue often means “temporary or expiring expression.” That intuition is helpful, but the formal categories below are more precise.
#### The categories: `glvalue`, `prvalue`, and `xvalue`
C++ uses three primary categories:
- **lvalue:** an expression that identifies an object or function and is not an xvalue.
- **xvalue (expiring value):** an expression that identifies an object whose resources may be reused; `std::move(object)` is a familiar example.
- **prvalue (pure rvalue):** a value computation that initializes an object or computes a value, such as `42` or `a + b` for integers.

Two umbrella categories are also important:
- **glvalue (generalized lvalue)** = lvalue or xvalue.
- **rvalue** = prvalue or xvalue.

#### Lvalue references and rvalue references
An **lvalue reference**, written `T&`, normally binds to an lvalue of a compatible type. An **rvalue reference**, written `T&&`, normally binds to a compatible rvalue. `const T&` is special because it can bind to both lvalues and rvalues, making it useful for read-only parameters.
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

    describe(name);            // Selects const std::string& overload.
    describe(std::string("Fan")); // Selects std::string&& overload.
    describe(std::move(name)); // Also selects std::string&& overload.
}
```
In the third call, `std::move(name)` does not itself move the string. It makes the expression eligible to bind to an rvalue reference, so the rvalue-reference overload is selected. What that overload does with the object determines whether anything is actually moved from it.

#### Reference-binding guide

| Reference declaration | Typical binding behavior                                                 |
| --------------------- | ------------------------------------------------------------------------ |
| `T& ref`              | Binds to a compatible non-const lvalue                                   |
| `const T& ref`        | Binds to a compatible lvalue or rvalue, read-only through this reference |
| `T&& ref`             | Binds to a compatible non-const rvalue                                   |
| `const T&& ref`       | Can bind to a compatible const rvalue, but is relatively uncommon        |

There are additional rules for derived classes, conversions, and template type deduction. For everyday code, the table captures the most useful starting point.

#### Named variables and expression value categories
A subtle but essential rule is that **a named variable is an lvalue expression even when its declared type is an rvalue reference**.
```cpp
#include <iostream>
#include <string>
#include <utility>

void accept(std::string&& text) {
    std::cout << text << '\n';
}

int main() {
    std::string original = "compressor";
    std::string&& reference = std::move(original);

    // accept(reference);            // Error: reference is a named lvalue expression.
    accept(std::move(reference));    // Explicitly casts the expression to an rvalue.
}
```
The declaration `std::string&& reference` says what type `reference` has. It does not make every later use of the name `reference` an rvalue. This rule is one reason that move constructors use `std::move` on named members and parameters when they intend to move from them.

#### How value categories influence copying and moving
When an object is initialized from an lvalue, a copy constructor is commonly selected if copying is available. When initialized from a suitable rvalue, a move constructor may be selected. The exact overload resolution depends on the type and the available constructors.
```cpp
#include <iostream>
#include <string>
#include <utility>

int main() {
    std::string a = "a long string that may allocate memory";
    std::string copy = a;             // Copies from an lvalue.
    std::string moved = std::move(a); // Enables moving from a.

    std::cout << "copy: " << copy << '\n';
    std::cout << "moved: " << moved << '\n';
    // a remains valid, but its value is unspecified after the move.
}
```
A move can be cheaper than a deep copy because it can transfer ownership of internal resources rather than duplicate them. Not every move is free, and not every rvalue is necessarily moved from. The class's constructors and assignment operators define the actual behavior.
### Move Semantics
Move semantics allow a type to transfer resources from one object to another. They are particularly useful for objects that manage dynamically allocated memory, large buffers, file handles, or other resources whose ownership can be transferred.

#### Why move semantics exist
Suppose a vector owns a large dynamically allocated buffer. Copying the vector generally means allocating a new buffer and copying its elements. Moving the vector can often transfer its internal buffer to the destination, avoiding an element-by-element copy.

Move semantics are useful for:

- Returning large objects from functions efficiently.
- Transferring ownership of dynamically allocated resources.
- Building containers that can efficiently reallocate or rearrange elements.
- Expressing that a source object's resources may be reused by a destination.

Compilers can eliminate many copies through copy elision, but move semantics still matter when a distinct source object must transfer resources.

#### What `std::move` actually does
`std::move` is declared in `<utility>`. It does **not** transfer resources by itself. It is a cast that produces an rvalue expression from its argument, allowing a move constructor or move-assignment operator to be selected if one is available and appropriate.
```cpp
#include <iostream>
#include <string>
#include <utility>

int main() {
    std::string source = "sensor data";

    std::cout << "The source is still a valid string object.\n";
    std::string destination = std::move(source); // This initialization can move.
    std::cout << destination << '\n';
}
```
Think of `std::move(x)` as “allow an operation to treat `x` as an rvalue.” The operation that consumes the expression is what performs the move.

Avoid moving from an object when you still need its original value. Also, do not write `std::move` on a `const` object expecting the usual efficient move: many move operations require a non-const rvalue, so a const object may instead be copied.
#### Move constructors
A **move constructor** initializes a new object from an rvalue of the same type. Its common signature is:
```cpp
TypeName(TypeName&& other);
```
A move constructor usually transfers resources and leaves `other` in a valid state that can be safely destroyed or assigned a new value. The exact state after moving depends on the type's contract.

Here is a class that owns a vector of measurements. The example explicitly declares copy and move operations to illustrate the familiar Rule-of-Five interface; in ordinary code, letting `std::vector` manage its resource often means these declarations are unnecessary.

```cpp
#include <utility>
#include <vector>

class MeasurementBatch {
private:
    std::vector<double> values_;

public:
    MeasurementBatch() = default;
    explicit MeasurementBatch(std::vector<double> values)
        : values_(std::move(values)) {}

    MeasurementBatch(const MeasurementBatch&) = default;
    MeasurementBatch& operator=(const MeasurementBatch&) = default;

    MeasurementBatch(MeasurementBatch&& other) noexcept
        : values_(std::move(other.values_)) {}

    MeasurementBatch& operator=(MeasurementBatch&& other) noexcept {
        if (this != &other) {
            values_ = std::move(other.values_);
        }
        return *this;
    }

    ~MeasurementBatch() = default;
};
```
Important details:
- The constructor taking `std::vector<double>` by value can move from its parameter into `values_`.
- The move constructor initializes the destination member by moving from `other.values_`.
- The move-assignment operator replaces the destination's current member value with the source member's value, according to `std::vector`'s move-assignment behavior.
- The self-assignment check makes the intended behavior explicit. For many standard-library members, self-move assignment remains valid but can leave the value unspecified, so avoiding accidental self-moves can make application logic clearer.
- `noexcept` is important for move operations when it is truthful: some standard-library containers prefer a non-throwing move when growing their storage.


#### Move assignment operators
A **move-assignment operator** transfers or reassigns resources into an object that already exists. Its common signature is:
```cpp
TypeName& operator=(TypeName&& other);
```
The difference is:
- A move constructor creates a new destination object from the source.
- A move-assignment operator acts on an already-constructed destination object and must correctly deal with whatever resources it already owns.

`std::unique_ptr` provides a clear example:
```cpp
#include <iostream>
#include <memory>
#include <string>
#include <utility>

int main() {
    auto first = std::make_unique<std::string>("first device");
    auto second = std::make_unique<std::string>("second device");

    second = std::move(first); // Move assignment.

    std::cout << *second << '\n';
    std::cout << std::boolalpha << static_cast<bool>(first) << '\n';
    // The previous object owned by second is destroyed during assignment.
    // first is empty; second owns the first device string.
}
```
The old resource owned by `second` is released as part of assigning the new ownership. After the move, `first` is empty and `second` owns the original object from `first`.
#### Moved-from object states
For standard-library types, a moved-from object is generally **valid but in an unspecified state**, unless the type documents a more specific postcondition. “Valid” means the object can be destroyed and used in operations allowed by its contract. “Unspecified” means you must not assume it still contains the old value.

Good practice after moving from an ordinary standard-library object:

- Destroy it normally, or assign a new value to it.
- Use only operations whose requirements are satisfied by its current state.
- Do not assume a moved-from string or vector is empty unless that type's contract guarantees it for the specific operation.

For `std::unique_ptr`, the move operation has a stronger, documented result: the source becomes empty.
#### Rule of Five and Rule of Zero
The **Rule of Five** says that when a class needs to define any of the following because it directly manages a resource or has special copy/move behavior, you should review all five together:
1. Destructor.
2. Copy constructor.
3. Copy-assignment operator.
4. Move constructor.
5. Move-assignment operator.

Defining one special member can affect whether others are generated automatically. For instance, declaring a move constructor can cause the implicitly declared copy operations to be deleted. Be explicit about the intended copy and move policy.

The **Rule of Zero** is usually the better default for application code: compose members such as `std::string`, `std::vector`, and `std::unique_ptr` that already manage their own resources, and avoid writing custom destructors, copy operations, or move operations unless the class truly needs special behavior.

Use `= delete` when an operation must be forbidden, and `= default` when the normal compiler-generated behavior is correct and you want to state that intent explicitly.
### Type-Safe Alternatives to Sentinels and Unstructured Values
Programs often need to represent a value that may be absent, one value from a known set of possible types, or a value whose type is determined dynamically. Traditional code sometimes represents these states with magic numbers, null pointers, untyped `void*`, or loosely documented conventions. C++17 provides standard-library types that express these possibilities more clearly.
####  `std::optional`: A value that may be absent
`std::optional<T>` represents either:
- a value of type `T`, or
- no value.

It is declared in `<optional>` and was introduced in C++17. It is useful when “no result” is a normal outcome, such as a missing configuration value, unavailable sensor reading, or unsuccessful lookup.
```cpp
#include <iostream>
#include <optional>

std::optional<double> readPressure(bool sensorResponded) {
    if (!sensorResponded) {
        return std::nullopt;
    }
    return 101.3;
}

int main() {
    auto pressure = readPressure(true);

    if (pressure) {
        std::cout << "Pressure: " << *pressure << " kPa\n";
    } else {
        std::cout << "No pressure reading available\n";
    }
}
```
Here, `std::nullopt` explicitly means that no value is present. The `if (pressure)` check tests whether a value exists, and `*pressure` accesses it only after that check.

We can work with optional and access it value using one of thes following ways
- `if (opt)` or `opt.has_value()`: test whether a value is present.
- `*opt` or `opt->member`: access the contained value; use only when engaged.
- `opt.value()`: access the value, throwing `std::bad_optional_access` if no value is present.
- `opt.value_or(fallback)`: return the value if present, otherwise return the supplied fallback value.
- `opt.reset()`: make the optional empty.

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
The main advantage is semantic clarity. A return type such as `std::optional<double>` tells callers that a result may be absent. The caller does not need to guess that `-1.0`, `0.0`, or another special value means “no reading.”

`std::optional<T>` stores its value directly within the optional object; it does not inherently allocate a separate object on the heap. An optional is not a substitute for an error type when the program must explain *why* an operation failed. In that situation, consider a dedicated result type or an error-handling design that preserves the failure reason.

#### `std::variant`: One of several known types
`std::variant<Types...>` stores one active value from a fixed set of alternative types. It is declared in `<variant>` and was introduced in C++17. Unlike an untyped pointer, a variant remembers which alternative is currently active and provides checked access mechanisms.

For example, a device configuration setting might be an integer, floating-point value, or string:
```cpp
#include <iostream>
#include <string>
#include <variant>

int main() {
    using Setting = std::variant<int, double, std::string>;

    Setting setting = 42;
    std::cout << std::get<int>(setting) << '\n';

    setting = 2.5;
    std::cout << std::get<double>(setting) << '\n';

    setting = std::string("automatic");
    std::cout << std::get<std::string>(setting) << '\n';
}
```
At any one time, the variant holds one active alternative. `std::get<T>(value)` retrieves the value if the requested type is active; if the alternative does not match, it throws `std::bad_variant_access`.

When the same type appears more than once in a variant's alternative list, use index-based access or otherwise design the alternatives so access is unambiguous. Most code is easier to maintain when each alternative type appears once.

#### Checking the active alternative
`std::holds_alternative<T>(value)` checks which type is active. `std::get_if<T>(&value)` returns a pointer to the contained value if the type matches, or `nullptr` otherwise.
```cpp
#include <iostream>
#include <string>
#include <variant>

int main() {
    using Reading = std::variant<int, double, std::string>;
    Reading reading = 18.75;

    if (std::holds_alternative<double>(reading)) {
        std::cout << "Floating-point reading: "
                  << std::get<double>(reading) << '\n';
    }

    if (const auto* text = std::get_if<std::string>(&reading)) {
        std::cout << "Text reading: " << *text << '\n';
    } else {
        std::cout << "The active alternative is not a string\n";
    }
}
```
#### Processing alternatives with `std::visit`
`std::visit` invokes a callable with the currently active value. It is useful when each alternative needs different handling.
```cpp
#include <iostream>
#include <string>
#include <variant>

int main() {
    using Reading = std::variant<int, double, std::string>;
    Reading reading = std::string("sensor offline");

    std::visit([](const auto& value) {
        std::cout << "Value: " << value << '\n';
    }, reading);
}
```

The generic lambda works for all alternatives because each of these types supports stream insertion. If alternatives require different operations, use overloads or compile-time branching (such as `if constexpr`) to customize behavior for each type.

A variant is often a good choice when the set of possible types is known at compile time. It provides more static structure than `std::any` and makes the permitted alternatives visible in the type declaration.

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

#### Accessing a stored value safely
`std::any_cast<T>(value)` retrieves a value of the requested type. If the contained type is not `T`, the value-returning form throws `std::bad_any_cast`. To check without throwing, use the pointer form:
```cpp
#include <any>
#include <iostream>
#include <string>

int main() {
    std::any metadata = std::string("batch-17");

    if (const auto* label = std::any_cast<std::string>(&metadata)) {
        std::cout << "Label: " << *label << '\n';
    } else {
        std::cout << "Metadata is not a string\n";
    }

    if (const auto* count = std::any_cast<int>(&metadata)) {
        std::cout << "Count: " << *count << '\n';
    } else {
        std::cout << "Metadata is not an integer\n";
    }
}
```
Other useful operations include:

- `metadata.has_value()`: test whether an object is stored.
- `metadata.reset()`: clear the stored object.
- `metadata.type()`: obtain a `std::type_info` reference describing the current contained type, or `typeid(void)` if empty.

Use `std::any` when a component genuinely needs to store values of varying, runtime-selected types and the exact type is not conveniently represented by a fixed variant. Because the contained type is not visible in the `any` declaration, callers may need runtime checks and clearer interface documentation.

## Tasks

The tasks below are designed to be completed after studying the examples. Use C++17 and compile each program with warnings enabled.

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