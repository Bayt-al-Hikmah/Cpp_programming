# Standard Library Containers and Iterators

## Learning Objectives
- Understand the roles of standard-library containers, iterators, and algorithms.
- Choose suitable sequence, associative, unordered, and adaptor containers.
- Traverse containers with iterators and range-based loops.
- Understand vector capacity, reallocation, and iterator/reference invalidation.
## The Standard Library Containers and Iterators

### Introduction
In our previous lectures, we learned how to organize programs using functions, structures, classes, and objects. We also explored inheritance, polymorphism, exception handling, and resource management. These concepts help us design programs that are organized, reusable, and easier to maintain.

However, there is another important question we need to answer when developing real applications: How should we store, organize, search, and manipulate large amounts of data efficiently?

Imagine that we are developing a university management system. We need to store students, search for a particular student, sort students by their grades, count how many students passed an examination, and calculate the average grade.

We could implement all these operations ourselves. We could create dynamic arrays, write searching algorithms, implement sorting algorithms, and build our own data structures.

But this would require a considerable amount of code, and we would have to handle many details ourselves.

C++ provides a collection of reusable components that already solve many of these problems. This collection is called the **Standard Template Library (STL)**.

The STL provides containers for storing data, iterators for traversing that data, algorithms for processing it, and callable objects for customizing operations.

Instead of implementing a dynamic array from scratch, for example, we can use `std::vector`. Instead of writing a sorting algorithm ourselves, we can use `std::sort`. Instead of manually writing a loop for every search operation, we can use algorithms such as `std::find` and `std::find_if`.

### STL Fundamentals
The STL is built around several closely related concepts:
- **Containers:** Store and organize collections of elements.
- **Iterators:** Provide a way to access and traverse elements stored in containers.
- **Algorithms:** Perform operations such as searching, sorting, copying, and counting.
- **Function objects:** Represent callable objects that can be passed to other functions.
- **Allocators:** Define how containers obtain and manage memory for their elements.

To understand how these components work together, let's consider a collection of examination grades. We want to store the grades, display them, search for a particular grade, and sort them.

Without the STL, we might have to write separate code for storage, traversal, searching, and sorting. With the STL, each responsibility can be handled by an appropriate component.
### Containers: Storing Data
A container is an object that stores a collection of other objects.

For example, a `std::vector<int>` stores integers:
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 18, 12, 16, 10};

    cout << "Number of grades: " << grades.size() << '\n';

    return 0;
}
```
The declaration:
```
vector<int> grades;
```
creates a vector whose elements have type `int`.

The vector manages the memory required to store its elements. We do not need to allocate an array manually, calculate its memory size, or write a resizing function.
### Iterators: Accessing Elements
A container stores elements, but we also need a way to access those elements systematically. This is the role of **iterators**.

An iterator behaves somewhat like a pointer: it identifies an element within a container and allows us to move through the collection.

For example:
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 18, 12, 16, 10};

    vector<int>::iterator it = grades.begin();

    cout << *it << '\n';

    return 0;
}
```
Let's examine the important expressions.
```cpp
grades.begin()
```
Returns an iterator referring to the first element of the vector, provided the vector is not empty.
```
*it
```
Dereferences the iterator, giving us access to the element it refers to.
#### `begin()` and `end()`
Most STL containers provide two particularly important functions:
- `begin()` returns an iterator to the first element.
- `end()` returns an iterator representing the position immediately after the last element. 

The position returned by `end()` is not an element. It is a boundary marking the end of the valid range.

Many STL algorithms accept `begin()` and `end()`, because they describes a range of elements to process, the beginning is included, while the ending position is excluded. This is called a **half-open range**.

Half-open ranges make it easy to represent empty collections and calculate the number of elements between two positions. For example, if `begin()` and `end()` are equal, the range is empty.
#### Constant Iterators: `cbegin()` and `cend()`
Sometimes we want to traverse a container without modifying its elements.

