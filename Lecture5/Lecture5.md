# Classes, Objects, and Object-Oriented Programming

## Learning Objectives
- Design classes with private data and a clear public interface.
- Use constructors, destructors, member functions, and static members.
- Overload operators when the meaning is natural and unsurprising.
- Apply inheritance, virtual functions, abstract classes, and polymorphism.
- Understand copying and the Rule of Zero, Three, and Five.
## Object-Oriented Programming in C++
### Introduction
In the last lecture, we explored **functional programming** and how it helps us organize a program into smaller, reusable functions, with each function responsible for a particular task. This approach works well for many problems, but as programs become larger, we sometimes need a different way to organize our code.

Imagine that we want to develop a program for managing a pet store. We need to represent cats, dogs, and other animals, each with its own name, age, and behavior. We could store this information in variables and write functions to manipulate it, but as the program grows, keeping everything organized becomes increasingly difficult. We need a way to group related data and the functions that operate on that data.

This is where **Object-Oriented Programming (OOP)** comes in. Instead of organizing our program only around functions, we organize it around objects that combine data and behavior. A bank account, for example, has data such as its balance and account number, but it also has behaviors such as depositing money, withdrawing money, and checking the balance.

To understand how this works in C++, we first need to distinguish between two concepts: **classes and objects**.

A **class** is a blueprint that defines the data and behaviors that a particular type of object will have. An **object** is an actual instance of that class, created when we want to use it in our program. We can create multiple objects from the same class, and although they share the same structure, each object maintains its own state.
### Creating Our First Class
In C++, we define a class using the `class` keyword, followed by its name and a pair of curly braces. Inside the class, we declare its **data members**, which store information about an object, and its **member functions**, which define what the object can do.

Consider the following example:
```cpp
#include <iostream>
#include <string>
using namespace std;

class Cat {
public:
    string name = "Catos";

    void talk() {
        cout << "Meow, meow, meow" << endl;
    }
};

int main() {
    Cat mycat;

    cout << mycat.name << endl;
    mycat.talk();

    return 0;
}
```
Here, `name` is a data member, while `talk()` is a member function. The `public` keyword allows us to access both from outside the class.

Inside `main()`, we create an object named `mycat` using the class name `Cat`. We then use the dot operator (`.`) to access its members. When we write `mycat.name`, we access the object's name, and when we write `mycat.talk()`, we call its function.

There is one important detail to notice: in C++, **class members are private by default**. In our example, we explicitly wrote `public` because we wanted to access the members from `main()`. 
### Access Specifiers and Encapsulation
Not every piece of data should be accessible from everywhere in a program. Consider a bank account whose balance is stored in a variable. If any part of the program could directly change that balance, someone could accidentally assign a negative value or bypass the withdrawal rules. To prevent this, C++ provides three main access specifiers: `public`, `private`, and `protected`.

A `public` member can be accessed from anywhere the object or class is accessible, subject to the normal rules of C++.

A `private` member can be accessed directly only by member functions and other authorized entities of the same class. Code outside the class cannot access it directly.

A `protected` member is similar to a private member, but it can also be accessed by derived classes, subject to the inheritance access rules. 

For example, consider a circle:
```cpp
#include <iostream>
using namespace std;

class Circle {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getArea() const {
        const double PI = 3.141592653589793;
        return PI * radius * radius;
    }
};

int main() {
    Circle circle(5);
    cout << "Area: " << circle.getArea() << endl;
    // circle.radius = 10; // Error: radius is private
    return 0;
}
```
Here, `radius` is private, while `getArea()` is public. This means that we cannot directly access or modify `radius` from outside the class. Instead, we must use the public methods provided by the class to interact with its internal data.

This is an example of **encapsulation**: we keep data and the operations that work on it together while controlling how the internal state can be accessed or modified.

Encapsulation is not simply about hiding variables. It also allows us to protect the rules that our objects must follow and prevent invalid modifications to their internal data.
### Getters and Setters
Sometimes, we want to allow users to read or modify a private member without exposing it directly. We can provide a getter to retrieve its value and a setter to change it.

A getter returns the value of a member, while a setter modifies it, usually after checking whether the new value is valid.
```cpp
#include <iostream>
#include <string>
using namespace std;

class Cat {
private:
    string name;

public:
    Cat(const string& n) : name(n) {}

    const string& getName() const {
        return name;
    }

    void setName(const string& n) { // setter
        if (!n.empty()) {
            name = n;
        }
    }

    void talk() const {
        cout << name << " says meow!" << endl;
    }
};

int main() {
    Cat mycat("Mimi");
    cout << mycat.getName() << endl;
    mycat.setName("Kitty");
    mycat.talk();
    mycat.setName(""); // Rejected: the name must not be empty
    return 0;
}
```
Notice that the `setName()` setter checks whether the new name is empty before changing the object's state. Without this check, the class would have no way to prevent an invalid name from being assigned.

Also, `getName()` and `talk()` are declared with `const` at the end of their declarations. A **const member function** promises not to modify the object's ordinary data members. 
### Constructors 
When we create an object, we usually want its data members to start with meaningful values. We could create the object first and assign its members afterward, but this approach can become inconvenient, and it may leave the object in an invalid state if we forget to initialize something.

C++ solves this problem with **constructors**. A constructor is a special member function that runs automatically when an object is created. Its main purpose is to initialize the object and establish its initial state.

A constructor has the same name as its class and has no return type, not even `void`. It can accept parameters, allowing us to provide the values the object needs at creation time.
#### Default and Parameterized Constructors
A default constructor is a constructor that can be called without arguments. A parameterized constructor accepts arguments that allow us to initialize an object with specific values.