C++ provides `cbegin()` and `cend()` for this purpose.
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 18, 12};

    for (auto it = grades.cbegin(); it != grades.cend(); ++it) {
        cout << *it << '\n';
    }

    return 0;
}
```
The expressions:
```cpp
grades.cbegin()
grades.cend()
```
provide constant iterators. We can read the elements through these iterators, but we cannot modify the elements through them.
#### Iterator Categories and Their Capabilities
Not every iterator supports the same operations. For example, an iterator into a vector can move forward and backward and can jump directly to another position. An iterator into a linked list supports moving forward and backward, but it cannot jump directly to the element at index 100.

The STL therefore distinguishes between iterator categories according to the operations they support.
#### Input Iterators
Input iterators are used to read elements while moving forward through a sequence. They are useful when an algorithm needs to consume data sequentially.
#### Output Iterators
Output iterators are used to write values to a destination sequence. They are useful for algorithms that produce results, although the exact operations supported depend on the iterator type.
#### Forward Iterators
Forward iterators can move forward through a sequence and support repeated traversal when the underlying range permits it. They are commonly associated with containers such as `std::forward_list`.
#### Bidirectional Iterators
Bidirectional iterators can move both forward and backward. For example, iterators for `std::list`, `std::set`, and `std::map` support bidirectional traversal.
#### Random-Access Iterators
Random-access iterators support moving directly between positions using arithmetic operations.

For example, vector iterators support operations such as:
```cpp
it + 3
it - 2
it[4]
```
They also support comparing positions and calculating the distance between compatible iterators.

Random-access iterators are particularly useful for algorithms that require efficient access to arbitrary positions.
#### Contiguous Iterators
In modern C++, contiguous iterators provide the additional guarantee that the elements they refer to occupy consecutive memory locations. Pointers and the iterators of `std::vector` are examples of contiguous iterators.

The following table summarizes the main capabilities:

| Iterator category | Main capability                        | Example                     |
| ----------------- | -------------------------------------- | --------------------------- |
| Input             | Read while moving forward              | Input stream iterators      |
| Output            | Write while moving forward             | Output iterator adaptors    |
| Forward           | Repeated forward traversal             | `std::forward_list`         |
| Bidirectional     | Move forward and backward              | `std::list`, `std::map`     |
| Random access     | Jump directly between positions        | `std::vector`, `std::deque` |
| Contiguous        | Random access with consecutive storage | `std::vector`               |

### Using STL Components Together
Now that we understand containers, iterators, and algorithms at a basic level, let's combine them.

Suppose we want to store grades, display them, and search for a particular value.
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades = {14, 18, 12, 16, 10};

    // Display the grades
    for (auto it = grades.begin(); it != grades.end(); ++it) {
        cout << *it << ' ';
    }

    cout << '\n';

    // Search for a grade
    auto result = find(grades.begin(), grades.end(), 16);

    if (result != grades.end()) {
        cout << "Grade found: " << *result << '\n';
    } else {
        cout << "Grade not found\n";
    }

    return 0;
}
```
Let's identify the role of each component.
- `vector<int>` stores the grades.
- `begin()` and `end()` define the range of elements.
- The iterator loop traverses the collection.
- `find()` searches the range for the value `16`.
- The returned iterator identifies the matching element if one is found.

Notice how `find()` does not need to know that the data is stored in a vector. It works with iterators that describe a suitable range.

This is one of the most important design ideas behind the STL: containers manage data, iterators provide access to ranges, and algorithms operate on those ranges.
### Sequence Containers
Sequence containers store elements in a linear sequence. The elements have an order, and that order determines how we traverse them. Depending on the container, we may access elements by index, insert elements at either end, or insert and remove elements at different positions.

C++ provides several sequence containers:
- `std::array`
- `std::vector`
- `std::deque`
- `std::list`
- `std::forward_list`

Although these containers can all store sequences of elements, they do not organize memory or support operations in exactly the same way.
#### Fixed-Size Arrays: `std::array`
In earlier C++ lessons, we learned how to use built-in arrays:
```cpp
int numbers[5] = {10, 20, 30, 40, 50};
```
A built-in array stores a fixed number of elements. Once its size has been determined, it cannot be resized.

C++ provides `std::array` as a standard-library alternative that retains the fixed-size nature of an array while providing a more convenient interface.

To use it, include the `<array>` header.
```cpp
#include <array>
#include <iostream>

using namespace std;

int main() {
    array<int, 5> numbers = {10, 20, 30, 40, 50};

    cout << "First element: " << numbers[0] << '\n';
    cout << "Number of elements: " << numbers.size() << '\n';

    return 0;
}
```
Let's examine the declaration:
```cpp
array<int, 5> numbers;
```
The first template argument, `int`, specifies the element type. The second argument, `5`, specifies the number of elements.

The size is part of the type, so `std::array<int, 5>` and `std::array<int, 10>` are different types.

`std::array` provides useful member functions  to work with it element such as:
- `size()` returns the number of elements.
- `front()` accesses the first element.
- `back()` accesses the last element.
- `at(index)` accesses an element with bounds checking.
- `begin()` and `end()` provide iterators.

For example:
```cpp
cout << numbers.at(2) << '\n';
```
The `at()` function checks whether the requested index is valid and throws `std::out_of_range` if it is not. In contrast, `operator[]` does not perform bounds checking.