Consider our `Cat` class:
```cpp
#include <iostream>
#include <string>
using namespace std;

class Cat {
private:
    string name;
    int age;

public:
    Cat() { // Default constructor
        name = "Unknown";
        age = 0;
    }
    Cat(const string& n, int a) { // Parameterized constructor
        name = n;
        age = a;
    }
    void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

int main() {
    Cat cat1;
    Cat cat2("Mimi", 4);

    cat1.display();
    cat2.display();

    return 0;
}
```
The first object uses the default constructor, so it receives the default values. The second uses the parameterized constructor, allowing us to specify its name and age.

There is an important rule to remember: **if we declare a constructor with parameters and do not provide a default constructor ourselves, the compiler generally will not generate a default constructor for us.**

For example, If our class has only `Cat(const string& n, int a)`, writing `Cat cat1;` would cause a compilation error.
#### Constructor Initialization Lists
In the previous example, we assigned values to the members inside the constructor's body. However, C++ offers a more direct way to initialize them: the constructor initialization list.

We write a colon after the constructor's parameter list, followed by the members we want to initialize.
```cpp
class Cat {
private:
    string name;
    int age;

public:
    Cat(const string& n, int a)
        : name(n), age(a) {
    }

    void display() const {
        cout << name << ", " << age << endl;
    }
};
```
Here, `name(n)` initializes `name` directly from `n`, and `age(a)` initializes `age` from `a`.

There is one important detail: **members are initialized in the order in which they are declared in the class, not the order in which they appear in the initialization list.** For this reason, we should normally list them in declaration order.
### The `this` Pointer
When we work with constructors and member functions, we sometimes use parameter names that are identical to member names. To avoid the conflict between the two variables C++ provide use `this` keyword   

Consider a class that stores a person's name:
```cpp
class Person {
private:
    string name;

public:
    Person(const string& name) {
        this->name = name;
    }
};
```
Here, `name` refers to the constructor parameter, while `this->name` refers to the current object's data member.

The `this` pointer is available inside non-static member functions and points to the current object on which the function is operating.

For example, if we create `Person p1("Ali")` and then call a member function on `p1`, `this` refers to `p1` during that call.
### Destructors and Object Lifetime
We have seen how constructors prepare an object for use. At the other end of its lifetime, C++ provides destructors, which allow an object to perform cleanup before its lifetime ends.

A destructor has the same name as the class, preceded by a tilde (`~`), and it has no return type and takes no parameters.
```cpp
#include <iostream>
#include <string>
using namespace std;

class Cat {
private:
    string name;

public:
    Cat(const string& n) : name(n) {
        cout << name << " is created." << endl;
    }
    ~Cat() { // Destructor
        cout << name << " is destroyed." << endl;
    }
    void talk() const {
        cout << name << " says meow!" << endl;
    }
};

int main() {
    Cat cat("Mimi");
    cat.talk();
    cout << "End of main." << endl;
    return 0;
}
```
When `cat` is created, its constructor runs. When execution leaves `main()`, the local object is destroyed automatically, and its destructor runs.

Destructors are particularly useful when a class manages resources, such as files, locks, or dynamically allocated memory. For a class that only contains ordinary standard-library members, such as `std::string`, the compiler-generated destructor is often sufficient.
### Static Members:
Every object  maintain its own data members. If we create three `Cat` objects, each has its own `name` and `age`.

But what if we want to know how many `Cat` objects have been created? Storing that information separately in every object would not make sense. We need a value shared by all instances of the class. This is where **static data members** become useful.

A static data member belongs to the class itself rather than to an individual object. All instances share the same variable.
```cpp
#include <iostream>
using namespace std;

class Cat {
private:
    static int count;

public:
    Cat() {
        count++;
    }

    static int getCount() {
        return count;
    }
};

int Cat::count = 0;

int main() {
    Cat cat1;
    Cat cat2;
    Cat cat3;

    cout << "Number of cats: " << Cat::getCount() << endl;
    return 0;
}
```
The variable `count` is shared by all `Cat` objects. Each time a constructor runs, it increments the same variable.

Notice that we define `count` outside the class using `Cat::count`. This is the traditional definition required for a non-inline static data member. In C++17 and later, we can alternatively declare it as `inline static int count = 0;` inside the class.

The function `getCount()` is also static. A **static member function** can be called using the class name, as in `Cat::getCount()`, without creating an object.
### Operator Overloading
Suppose we have two objects representing points in a two-dimensional coordinate system. It would be convenient to write `p1 + p2` rather than call a function such as `addPoints(p1, p2)`.

C++ allows us to define how certain operators behave for user-defined types. This feature is called operator overloading.
#### Arithmetic Operators
Consider a `Point` class that stores two coordinates. When we add two points, we want the resulting point to contain the sum of their respective coordinates.
```cpp
#include <iostream>
using namespace std;

class Point {
public:
    double x, y;

    Point(double x, double y) : x(x), y(y) {}

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
};

int main() {
    Point p1(4, 8);
    Point p2(2, 3);

    Point p3 = p1 + p2;
    Point p4 = p1 - p2;

    cout << "p3: (" << p3.x << ", " << p3.y << ")" << endl;
    cout << "p4: (" << p4.x << ", " << p4.y << ")" << endl;

    return 0;
}
```
When the compiler encounters `p1 + p2`, it uses the overloaded `operator+()` function. The current object provides the left operand, while `other` refers to the right operand.

The `const Point&` parameter allows us to pass the other point without copying it, and the trailing `const` guarantees that the operation does not modify the left operand.
#### Comparison Operators
For our `Point` class, we might decide that two points are equal when both coordinates are equal.