A `std::array` is useful when the number of elements is known in advance and should remain fixed, such as storing the seven days of a week or the three coordinates of a point.
#### Dynamic Arrays: `std::vector`
A fixed-size array is not always appropriate. Suppose we are developing a program that records examination results. At the beginning, we do not know how many students will submit their results.

We could allocate a large array and hope that it is sufficient, but this wastes memory when the array is too large and creates problems when it is too small. We could also allocate memory manually and write our own resizing logic, but this introduces additional complexity.

A `std::vector` solves this problem by providing a dynamically sized array.
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> grades;

    grades.push_back(14);
    grades.push_back(18);
    grades.push_back(12);

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << "\nNumber of grades: " << grades.size() << '\n';

    return 0;
}
```
The declaration:
```cpp
vector<int> grades;
```
creates an initially empty vector.

We then add elements using `push_back()`.
```cpp
grades.push_back(14);
```
This adds a new element to the end of the vector. We do not need to specify the final number of elements when creating the vector. It can grow as we add more values.

A vector also supports index-based access:
```cpp
cout << grades[0] << '\n';
cout << grades[1] << '\n';
```
Accessing an existing element by index is efficient because vector elements are stored contiguously in memory.

Vectors provide several operations for managing their contents.
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers = {10, 20, 30};

    numbers.push_back(40);
    numbers.pop_back();

    cout << "First: " << numbers.front() << '\n';
    cout << "Last: " << numbers.back() << '\n';
    cout << "Size: " << numbers.size() << '\n';

    return 0;
}
```
The `push_back()` function adds an element to the end. whereas `pop_back()` removes the last element, the `front()` and `back()` functions access the first and last elements, respectively.

These functions assume that the vector contains at least one element. Calling `front()`, `back()`, or `pop_back()` on an empty vector is not valid.
#### Double-Ended Queues: `std::deque`
Sometimes we need a sequence that supports efficient operations at both ends. For example, imagine a system that maintains a list of recent events. New events are added at the back, but older or higher-priority events might also need to be inserted or removed at the front.

A vector efficiently supports adding elements at the back, but inserting at the front generally requires shifting existing elements.

C++ provides `std::deque`, pronounced _deck_, for situations where operations at both ends are important. The name stands for **double-ended queue**.
```cpp
#include <deque>
#include <iostream>

using namespace std;

int main() {
    deque<int> numbers = {20, 30};

    numbers.push_front(10);
    numbers.push_back(40);

    for (int number : numbers) {
        cout << number << ' ';
    }

    cout << '\n';

    return 0;
}
```
The following operations add elements at either end:
```cpp
numbers.push_front(10);
numbers.push_back(40);
```
Similarly, `pop_front()` and `pop_back()` remove elements from the front and back.

Like a vector, a deque supports efficient index-based access:
```cpp
cout << numbers[2] << '\n';
```
However, a deque does not guarantee that all its elements occupy one contiguous block of memory. Its internal storage is organized differently from a vector.
#### Doubly Linked Lists: `std::list`
Vectors and deques provide efficient index-based access, but inserting or removing elements in the middle can require moving or shifting elements. 

What if our application frequently inserts and removes elements at positions where we already have an iterator?

For example, suppose a task manager maintains a list of tasks, and tasks can be inserted or removed at different positions.

C++ provides `std::list`, which is typically implemented as a doubly linked list. Each element is stored in a node that contains the value and links to the preceding and following nodes.

Let's use a list:
```cpp
#include <iostream>
#include <list>

using namespace std;

int main() {
    list<int> tasks = {10, 20, 30};

    auto it = tasks.begin();
    ++it;

    tasks.insert(it, 15);

    for (int task : tasks) {
        cout << task << ' ';
    }

    cout << '\n';

    return 0;
}
```
The expression:
```cpp
auto it = tasks.begin();
++it;
```
moves the iterator from the first element to the second element, which contains `20`. Then:
```cpp
tasks.insert(it, 15);
```
inserts `15` immediately before that position. In a linked list, insertion and removal at a known position can be performed without shifting all subsequent elements.

However, finding that position may still require traversing the list. For example, this operation is not supported:
```cpp
tasks[2];
```
A `std::list` does not provide index-based access because its elements are not stored as a conventional contiguous array.
#### Singly Linked Lists: `std::forward_list`
A doubly linked list stores links to both the preceding and following nodes. Sometimes, however, we only need to traverse a sequence in the forward direction.

C++ provides `std::forward_list`, a singly linked list. Each node generally stores its value and a link to the next node. Because of that the structure can use less memory per node than a doubly linked list.