We can implement this by overloading `operator==()`:
```cpp
bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
}
```
This function can be added to the public section of `Point`.
```cpp
Point p1(4, 8);
Point p2(4, 8);
Point p3(1, 2);

cout << (p1 == p2) << endl; // 1: true
cout << (p1 == p3) << endl; // 0: false
```
#### Assignment Operators and Copying Objects
The assignment operator (`=`) allows us to copy the state of one existing object into another. Consider the following example:
```cpp
Point p1(4, 8);
Point p2(1, 2);

p2 = p1;
```
Initially, `p1` stores the coordinates `(4, 8)`, while `p2` stores `(1, 2)`. When we write `p2 = p1`, the values of `p1` are copied into `p2`, so both objects now store `(4, 8)`. However, they remain two separate objects, meaning that changing `p2` afterward does not change `p1`.

However, assignment is not the same as initialization:
```cpp
Point p1(4, 8);

Point p2 = p1;  // Copy constructor
p2 = p1;        // Copy assignment operator
```
In the first case, `p2` is being created and initialized using the existing object `p1`, so the copy constructor is used. In the second case, `p2` already exists, and we are replacing its current state with the state of `p1`, so the copy assignment operator is used.  

The **copy constructor** controls how a new object is created from an existing object, while the **copy assignment operator** controls how an existing object receives the state of another object.
```cpp
#include <iostream>
using namespace std;

class Number {
private:
    int* value;

public:
    Number(int v) {
        value = new int(v);
    }
    // Copy constructor
    Number(const Number& other) {
        value = new int(*other.value);
    }
    // Copy assignment operator
    Number& operator=(const Number& other) {
        if (this != &other) {
            *value = *other.value;
        }
        return *this;
    }
    ~Number() {
        delete value;
    }
    void display() {
        cout << *value << endl;
    }
};

int main() {
    Number n1(10);
    Number n2 = n1;  // Calls the copy constructor
    Number n3(20);
    n3 = n1;         // Calls the copy assignment operator
    n2.display();    // 10
    n3.display();    // 10
    return 0;
}
```
In this example, the copy constructor allocates new memory for `n2` and copies the value stored in `n1`. This ensures that the two objects own separate memory rather than sharing the same pointer.

The assignment operator handles a different situation. Since `n3` already exists and owns allocated memory, we copy the value from `n1` into the memory that `n3` already owns. We also check `this != &other` to avoid unnecessary work when an object is assigned to itself. Finally, `return *this` returns the current object by reference, allowing assignments to be chained.
#### Stream Operators
We have been using `cout` to print numbers, strings, and other values. However, when we try to print an object directly, such as `cout << p1`, C++ does not automatically know how we want that object to be displayed. We can solve this by overloading the **stream insertion operator (`<<`)**, allowing us to define how objects of our class are printed.
```cpp
#include <iostream>
using namespace std;

class Point {
private:
    double x, y;

public:
    Point(double x, double y) : x(x), y(y) {}

    friend ostream& operator<<(ostream& out, const Point& p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
};

int main() {
    Point p1(4, 8);

    cout << "Point: " << p1 << endl;

    return 0;
}
```
When we write `cout << p1`, the overloaded `operator<<` function is called. It receives two arguments: the output stream, represented by `out`, and the `Point` object we want to print, represented by `p`. The function then writes the coordinates to the stream, producing `(4, 8)`.

You might wonder why the function takes an `ostream&` as its first parameter. The type `ostream` represents an output stream, such as `cout`, which is used to send data to an output destination. 

Notice that the function returns `ostream&` as well. This means it returns a reference to the same output stream it received. Returning the stream allows us to chain multiple output operations in a single statement.

For example:
```cpp
cout << "Point: " << p1 << endl;
```
C++ evaluates this expression from left to right in terms of the chained stream operations. First, it inserts `"Point: "` into `cout`. The stream is then returned, allowing the next `<<` operation to print `p1`. Finally, `endl` inserts a newline and flushes the stream. If our overloaded operator did not return the stream, this chaining would not work as expected.

There is another important detail in our implementation: the `operator<<` function is declared using the keyword `friend`.

The keyword `friend` allows a function defined outside the class to access its private and protected members. In our example:
```cpp
friend ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}
```
By declaring `operator<<` as a friend, we allow it to access `p.x` and `p.y` directly, even though they are private.

One final detail: **a friend function is not a member function of the class**, even when its definition appears inside the class declaration. The `friend` keyword simply grants it access to private and protected members. It does not make the function a member of the class.
#### Member and Non-Member Operators
When overloading operators, we can implement them either as member functions or as non-member functions. Both approaches allow us to define how operators behave with our objects, but the main difference is how the operands are passed to the function.

When an operator is implemented as a member function, the left operand is the object on which the function is called. For example, consider the following implementation of `operator+` inside the Point class:
```cpp
Point operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}
```
Now, when we write:
```cpp
Point p1(4, 8);
Point p2(1, 2);

Point p3 = p1 + p2;
```
C++ interprets `p1 + p2` as a call to `p1.operator+(p2)`. The object `p1` is the left operand and is accessed through the implicit this pointer, while `p2` is passed as the argument other. The function adds their coordinates and returns a new `Point` containing the result `(5, 10)`.

However, we can also implement the same operator as a non-member function:
```cpp
Point operator+(const Point& a, const Point& b) {
    return Point(a.getX() + b.getX(), a.getY() + b.getY());
}
```
In this version, the function is not part of the Point class. Instead, both operands are passed explicitly as arguments: `a` represents the left operand, and `b` represents the right operand.

The expression `p1 + p2` now calls `operator+(p1, p2)`. The result is the same, but the function is called differently.

Notice that this example uses `getX()` and `getY()` to access the coordinates. Since `x` and `y` are private, a non-member function cannot access them directly. 
#### Friend Functions and Friend Classes
A **friend function** is a non-member function that is granted access to a class's private and protected members. A **friend class** grants the same kind of access to all member functions of another class.

Consider our `Point` class again. We want to print its coordinates using `operator<<`, but the coordinates are private.
```cpp
#include <iostream>
using namespace std;

class Point {
private:
    double x, y;

public:
    Point(double x, double y) : x(x), y(y) {}

    friend void display(const Point& p);
};

void display(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")" << endl;
}

int main() {
    Point p(4, 8);

    display(p);

    return 0;
}
```
The declaration `friend void display(const Point& p);` gives `display()` permission to access the private coordinates. The function itself remains a non-member function; it does not receive a `this` pointer.

We can also declare an entire class as a friend:
```cpp
class Engine {
private:
    int power = 100;

    friend class Mechanic;
};

class Mechanic {
public:
    void inspect(const Engine& engine) {
        cout << engine.power << endl;
    }
};
```
The `Mechanic` class can access the private members of `Engine` because it has been declared a friend.
### Inheritance
Imagine that we want to represent several kinds of animals in a program: cats, dogs, birds, and other pets.

All these animals share certain characteristics. They have names, they may have ages, and they can perform common actions such as sleeping. Creating a separate class with all these members for every animal would lead to unnecessary duplication.

Instead, we can define a common class containing the shared members and let the other classes build upon it. This is the idea behind **inheritance**.

The class providing the shared members is called the **base class**, while the classes that inherit from it are called **derived classes**.
#### Base and Derived Classes
Let's return to our pet-store example:
```cpp
#include <iostream>
#include <string>
using namespace std;

// base class
class Pet {
protected:
    string name;
    int age;

public:
    Pet(const string& name, int age)
        : name(name), age(age) {}

    void sleep() const {
        cout << name << " is sleeping." << endl;
    }

    void walk() const {
        cout << name << " is walking." << endl;
    }
};

// derived class
class Cat : public Pet {
public:
    Cat(const string& name, int age)
        : Pet(name, age) {}

    void talk() const {
        cout << name << " says meow!" << endl;
    }
};

class Dog : public Pet {
public:
    Dog(const string& name, int age)
        : Pet(name, age) {}

    void talk() const {
        cout << name << " says woof!" << endl;
    }
};

int main() {
    Cat cat("Mimi", 4);
    Dog dog("Jack", 8);

    cat.talk();
    cat.sleep();

    dog.talk();
    dog.walk();

    return 0;
}
```
The `Pet` class contains the shared data members, `name` and `age`, as well as the common functions `sleep()` and `walk()`.

The `Cat` and `Dog` classes inherit from `Pet` using the syntax `class Cat : public Pet`. This allows them to reuse the functionality provided by the base class and introduce their own behavior.

Notice how their constructors call `Pet(name, age)` in their initialization lists. This initializes the base-class portion of each object before the derived-class constructor body executes.
### Public, Protected, and Private Inheritance
We have used `public` inheritance, but C++ also allows `protected` and `private` inheritance.

With **public inheritance**, the base class's public members remain public, and its protected members remain protected. This is the usual choice when a derived class represents a specialized form of the base class. For example, a `Dog` is a kind of `Pet`.

With **protected inheritance**, the base class's public and protected members become protected in the derived class. They can be accessed within the derived class and its descendants, but they are not publicly accessible through an ordinary object of that class.

With **private inheritance**, the base class's public and protected members become private in the derived class. They can be used by the derived class's implementation but are not exposed as public members of the derived type.

In all three cases, private members of the base class remain inaccessible directly to the derived class. They still form part of the base-class subobject, but the derived class must use accessible base-class functions to interact with them.

For example:
```cpp
class A {
public:
    int x = 10;

protected:
    int y = 20;

private:
    int z = 30;
};

class B : public A {
public:
    void display() {
        cout << x << endl; // Allowed
        cout << y << endl; // Allowed
        // cout << z << endl; // Error
    }
};
```
### Constructor and Destructor Order in Inheritance
Inheritance also affects the order in which objects are constructed and destroyed.

When we create an object of a derived class, its base-class constructor runs first, before the derived-class constructor body. If the derived class contains additional data members, they are initialized after the base classes and in the order in which they are declared.

Destruction happens in the reverse order: the derived-class destructor runs first, followed by the base-class destructor.

Consider the following example:
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base constructor" << endl;
    }

    ~Base() {
        cout << "Base destructor" << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived constructor" << endl;
    }

    ~Derived() {
        cout << "Derived destructor" << endl;
    }
};

int main() {
    Derived obj;

    return 0;
}
```
The output is:
```
Base constructor
Derived constructor
Derived destructor
Base destructor
```
### Polymorphism and Virtual Functions
Our `Cat` and `Dog` classes both have a `talk()` function, but they produce different sounds. We might want to write a function that accepts any pet and asks it to make a sound without knowing whether the actual object is a cat or a dog.

This brings us to **polymorphism**, which allows us to work with objects through a common interface while preserving their different behaviors.

However, simply defining a function with the same name in two unrelated classes is not enough to achieve runtime polymorphism. We need inheritance and virtual functions.
#### Method Overriding
Suppose we add a `talk()` function to the base class `Pet` and then provide a different implementation in `Cat` and `Dog`.

The derived classes can **override** the base-class function. To make the behavior depend on the actual object at runtime, we declare the base function as `virtual`.
```cpp
#include <iostream>
#include <string>
using namespace std;

class Pet {
protected:
    string name;

public:
    Pet(const string& name) : name(name) {}

    virtual void talk() const {
        cout << name << " makes a sound." << endl;
    }

    virtual ~Pet() = default;
};

class Cat : public Pet {
public:
    Cat(const string& name) : Pet(name) {}

    void talk() const override {
        cout << name << " says meow!" << endl;
    }
};

class Dog : public Pet {
public:
    Dog(const string& name) : Pet(name) {}