Let's examine an example:
```cpp
#include <forward_list>
#include <iostream>

using namespace std;

int main() {
    forward_list<int> numbers = {10, 20, 30};

    numbers.push_front(5);

    auto it = numbers.begin();
    ++it;

    numbers.insert_after(it, 15);

    for (int number : numbers) {
        cout << number << ' ';
    }

    cout << '\n';

    return 0;
}
```
Notice that `std::forward_list` provides `insert_after()` rather than the general `insert()` operation used by `std::list`. Because a forward list only supports forward traversal, it cannot efficiently move backward through its elements.

It also does not provide the same full set of convenience operations as other sequence containers. For example, it does not have a `size()` member function.
#### Comparing Sequence Containers
We have now examined five sequence containers. Although they can all store sequences, their strengths differ.

|Container|Memory organization|Index access|Insertion/removal at ends|Typical use|
|---|---|---|---|---|
|`std::array`|Contiguous, fixed size|Constant time|Size cannot change|Fixed-size collections|
|`std::vector`|Contiguous, dynamic size|Constant time|Efficient at the back|General-purpose dynamic arrays|
|`std::deque`|Multiple memory blocks|Constant time|Efficient at both ends|Sequences modified at both ends|
|`std::list`|Doubly linked nodes|No index access|Efficient at both ends|Frequent edits at known positions|
|`std::forward_list`|Singly linked nodes|No index access|Efficient at the front|Forward-only linked sequences|
### Associative Containers and Container Adaptors
Sequence containers organize elements into a sequence. Sometimes, however, the order in which we insert elements is not the most important property.

Imagine that we are building a dictionary. We want to look up a word and retrieve its definition. Or imagine a university system where each student has a unique identifier. We want to retrieve a student's record using that identifier. Searching through a vector one element at a time may work, but it is not always the most appropriate solution.

C++ provides **associative containers** for organizing data around keys. Some maintain their elements in sorted order, while others use hashing to support efficient average-case lookup.

The STL also provides **container adaptors**, which expose specialized interfaces for particular access patterns.
#### Ordered Sets: `std::set`
A set stores unique values. If we insert the same value more than once, the set retains only one copy of that value.

A `std::set` also keeps its elements sorted according to its ordering rules. By default, values are ordered using the less-than comparison.

Consider the following example:
```cpp
#include <iostream>
#include <set>

using namespace std;

int main() {
    set<int> numbers;

    numbers.insert(30);
    numbers.insert(10);
    numbers.insert(20);
    numbers.insert(10);

    for (int number : numbers) {
        cout << number << ' ';
    }

    cout << '\n';

    return 0;
}
```
**Output:**
```
10 20 30
```
Notice two things.
- First, the output is sorted even though we inserted the values in a different order.
- Second, `10` appears only once, even though we inserted it twice.

These behaviors come from the properties of `std::set`. We can also search for an element:
```cpp
auto it = numbers.find(20);

if (it != numbers.end()) {
    cout << "Number found\n";
}
```
For a typical `std::set` implementation based on a balanced search tree, searching, insertion, and removal have logarithmic complexity.

This makes sets useful when we need to maintain unique values in sorted order and perform efficient searches. However, we cannot directly modify a set element through an iterator. Changing a value could violate the ordering of the container. If a value needs to change, we generally remove the old value and insert the new one.
#### Ordered Sets with Duplicates: `std::multiset`
Suppose we are storing examination grades. Several students may receive the same grade, and we need to preserve all those occurrences while keeping the values sorted. A regular set would discard duplicate values.

A `std::multiset` solves this problem.
```cpp
#include <iostream>
#include <set>

using namespace std;

int main() {
    multiset<int> grades = {15, 12, 18, 15, 12};

    for (int grade : grades) {
        cout << grade << ' ';
    }

    cout << "\nNumber of occurrences of 15: " << grades.count(15) << '\n';

    return 0;
}
```
**Output:**
```
12 12 15 15 18
Number of occurrences of 15: 2
```
The values are sorted, but duplicates are preserved.
#### Key-Value Storage: `std::map`
A set stores individual values. But many applications need to associate one piece of information with another.

Consider a student management system. Each student has an identifier, and we want to retrieve the student's name using that identifier.

We can represent this relationship as:

```
Student ID       Student name
----------       ------------
1001             Ali
1002             Sara
1003             Yacine
```
This is a key-value relationship. A `std::map` stores pairs consisting of a key and a mapped value. The key is used to identify the associated value.

Let's examine an example:
```cpp
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<int, string> students;

    students[1001] = "Ali";
    students[1002] = "Sara";
    students[1003] = "Yacine";

    cout << students[1002] << '\n';

    return 0;
}
```
The declaration:
```cpp
map<int, string> students;
```
creates a map whose keys are integers and whose mapped values are strings.