    void talk() const override {
        cout << name << " says woof!" << endl;
    }
};

int main() {
    Cat cat("Mimi");
    Dog dog("Jack");

    Pet* p1 = &cat;
    Pet* p2 = &dog;

    p1->talk();
    p2->talk();

    return 0;
}
```
Although `p1` and `p2` are pointers to `Pet`, they point to different derived objects. Because `talk()` is virtual, the program calls the appropriate derived implementation. This behavior is known as **dynamic dispatch**

The keyword `virtual` tells C++ that a function can be **overridden in a derived class and that the appropriate implementation should be selected at runtime**, based on the actual type of the object. Without `virtual`, calling `talk()` through a `Pet*` would select the base-class version instead.
#### The `override` and `final` Specifiers
You may have noticed that we wrote `override` after the `talk()` functions in the derived classes. These specifiers help us control how virtual functions behave in an inheritance hierarchy.

The `override` specifier tells the compiler that a function is intended to override a virtual function inherited from a base class. If the function does not correctly match an overridable base-class function, the compiler reports an error.

For example, if the base class declares `virtual void talk() const`, accidentally writing `void talk()` in the derived class would not override it because the `const` qualifier is missing. Adding `override` allows the compiler to catch this mistake.

The `final` specifier serves a different purpose: it prevents a virtual function from being overridden in further derived classes.
```cpp
class Cat : public Pet {
public:
    Cat(const string& name) : Pet(name) {}

    void talk() const override final {
        cout << name << " says meow!" << endl;
    }
};
```
We can also use `final` on a class itself to prevent further inheritance:
```cpp
class SpecialPet final : public Pet {
public:
    SpecialPet(const string& name) : Pet(name) {}
};
```
In this case, `SpecialPet` can inherit from `Pet`, but no other class can inherit from `SpecialPet`.
#### Virtual Destructors
We previously saw that destructors run when an object's lifetime ends. In inheritance, however, we must pay attention to how an object is deleted, especially when we use a base-class pointer to refer to a derived object.

Consider the following example:
```cpp
Pet* pet = new Cat("Mimi");
delete pet;
```
Here, `pet` is a pointer to `Pet`, but the object it points to is actually a `Cat`. If `Pet` has a non-virtual destructor, deleting the object through this base-class pointer results in **undefined behavior**.

To handle this correctly, we declare the base-class destructor as `virtual`:
```cpp
virtual ~Pet() = default;
```
Now, when we delete the object through a `Pet*`, C++ calls the derived-class destructor first, followed by the base-class destructor. 
#### Overloading and Overriding
We have encountered two related concepts that are important in C++, but they serve different purposes: **function overloading** and **function overriding**.

**Function overloading** means defining multiple functions with the same name but different parameter lists. The compiler determines which function to call based on the arguments provided.
```cpp
#include <cmath>
using namespace std;

class Distance {
public:
    double d;

    explicit Distance(double x) : d(x) {}

    Distance(double x, double y)
        : d(sqrt(x * x + y * y)) {}

    Distance(double x, double y, double z)
        : d(sqrt(x * x + y * y + z * z)) {}
};
```
We can create `Distance d1(5.0)`, `Distance d2(3.0, 4.0)`, or `Distance d3(3.0, 4.0, 6.0)`. The compiler selects the appropriate constructor according to the number and types of the arguments.

**Function overriding**, on the other hand, occurs when a derived class provides its own implementation of an inherited virtual function. The overriding function must have a compatible signature, and the `override` specifier can be used to let the compiler verify that the function actually overrides a base-class function.
### Abstract Classes and Interfaces
In the previous example, our `Pet` class provided a default implementation of `talk()`. But sometimes a base class should define a required behavior without specifying how that behavior must be implemented.

For example, a generic `Shape` class could require every derived shape to calculate its area, while leaving the actual calculation to classes such as `Circle` and `Rectangle`. C++ allows us to express this using **pure virtual functions**.

A pure virtual function is declared by placing `= 0` at the end of its declaration. A class containing at least one pure virtual function is an abstract class, and we cannot create objects of that class directly.
```cpp
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() const = 0;

    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}

    double area() const override {
        return 3.141592653589793 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h)
        : width(w), height(h) {}

    double area() const override {
        return width * height;
    }
};

int main() {
    Circle circle(5);
    Rectangle rectangle(4, 6);

    Shape* shapes[] = {&circle, &rectangle};

    for (Shape* shape : shapes) {
        cout << "Area: " << shape->area() << endl;
    }

    return 0;
}
```
The `Shape` class establishes a common interface: every concrete shape must provide an `area()` implementation before it can be instantiated.

An abstract class can contain ordinary data members, constructors, implemented member functions, and pure virtual functions. It does not have to consist entirely of abstract operations.
#### Interface
In C++, an **interface** is commonly represented by an abstract class whose main purpose is to specify operations that derived classes must provide. C++ does not have a separate `interface` keyword like some other languages, so we typically use a class containing pure virtual functions and a virtual destructor.

The distinction is conceptual: an abstract class can provide shared state and implementation, while an interface-style class focuses primarily on defining a contract.
### Copy Semantics: 
Until now, our objects have contained relatively simple data, such as numbers and strings. When we copy an object of this kind, the compiler-generated copy operations are usually sufficient.

However, things become more complicated when a class manages a resource, such as dynamically allocated memory. To understand why, we need to distinguish between copying an object's values and copying the resources it owns.
#### The Copy Constructor
A copy constructor creates a new object from an existing object of the same class.

Its usual form is:
```cpp
ClassName(const ClassName& other);
```
For example:
```cpp
#include <iostream>
#include <string>
using namespace std;

class Cat {
private:
    string name;
    int age;

public:
    Cat(const string& n, int a)
        : name(n), age(a) {}