When we write:
```cpp
students[1002] = "Sara";
```
we associate the key `1002` with the value `"Sara"`. We can then retrieve that value using:
```cpp
cout << students[1002];
```
By default, a map maintains its keys in sorted order. It also requires keys to be unique. Assigning a new value to an existing key replaces the mapped value rather than creating another entry.

One detail is important: using `operator[]` to access a key that does not exist inserts a new entry with a default-initialized mapped value.

For example:
```cpp
cout << students[2000];
```
If the key `2000` is absent empty string get inserted to this key.

If we only want to check whether a key exists, we can use `find()` or `contains()`.
```cpp
if (students.contains(1002)) {
    cout << "Student exists\n";
}
```
The `contains()` member function is available starting in C++20.

For earlier C++ versions, use:
```cpp
if (students.find(1002) != students.end()) {
    cout << "Student exists\n";
}
```
#### Maps with Duplicate Keys: `std::multimap`
Sometimes one key can be associated with several values. For example, one department may contain several employees. If we use the department identifier as the key, multiple employees may share that key.

A regular map cannot store multiple entries with equivalent keys. A `std::multimap` allows this.
```cpp
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    multimap<string, string> employees;

    employees.insert({"Engineering", "Ali"});
    employees.insert({"Engineering", "Sara"});
    employees.insert({"Finance", "Yacine"});

    for (const auto& employee : employees) {
        cout << employee.first << ": "
             << employee.second << '\n';
    }

    return 0;
}
```
The expression `employee.first` accesses the key, while `employee.second` accesses the mapped value.

Unlike `std::map`, `std::multimap` does not provide `operator[]`, because a key can refer to multiple entries.

To find entries associated with a particular key, we can use `equal_range()`:
```cpp
auto [first, last] = employees.equal_range("Engineering");

for (auto it = first; it != last; ++it) {
    cout << it->second << '\n';
}
```
This example uses structured bindings, introduced in C++17, to obtain the beginning and ending iterators of the matching range. The loop then processes all entries whose key is `"Engineering"`.
#### Unordered Containers: `std::unordered_set`
So far, our ordered associative containers have maintained sorted order. But what if we do not need sorted output?

Imagine that we are checking whether a username has already been registered. We only need to know whether the username exists; we do not need all usernames stored alphabetically.

C++ provides unordered associative containers that use **hash tables** instead of maintaining their elements in sorted order.

A `std::unordered_set` stores unique values and uses hashing to organize them.
```cpp
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    unordered_set<string> usernames;

    usernames.insert("ali");
    usernames.insert("sara");
    usernames.insert("yacine");
    usernames.insert("ali");

    cout << "Number of unique usernames: " << usernames.size() << '\n';

    if (usernames.contains("sara")) {
        cout << "Username exists\n";
    }

    return 0;
}
```
As with `std::set`, duplicate values are not stored as separate elements. However, unlike `std::set`, an unordered set does not maintain its elements in sorted order.
#### Unordered Maps: `std::unordered_map`
An unordered map combines key-value storage with hash-based organization. Consider a program that counts how many times each word appears in a sentence. We want to associate each word with an integer representing its frequency.

A `std::unordered_map` is a natural choice.
```cpp
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    string sentence = "cat dog cat bird dog cat";
    unordered_map<string, int> frequency;

    string word;
    istringstream input(sentence);

    while (input >> word) {
        ++frequency[word];
    }

    for (const auto& entry : frequency) {
        cout << entry.first << ": " << entry.second << '\n';
    }

    return 0;
}
```
Let's examine the counting operation:
```
++frequency[word];
```
If the word is not already present, `operator[]` inserts it with a default-initialized integer value of zero. The increment then changes that value to one. If the word already exists, the existing count is incremented.

A `std::unordered_map` is useful for tasks such as counting occurrences, maintaining lookup tables, and associating identifiers with records when sorted keys are not required.
#### Understanding Hash Tables and Hash Functions
To understand unordered containers, we need to understand the basic idea behind a hash table.

A hash function takes a key and produces a hash value. The container uses that value to help determine where the key should be stored.

Conceptually:
```
Key
 |
 v
Hash function
 |
 v
Hash value
 |
 v
Hash table location
```
For example, suppose we insert the username `"ali"`.

The container computes a hash value for the string and uses it to determine which part of its internal table should hold the element.

When we later search for `"ali"`, the container computes the hash again and uses it to locate the relevant area of the table.

However, different keys can produce the same hash value. This situation is called a **hash collision**.

A collision does not mean that the container treats two different keys as equal. The container must still determine whether the actual keys are equivalent.

Standard-library unordered containers handle collisions internally, typically by organizing elements into buckets and comparing keys within the relevant bucket.
### Ordered Versus Unordered Containers

Let's compare the main associative containers.

| Container            | Stores          | Duplicate keys | Ordering        | Typical lookup complexity |
| -------------------- | --------------- | -------------- | --------------- | ------------------------- |
| `std::set`           | Keys            | No             | Sorted          | Logarithmic               |
| `std::multiset`      | Keys            | Yes            | Sorted          | Logarithmic               |
| `std::map`           | Key-value pairs | No             | Sorted by key   | Logarithmic               |
| `std::multimap`      | Key-value pairs | Yes            | Sorted by key   | Logarithmic               |
| `std::unordered_set` | Keys            | No             | No sorted order | Average constant time     |
| `std::unordered_map` | Key-value pairs | No             | No sorted order | Average constant time     |
### Container Adaptors: 
#### `std::stack`
The containers we have examined expose different ways to access their elements. A container adaptor takes an underlying container and exposes a more specialized interface.

For example, a stack follows the **Last In, First Out (LIFO)** principle. The last element added is the first element removed.

C++ provides `std::stack` for this behavior.
```CPP
#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> numbers;

    numbers.push(10);
    numbers.push(20);
    numbers.push(30);

    cout << "Top: " << numbers.top() << '\n';

    numbers.pop();

    cout << "New top: " << numbers.top() << '\n';

    return 0;
}
```
The main operations are:
- `push(value)` adds an element to the top.
- `top()` accesses the top element.
- `pop()` removes the top element.
- `empty()` checks whether the stack is empty.
- `size()` returns the number of elements.
#### `std::queue`
A queue work in the reversed logic, the **First In, First Out (FIFO)**. The first element inserted is the first element removed.

C++ provides `std::queue` for this behavior.
```CPP
#include <iostream>
#include <queue>

using namespace std;

int main() {
    queue<string> customers;

    customers.push("Ali");
    customers.push("Sara");
    customers.push("Yacine");

    cout << "First customer: "
         << customers.front() << '\n';

    customers.pop();

    cout << "Next customer: "
         << customers.front() << '\n';

    return 0;
}
```
The main operations are:
- `push(value)` adds an element to the back.
- `front()` accesses the first element.
- `back()` accesses the last element.
- `pop()` removes the first element.
- `empty()` checks whether the queue is empty.
- `size()` returns the number of elements.
#### `std::priority_queue`
Sometimes, processing elements in insertion order is not appropriate. Imagine a system that schedules tasks according to their priority. A task with a higher priority should be processed before tasks with lower priorities, even if it was inserted later.

C++ provides `std::priority_queue` for this situation. By default, a priority queue places the largest element at the top.
```cpp
#include <iostream>
#include <queue>

using namespace std;

int main() {
    priority_queue<int> priorities;

    priorities.push(20);
    priorities.push(50);
    priorities.push(10);
    priorities.push(40);

    while (!priorities.empty()) {
        cout << priorities.top() << ' ';
        priorities.pop();
    }

    cout << '\n';

    return 0;
}
```
**Output:**
```
50 40 20 10
```
Even though `10` was inserted after some of the other values, it is not removed first. The priority queue maintains the element with the highest priority at the top according to its comparison rules.

Its main operations include:
- `push(value)` inserts an element.
- `top()` accesses the highest-priority element.
- `pop()` removes that element.
- `empty()` checks whether the queue is empty.
- `size()` returns the number of elements.
### Vector Memory Management and Iterator Safety
In our earlier examples, we used `std::vector` as though it were simply an array that grows automatically. That description is useful as a starting point, but to write reliable C++ programs, we need to understand how a vector manages its memory.
#### Understanding Vector Size and Capacity
A vector has two related but different properties:
- **Size:** The number of elements currently stored.
- **Capacity:** The number of elements that can be stored in the vector's current allocated storage without requiring reallocation.

Consider the following example:
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers;

    numbers.reserve(5);

    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    cout << "Size: " << numbers.size() << '\n';
    cout << "Capacity: " << numbers.capacity() << '\n';

    return 0;
}
```
The `reserve(5)` call requests enough capacity to hold at least five elements without reallocation. The vector contains only three elements, so its size is three.

If we try to do
```cpp
numbers[4] = 50;
```
We will get error cause the vector's size is three, even if its capacity is five. Capacity does not make additional elements accessible through `operator[]`.

To create more elements, use an operation such as `push_back()`, `emplace_back()`, or `resize()`.
#### Changing Size with `resize()`
The `resize()` function changes the number of elements in a vector.
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers = {10, 20, 30};

    numbers.resize(5);

    for (int number : numbers) {
        cout << number << ' ';
    }

    cout << "\nSize: " << numbers.size() << '\n';

    return 0;
}
```
When `resize()` increases the size, additional elements are created. For an `int` vector, the new elements are initialized to zero.