    Cat(const Cat& other)
        : name(other.name), age(other.age) {
        cout << "Copy constructor called." << endl;
    }

    void display() const {
        cout << name << ", " << age << endl;
    }
};

int main() {
    Cat cat1("Mimi", 4);
    Cat cat2 = cat1;

    cat1.display();
    cat2.display();

    return 0;
}
```
The statement `Cat cat2 = cat1;` creates a new object by copying `cat1`. The copy constructor initializes `cat2` using the values stored in `cat1`.

Notice that this is different from assignment:
```cpp
Cat cat1("Mimi", 4);
Cat cat2("Jack", 8);

cat2 = cat1;
```
In this case, both objects already exist. The assignment operator copies the value from `cat1` into `cat2`.

For classes containing ordinary members such as `std::string` and integers, the compiler-generated copy constructor and copy assignment operator generally do the right thing.

The difficulty appears when a class owns a resource through a raw pointer.
#### Shallow Copy and Deep Copy
Consider a class that dynamically allocates memory for an integer:
```cpp
class Number {
private:
    int* value;

public:
    Number(int v) {
        value = new int(v);
    }

    ~Number() {
        delete value;
    }
};
```
This class has a problem. If we write:
```cpp
Number n1(10);
Number n2 = n1;
```
the compiler-generated copy constructor copies the pointer itself, not the integer stored at the address it points to. Both objects now hold the same pointer. When their destructors run, both attempt to delete the same allocation, resulting in undefined behavior.

This is an example of a shallow copy: the pointer value is copied, but the pointed-to resource is not duplicated.

A **deep copy** creates a separate resource for the new object.

We can implement it like this:
```cpp
#include <iostream>
using namespace std;

class Number {
private:
    int* value;

public:
    Number(int v)
        : value(new int(v)) {}

    Number(const Number& other)
        : value(new int(*other.value)) {}

    ~Number() {
        delete value;
    }

    void display() const {
        cout << *value << endl;
    }
};

int main() {
    Number n1(10);
    Number n2 = n1;

    n1.display();
    n2.display();

    return 0;
}
```
Now, `n1` and `n2` own separate allocations containing the same value. Destroying one object does not invalidate the other.

However, this implementation is still incomplete. We have defined a destructor and a copy constructor, but we have not defined how assignment should work. The compiler-generated copy assignment operator would still copy the pointer itself.
#### The Rule of Three
The **Rule of Three** states that if a class needs to define any one of the following because it manages a resource, it will often need to define all three:
- Destructor.
- Copy constructor.
- Copy assignment operator.

The reason is simple: these operations all affect the ownership and lifetime of the resource.

For example, our `Number` class needs a copy assignment operator that copies the pointed-to value rather than merely copying the pointer.
```cpp
Number& operator=(const Number& other) {
    if (this != &other) {
        *value = *other.value;
    }

    return *this;
}
```
### The Rule of Five
Modern C++ also introduces move semantics, which allow resources to be transferred instead of copied unnecessarily.

The **Rule of Five** extends the Rule of Three by including two additional operations:
- Move constructor.
- Move assignment operator.

A move constructor creates an object by transferring resources from another object, while a move assignment operator transfers resources into an object that already exists.

Both can be useful when objects own expensive resources, such as dynamically allocated buffers.

Here is a complete example:
```cpp
#include <iostream>
#include <utility>
using namespace std;

class Number {
private:
    int* value;

public:
    Number(int v)
        : value(new int(v)) {}

    // Copy constructor
    Number(const Number& other)
        : value(new int(*other.value)) {}

    // Copy assignment
    Number& operator=(const Number& other) {
        if (this != &other) {
            *value = *other.value;
        }

        return *this;
    }

    // Move constructor
    Number(Number&& other) noexcept
        : value(other.value) {
        other.value = nullptr;
    }

    // Move assignment
    Number& operator=(Number&& other) noexcept {
        if (this != &other) {
            delete value;

            value = other.value;
            other.value = nullptr;
        }

        return *this;
    }

    ~Number() {
        delete value;
    }

    void display() const {
        if (value != nullptr) {
            cout << *value << endl;
        } else {
            cout << "No value" << endl;
        }
    }
};

int main() {
    Number n1(10);
    Number n2 = n1;             // Copy construction

    Number n3 = std::move(n1);  // Move construction

    n2.display();
    n3.display();

    return 0;
}
```
The move constructor transfers the pointer from `n1` to `n3`, then sets `n1.value` to `nullptr`. The moved-from object remains valid and can safely be destroyed.

`std::move` does not transfer resources by itself. Instead, it converts an expression into an rvalue, allowing the appropriate move operation to be selected. 
#### Rule of Zero
There is also an important modern C++ guideline: **the Rule of Zero**. If we design a class using resource-managing types such as `std::string`, `std::vector`, and smart pointers, we can often avoid writing custom copy and move operations entirely.

For example, a class containing a `std::vector<int>` can generally rely on the vector's own copy, move, and destruction behavior. This is usually safer than manually managing a raw pointer.
### Multiple Inheritance
C++ also allows a class to inherit from multiple base classes, a feature known as **multiple inheritance**.

This is useful when a class needs to combine distinct capabilities. For example, a robot might need navigation and communication capabilities. Instead of defining both behaviors directly inside `Robot`, we can implement them in separate classes and let `Robot` inherit from both.
```cpp
#include <iostream>
using namespace std;

class Navigator {
public:
    void navigate() const {
        cout << "Navigating..." << endl;
    }
};

class Communicator {
public:
    void communicate() const {
        cout << "Communicating..." << endl;
    }
};

class Robot : public Navigator, public Communicator {
public:
    void operate() const {
        navigate();
        communicate();
    }
};