If `resize()` decreases the size, elements at the end are removed.

This differs from `reserve()`.
```cpp
numbers.reserve(100);
```
requests additional capacity without increasing the number of elements.
```cpp
numbers.resize(100);
```
changes the vector so that it contains 100 elements.
#### Adding Elements with `push_back()`
The `push_back()` function adds an existing value to the end of a vector.
```cpp
vector<int> numbers;

numbers.push_back(10);

int value = 20;
numbers.push_back(value);
```
If the vector has enough unused capacity, adding an element normally does not require allocating new storage. However, if the vector is already full, it must obtain more storage before it can add another element.
#### Adding Elements with `emplace_back()`
The `emplace_back()` function constructs a new element directly at the end of the vector using the arguments supplied to it.

This can be useful when storing objects that have constructors.

Consider the following class:
```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student {
public:
    string name;
    int age;

    Student(string studentName, int studentAge)
        : name(studentName), age(studentAge) {
        cout << "Constructing " << name << '\n';
    }
};

int main() {
    vector<Student> students;

    students.emplace_back("Ali", 23);

    cout << students[0].name << '\n';

    return 0;
}
```
The expression:
```cpp
students.emplace_back("Ali", 23);
```
passes the constructor arguments directly to the vector, which constructs the `Student` at the end of the vector.

Compare this with:
```cpp
Student student("Ali", 23);
students.push_back(student);
```
In this second version, the `Student` is constructed separately and then copied into the vector.

We could also write:
```
students.push_back(Student("Ali", 23));
```
which constructs a temporary `Student` and passes it to `push_back()`. Modern C++ can move that temporary into the vector, so this version is not necessarily expensive.

The key distinction is that `emplace_back()` constructs the element from the supplied arguments, while `push_back()` accepts an existing element to copy or move.
### Understanding Vector Reallocation
A vector stores its elements in contiguous memory. Eventually, adding elements may exceed the capacity of its current storage.

When that happens, the vector must allocate a larger block of memory and transfer its elements into the new storage. This process is called **reallocation**.

Conceptually, imagine a vector with capacity three, suppose we add another element and the current capacity is insufficient, The vector obtains new storage, the new allocation may have more capacity than strictly required. The exact growth strategy is implementation-dependent.
#### Iterator Invalidation
Reallocation can introduce problems when we work with iterator, Consider the following program:
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers;

    numbers.reserve(2);

    numbers.push_back(10);
    numbers.push_back(20);

    auto it = numbers.begin();

    cout << *it << '\n';

    numbers.push_back(30);

    // Do not use it here if reallocation occurred.

    return 0;
}
```
We reserve capacity for at least two elements and then add two values. At this point, `it` refers to the first element.

When we add `30`, the vector must increase its capacity if its current capacity is only two. If reallocation occurs, the iterator becomes invalid.

Dereferencing or otherwise using an invalidated iterator is not valid C++ behavior, this is not merely a problem with iterators. References and pointers to vector elements can also become invalid when reallocation occurs.
### Iterator and Reference Invalidation Rules
For `std::vector`, the following rules are particularly important.

**When reallocation occurs:**
- All iterators to the vector's elements are invalidated.
- All references to its elements are invalidated.
- All pointers to its elements are invalidated.
- The previous past-the-end iterator is also invalidated.

**When an element is inserted without reallocation:**
- Iterators, pointers, and references before the insertion position remain valid.
- Those at or after the insertion position are invalidated.
- The previous past-the-end iterator is invalidated.

**When elements are erased:**
- Iterators, pointers, and references to erased elements are invalidated.
- Those at or after the erased position are also invalidated, including the previous past-the-end iterator.

These rules explain why storing an iterator and then modifying a vector can be dangerous.

For example:
```cpp
auto it = numbers.begin();

numbers.erase(numbers.begin());

// Do not assume that it remains valid.
```
Even if the vector does not reallocate, the erase operation invalidates iterators at or after the erased position.
#### Avoiding Reallocation with `reserve()`
If we know approximately how many elements we need to store, we can reserve capacity in advance.
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> numbers;

    numbers.reserve(100);

    for (int i = 0; i < 100; ++i) {
        numbers.push_back(i);
    }

    cout << "Size: " << numbers.size() << '\n';
    cout << "Capacity: " << numbers.capacity() << '\n';

    return 0;
}
```
The vector requests enough capacity to hold at least 100 elements before the loop begins.