int main() {
    Robot robot;

    robot.navigate();
    robot.communicate();
    robot.operate();

    return 0;
}
```
The declaration `class Robot : public Navigator, public Communicator` tells the compiler that `Robot` inherits from both `Navigator` and `Communicator`. As a result, it can use their public functions without redefining them. 
#### Ambiguity in Multiple Inheritance
Consider two classes that both define a function called `display()`:
```cpp
#include <iostream>
using namespace std;

class A {
public:
    void display() const {
        cout << "Class A" << endl;
    }
};

class B {
public:
    void display() const {
        cout << "Class B" << endl;
    }
};

class C : public A, public B {
};

int main() {
    C obj;

    // obj.display(); // Error: ambiguous

    obj.A::display();
    obj.B::display();

    return 0;
}
```
The problem occurs when we call `obj.display()`. Since `C` inherits from both `A` and `B`, the compiler finds two possible functions with the same name and cannot determine which one we intend to call.

We can resolve this ambiguity using the **scope-resolution operator (`::`)** to specify the class whose function we want to execute. In the example, `obj.A::display()` calls the function inherited from `A`, while `obj.B::display()` calls the function inherited from `B`.

Alternatively, we can define our own `display()` function inside `C` to establish a specific behavior for the derived class.
#### The Diamond Problem
Imagine that we have a base class called `Person`. Two classes, `Student` and `Employee`, inherit from `Person`. We then create a class called `TeachingAssistant` that inherits from both `Student` and `Employee`.

The inheritance hierarchy looks like this:
```
          Person
          /    \
     Student   Employee
          \    /
      TeachingAssistant
```
This structure is known as the **diamond problem** because the inheritance hierarchy forms a diamond shape.

Let's see what happens when we implement it in C++:
```cpp
#include <iostream>
using namespace std;

class Person {
public:
    int id = 100;
};

class Student : public Person {
};

class Employee : public Person {
};

class TeachingAssistant : public Student, public Employee {
};

int main() {
    TeachingAssistant ta;

    // cout << ta.id; // Error: ambiguous

    cout << ta.Student::id << endl;
    cout << ta.Employee::id << endl;

    return 0;
}
```
The problem is that `TeachingAssistant` inherits from `Person` along two different paths: one through `Student` and another through `Employee`.

With ordinary inheritance, these paths create **two separate `Person` subobjects** inside `TeachingAssistant`. Each subobject has its own `id` member, so the compiler cannot determine which one we mean when we write `ta.id`.

We can access either member explicitly using `ta.Student::id` or `ta.Employee::id`, but this does not eliminate the duplication. In our example, a teaching assistant represents one person, so having two separate `Person` subobjects is probably not what we want.
#### Virtual Inheritance
To solve the diamond problem, we modify the declarations of `Student` and `Employee`:
```cpp
#include <iostream>
using namespace std;

class Person {
public:
    int id = 100;
};

class Student : virtual public Person {
};

class Employee : virtual public Person {
};

class TeachingAssistant : public Student, public Employee {
};

int main() {
    TeachingAssistant ta;

    cout << ta.id << endl;

    return 0;
}
```
Notice the addition of `virtual` in the inheritance declarations:
```cpp
class Student : virtual public Person {
};

class Employee : virtual public Person {
};
```
This tells C++ that `Person` is a **virtual base class**. When a `TeachingAssistant` object is created, both inheritance paths share the same `Person` subobject instead of creating two separate copies.

It is important to understand that virtual inheritance solves the problem of duplicated base-class subobjects, but it does not resolve every ambiguity in multiple inheritance. If two base classes independently define a function with the same name, we may still need to qualify the function or provide an explicit implementation in the derived class.
#### When Should We Use Multiple Inheritance?
Multiple inheritance is useful when a class genuinely combines distinct interfaces or capabilities. It can be especially effective when inheriting from small abstract interface classes that define separate responsibilities.

However, it should not be used simply to avoid writing a few functions. Deep inheritance hierarchies and complicated combinations of concrete base classes can make a program harder to understand and maintain.

When a class needs to use another object without representing a specialized form of that object, **composition** is often a better choice. For example, a `Robot` can contain a `Navigator` and a `Communicator` as members rather than inherit their implementations.

Inheritance expresses an _is-a_ relationship, while composition often expresses a _has-a_ relationship. Choosing between them depends on the design and the responsibilities of the classes involved.
### Namespace
Before finishing, let's return briefly to a feature we have used throughout this lecture: `namespace`.

A namespace groups related identifiers, such as functions, variables, and classes, under a common name. It helps prevent naming conflicts when different parts of a program use the same identifier.

For example, we can create a namespace for mathematical operations:
```cpp
#include <iostream>
using namespace std;

namespace Math {
    constexpr double PI = 3.141592653589793;

    double circleArea(double radius) {
        return PI * radius * radius;
    }
}