Consequently, adding the 100 elements does not require reallocation if that capacity request succeeds and no other operation changes the capacity.

However, `reserve()` does not make iterators immune to every form of invalidation. Inserting or erasing elements can still invalidate iterators according to the rules described earlier.

Also, calling `reserve()` unnecessarily can result in excess memory use. It is most useful when we have a reasonable estimate of the required number of elements.
#### Safely Modifying a Vector While Traversing It
One common mistake is erasing elements from a vector while using a loop that assumes its iterators remain valid.

Consider a vector containing values that we want to remove, an unsafe approach would look like this:
```cpp
for (auto it = numbers.begin(); it != numbers.end(); ++it) {
    if (*it < 10) {
        numbers.erase(it);
    }
}
```
This code has a problem: `erase()` invalidates the iterator referring to the erased element, and the loop then attempts to increment that invalid iterator.

A safer approach is to use the iterator returned by `erase()`:
```cpp
for (auto it = numbers.begin(); it != numbers.end();) {
    if (*it < 10) {
        it = numbers.erase(it);
    } else {
        ++it;
    }
}
```
The `erase()` function returns an iterator to the element that follows the erased element, or `end()` if no such element exists. We assign that returned iterator to `it` and do not increment it again during the same iteration.
## Tasks
### Task 1:
Write a C++ program to manage students' examination grades using `std::vector`.

The program should:

1. Ask the user to enter the number of students and their grades.
2. Store the grades in a `std::vector<int>`.
3. Display all grades using iterators.
4. Use `std::sort()` to sort the grades in ascending order.
5. Use `std::find()` to search for a grade entered by the user.
6. Display the minimum, maximum, and number of grades stored.

**Hint:** Use `std::vector`, `std::sort`, `std::find`, `std::min_element`, and `std::max_element`.

### Task 2:

Write a C++ program that manages a collection of unique product identification numbers.

The program should:

1. Store product IDs in a `std::set<int>`.
2. Allow the user to insert new IDs.
3. Prevent duplicate IDs from being stored.
4. Display all IDs in ascending order.
5. Check whether a specific ID exists using `find()`.
6. Display the total number of unique IDs.

**Additional challenge:** Modify the program to use `std::unordered_set<int>` instead. Compare the behavior of the two containers.

**Hint:** Use `std::set`, `std::unordered_set`, `insert()`, `find()`, `end()`, and `size()`.


### Task 3:

Write a C++ program to manage student records using a `std::map<int, std::string>`.

Each student has a unique identification number and a name.

The program should:

1. Allow the user to add student IDs and names.
2. Store each student's name using their ID as the key.
3. Search for a student using their ID.
4. Display all students in ascending order of their IDs.
5. Allow the user to update a student's name.
6. Display an appropriate message when the requested student does not exist.

**Additional challenge:** Use `std::unordered_map<int, std::string>` and compare it with `std::map`.

**Hint:** Use `insert()`, `find()`, `end()`, and `operator[]`. Remember that `operator[]` inserts a new entry if the key does not exist.

### Task 4:

Write a C++ program that simulates a task management system using STL container adaptors.

The program should:

1. Use `std::queue<std::string>` to manage tasks in the order they are received.
2. Allow the user to add new tasks.
3. Process tasks in First In, First Out (FIFO) order.
4. Use `std::stack<std::string>` to store recently completed tasks.
5. Display the most recently completed task.
6. Handle attempts to process or access tasks when the corresponding container is empty.

**Additional challenge:** Use `std::priority_queue<int>` to process numerical task priorities, with the highest priority processed first.

**Hint:** Use `push()`, `pop()`, `front()`, `top()`, `empty()`, and `size()`.

### Task 5:
Write a C++ program to investigate how `std::vector` manages memory when elements are added or removed.

The program should:

1. Create an empty `std::vector<int>` and display its initial size and capacity.
2. Use `reserve(5)` to request capacity for at least five elements.
3. Add five integers using `push_back()` and display the size and capacity after each insertion.
4. Create an iterator pointing to the first element and display its value.
5. Add more elements and observe how the vector's capacity changes.
6. Explain why an iterator may become invalid when reallocation occurs.
7. Use `resize()` to change the number of elements and explain the difference between `size()` and `capacity()`.
8. Remove all elements smaller than a value entered by the user without using invalidated iterators.

**Additional challenge:** Repeat the experiment using `emplace_back()` and compare it with `push_back()`.

**Hint:** Use `size()`, `capacity()`, `reserve()`, `resize()`, `push_back()`, `emplace_back()`, and `erase()`.