int main() {
    cout << Math::circleArea(5) << endl;

    return 0;
}
```
Here, `Math` groups the constant `PI` and the function `circleArea()`. We access the function using `Math::circleArea()`.

This becomes particularly useful in larger programs where several classes and libraries might otherwise introduce conflicting names.

Although we have used `using namespace std;` throughout these introductory examples to keep them short, it is generally better to avoid placing that directive in header files. Using qualified names such as `std::cout` and `std::string` helps prevent naming conflicts in larger projects.
## Tasks
### Task 1 :
Create a class for a bank management system. The class should represent a bank account and include the basic methods and attributes.
- **Attributes:**
    - `account_number`: A unique identifier for the account.
    - `account_holder_name`: The name of the account holder.
    - `account_balance`: The current balance in the account.
- **Methods:**
    - **Constructor**: Initializes the object attributes (account number, account holder name, and initial balance).
    - **Deposit**: Adds a specified amount of money to the account balance.
    - **Withdraw**: Deducts a specified amount of money from the account balance (if sufficient funds are available).
    - **Get Balance**: Returns the current balance of the account.
    - **Transfer**: Transfers a specified amount of money from one account to another.
    - **Display Account Info**: Displays the account information (account number, account holder name, and balance).
### Task 2 :
Create a class for representing complex numbers. The class should include the basic attributes and methods, and it should support operations by overriding operators. Additionally, it should be able to perform comparisons and return the modulus of the complex number.
- **Attributes:**
    - `real`: The real part of the complex number.
    - `imaginary`: The imaginary part of the complex number.
- **Methods:**
    - **Constructor**: Initializes the object attributes (real and imaginary parts).
    - **Addition (`+`)**: Overrides the `+` operator to add two complex numbers.
    - **Subtraction (`-`)**: Overrides the `-` operator to subtract one complex number from another.
    - **Multiplication (`*`)**: Overrides the `*` operator to multiply two complex numbers.
    - **Division (`/`)**: Overrides the `/` operator to divide one complex number by another.
    - **Equality (`==`)**: Overrides the `==` operator to check if two complex numbers are equal.
    - **Modulus**: Calculates and returns the modulus (absolute value) of the complex number.
    - **Display**: Displays the complex number in the form `a + bi`.


### Task 3: 
Create a shape management system using Object-Oriented Programming in C++. The program should represent different geometric shapes and calculate their areas and perimeters using inheritance and polymorphism.

- **Classes:**
    - `Shape`: An abstract base class that defines the common interface for all shapes.
    - `Circle`: Represents a circle.
    - `Rectangle`: Represents a rectangle.
    - `Triangle`: Represents a triangle.
- **Attributes:**
    - `Circle`: Radius.
    - `Rectangle`: Width and height.
    - `Triangle`: Three side lengths.
- **Methods:**
    - **Constructors:** Initialize each shape with its required dimensions.
    - **Area:** Implement a function that calculates the area of each shape.
    - **Perimeter:** Implement a function that calculates the perimeter of each shape.
    - **Display:** Display the type and dimensions of each shape.
    - **Get Area and Perimeter:** Use appropriate member functions to retrieve calculated values.
- **Requirements:**
    - Make `Shape` an abstract class using pure virtual functions.
    - Override the area and perimeter functions in each derived class.
    - Use a virtual destructor in the base class.
    - Store different shapes in a collection of base-class pointers or smart pointers and calculate their areas and perimeters using polymorphism.
    - Use `const` member functions wherever appropriate.
    - Protect the dimensions using `private` access and validate them during construction.
    - Overload the `<<` operator to display shape information.
    - Prevent further inheritance from one of the derived classes using `final`.

### Task 4:
Create a student management system that stores student information, calculates academic results, and manages a collection of students.
- **Classes:**
    - `Person`: Represents the common information shared by people.
    - `Student`: Inherits from `Person` and represents a student.
    - `StudentManager`: Manages a collection of students.
- **Attributes:**
    - `Person`: Name and age.
    - `Student`: Student ID, a collection of grades, and a static counter tracking the number of student objects.
    - `StudentManager`: A collection of students.
- **Methods:**
    - **Constructors:** Initialize people and students with appropriate values.
    - **Add Grade:** Add a grade after validating that it falls within the allowed range.
    - **Calculate Average:** Calculate the student's average grade.
    - **Display Information:** Display the person's and student's information.
    - **Compare Students:** Compare two students according to their average grades.
    - **Count Students:** Return the total number of student objects.
    - **Add and Remove Students:** Manage the collection of students.
    - **Search Student:** Find a student using their student ID.
- **Requirements:**
    - Use `protected` members in `Person` where appropriate, and keep sensitive implementation details `private`.
    - Initialize base-class members through constructor initialization lists.
    - Use `static` data members and static member functions to track student objects.
    - Implement the copy constructor and copy assignment operator where appropriate.
    - Overload `==` to compare students by student ID.
    - Overload `<` to compare students by average grade.
    - Overload `<<` to display student information.
    - Use a namespace named `University` to organize the classes.
    - Use `std::vector` to manage the collection of students.
    - Ensure that copying a student produces an independent copy of its grades.

### Task 5: Robot Control System

Design a small robot-control system that demonstrates abstract classes, multiple inheritance, polymorphism, and safe resource ownership.

- `Robot` is an abstract base class containing an ID and a name. It declares a pure virtual `operate()` function and has a virtual destructor.
- `Navigator` provides a method for changing and displaying a robot's position.
- `Communicator` provides methods for connecting and disconnecting communication.
- `MobileRobot` inherits from `Robot`, `Navigator`, and `Communicator`.
- `ArmRobot` is a second concrete robot type so that the manager can demonstrate polymorphism.
- `Sensor` stores a sensor type and a collection of integer measurements.
- `RobotManager` stores and manages robots through `std::unique_ptr<Robot>`.

**Requirements:**
1. Use constructor initialization lists and validate IDs and required text values.
2. Override `operate()` in both concrete robot classes.
3. Store robots in `std::vector<std::unique_ptr<Robot>>` and add them with `std::make_unique`.
4. Demonstrate navigation and communication with a `MobileRobot`.
5. Use `std::vector<int>` in `Sensor` so copying a sensor creates independent measurement data without writing manual memory-management functions.
6. Display each robot through the common `Robot` interface.

**Additional challenge:** Add a virtual `display()` function to `Robot` and override it in the derived classes. Compare two robots by their IDs without transferring ownership.

    - Apply the Rule of Five where manual resource management requires it, and explain how the Rule of Zero could simplify the implementation using standard-library containers or smart pointers.
    - Use `final` to prevent further inheritance from one selected class or prevent overriding of one selected virtual function.
    - Organize the system inside a namespace named `Robotics`.
