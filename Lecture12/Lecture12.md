# Concurrency and Multithreading

## Learning Objectives
- Create and manage threads and understand why their lifetimes matter.
- Recognize data races and protect shared state with mutexes.
- Coordinate threads using condition variables.
- Use `std::async`, `std::future`, and `std::promise` to exchange results.
## Concurrency & Multithreading
### Introduction
Many programs execute a sequence of operations: read some data, process it, and display or save the result. For simple tasks, performing these operations one after another is often sufficient.

However, consider an application that downloads several files, processes a collection of images, or performs multiple independent calculations. Waiting for each operation to finish before starting the next may prevent the program from making efficient use of available resources.

In such situations, we can organize the program so that multiple tasks make progress during overlapping periods.

**Concurrency** describes the organization of a program in which multiple tasks can make progress over overlapping periods.

**Multithreading** is one way to achieve concurrency. A _thread_ represents a separate sequence of execution within a process.

On a system with multiple processing cores, multiple threads may execute simultaneously. On a system with a single core, the operating system can switch between threads, allowing them to make progress at different times.

This distinction introduces two important concepts:
- **Concurrency** allows multiple tasks to make progress over overlapping periods.
- **Parallelism** involves executing multiple operations at the same time.

Concurrency does not necessarily require parallel execution, although a concurrent program can take advantage of parallelism when suitable resources are available.

C++ provides mechanisms for creating threads, coordinating their execution, protecting shared data, and communicating results between tasks.

However, introducing multiple threads also introduces new challenges. Two threads may attempt to modify the same value, one thread may need to wait for another, or a task may produce a result that another part of the program needs.
### Threading Basics

#### Creating a Thread with `std::thread`
C++ provides the `std::thread` class through the `<thread>` header.

A thread can execute a function independently of the thread that created it. This allows the program to begin a task without requiring the calling thread to execute that task directly.

Consider the following example:
```cpp
#include <iostream>
#include <thread>

void calculate() {
    std::cout << "Calculation started.\n";

    int result = 10 * 20;

    std::cout << "Result: " << result << '\n';
}

int main() {
    std::thread worker(calculate);

    worker.join();

    std::cout << "Main function finished.\n";

    return 0;
}
```
The important statement is:
```cpp
std::thread worker(calculate);
```
This creates a new thread that begins executing `calculate()`.

Meanwhile, the original thread continues executing `main()`. The operating system determines how the threads are scheduled, so we should not assume exactly when the worker begins executing relative to other operations in the main thread.

The next statement is:
```cpp
worker.join();
```
This makes the calling thread wait until the worker thread has completed.

In this example, the main thread cannot proceed beyond `join()` until `calculate()` finishes. Consequently, the message `"Main function finished."` is displayed after the worker has completed its calculation and output.

The general pattern is straightforward: create a thread, allow it to perform its work, and synchronize with it when its completion matters.
#### Managing the Thread's Lifetime
Creating a thread also creates a responsibility: we must manage its lifetime correctly.

Consider the following statement:
```cpp
std::thread worker(calculate);
```
The `worker` object represents the newly created thread of execution. If the object is destroyed while it is still joinable, C++ calls `std::terminate()`.

A joinable thread is one whose thread object still represents a thread that has not been joined or detached. For a straightforward worker thread, the usual approach is:
```cpp
worker.join();
```
Alternatively, we can write:
```cpp
worker.detach();
```
Detaching separates the thread's execution from its thread object. The thread can continue running independently, without another thread object waiting for it.

However, detaching requires particular care. A detached thread may continue executing after the function that created it has returned. If it accesses local variables or other resources that have already been destroyed, the program may exhibit undefined behavior.

We must also ensure that a thread is joinable before calling `join()`, and we must not attempt to join the same thread more than once.
#### Passing Arguments to a Thread
A thread can execute a function that accepts arguments, just as an ordinary function does.

Suppose we want a worker to process an order using its identifier and total amount.
```cpp
#include <iostream>
#include <thread>

void processOrder(int orderId, double amount) {
    std::cout << "Order ID: " << orderId << '\n';
    std::cout << "Order amount: " << amount << '\n';
}

int main() {
    std::thread worker(processOrder, 101, 249.99);

    worker.join();

    return 0;
}
```
The statement:
```cpp
std::thread worker(processOrder, 101, 249.99);
```
starts a thread that invokes `processOrder()` with the supplied arguments.

This is useful when a worker must process a particular record, perform a calculation using specific parameters, or execute an operation configured with particular values.

By default, `std::thread` stores its arguments by value after applying the appropriate decay and forwarding rules. This means that passing a variable does not automatically pass a reference to the original object.

Suppose we instead want a thread to modify an existing integer.
```cpp
#include <functional>
#include <iostream>
#include <thread>

void increase(int& value) {
    ++value;
}

int main() {
    int number = 10;

    std::thread worker(increase, std::ref(number));

    worker.join();

    std::cout << number << '\n';

    return 0;
}
```
The output is:
```
11
```
The expression:
```cpp
std::ref(number)
```
allows the thread to pass a reference to the original integer rather than an independent copy.

However, passing a reference creates an additional responsibility: **the referenced object must remain alive for the duration of its use**.

If multiple threads access that object, we must also ensure that their accesses are safe. We will return to this issue when discussing data races.
#### Using a Lambda as a Thread Function
Sometimes, creating a separate named function for a small task is unnecessary. A lambda allows us to define the work directly where the thread is created.
```cpp
#include <iostream>
#include <thread>

int main() {
    std::thread worker([] {
        std::cout << "Worker thread is running.\n";
    });

    worker.join();

    std::cout << "Worker thread completed.\n";

    return 0;
}
```
The expression:
```cpp
[] {
    std::cout << "Worker thread is running.\n";
}
```
defines the work performed by the new thread. Because the capture list is empty, the lambda does not capture local variables from its surrounding scope.

A lambda can also capture values or references when the task needs access to existing data. However, reference captures must be used carefully: every referenced object must remain alive until the thread finishes using it.

### Data Races and Synchronization
So far, our examples have involved tasks that perform their work independently. The situation becomes more complicated when multiple threads access the same data.

Suppose two threads need to increment a shared counter:
```cpp
int counter = 0;
```
Each thread repeatedly executes:
```cpp
++counter;
```
We might expect the final value to equal the total number of increments. However, incrementing an ordinary integer involves reading its current value, calculating the next value, and storing the result. Without appropriate synchronization, two threads can interfere with one another.

For example, both threads might read the same initial value before either has stored its update. One update can then overwrite the other.

This is a **data race** when conflicting accesses to the same memory location occur without the synchronization required by the C++ memory model, and at least one access modifies the memory.

In C++, a data race results in **undefined behavior**. The program is not guaranteed to produce any particular result. To prevent data races, we need a mechanism that coordinates access to shared data.

#### Protecting Shared Data with `std::mutex`
A **mutex**, short for _mutual exclusion_, provides a way to restrict access to a shared resource so that only one thread at a time holds its lock. C++ provides `std::mutex` through the `<mutex>` header.

Consider two threads that each perform 100,000 increments. Instead of modifying the shared counter during every iteration, each thread can calculate a local count and then add it to the shared counter under a lock.
```cpp
#include <iostream>
#include <mutex>
#include <thread>

int main() {
    int counter = 0;
    std::mutex counterMutex;

    auto increment = [&] {
        int localCount = 0;

        for (int i = 0; i < 100000; ++i) {
            ++localCount;
        }

        std::lock_guard<std::mutex> lock(counterMutex);
        counter += localCount;
    };

    std::thread first(increment);
    std::thread second(increment);

    first.join();
    second.join();

    std::cout << "Final counter: " << counter << '\n';

    return 0;
}
```
The program declares a shared counter and its associated mutex:
```cpp
int counter = 0;
std::mutex counterMutex;
```
Each thread first calculates its own local count:
```cpp
int localCount = 0;

for (int i = 0; i < 100000; ++i) {
    ++localCount;
}
```
The variable `localCount` belongs to the execution of the lambda, so each thread has its own copy. The two loops can therefore execute independently without modifying the same counter.

After completing the local calculation, each thread updates the shared counter:
```cpp
std::lock_guard<std::mutex> lock(counterMutex);
counter += localCount;
```
The `lock_guard` acquires the mutex, preventing another thread from simultaneously entering a critical section protected by that same mutex. One thread acquires the lock and updates the counter. The other must wait until the first releases it.

Because the guard is destroyed when execution leaves its scope, the mutex is released automatically. Both threads can perform their local calculations concurrently, while the final updates are protected.

The result is:
```cpp
Final counter: 200000
```
This example also illustrates an important performance consideration: **we should protect shared data without unnecessarily restricting independent work**.

If the mutex were acquired on every iteration, the threads would spend much more time contending for the lock. By performing local work first, we keep the critical section small.
#### Understanding `std::lock_guard`
We could lock and unlock the mutex manually:
```cpp
counterMutex.lock();

counter += localCount;

counterMutex.unlock();
```
However, manual locking can be error-prone. If an exception or an early return occurs between the two calls, the mutex may remain locked.

C++ provides `std::lock_guard` to manage mutex ownership automatically.
```cpp
std::lock_guard<std::mutex> lock(mutexObject);
```
When the guard is constructed, it acquires the mutex. When the guard is destroyed, it releases the mutex.

This follows the **Resource Acquisition Is Initialization (RAII)** principle: an object's lifetime is used to manage the acquisition and release of a resource.

The scope of the guard defines the critical section: the portion of the program executed while the mutex remains locked.

For example:
```cpp
{
    std::lock_guard<std::mutex> lock(counterMutex);
    counter += localCount;
}
```
When execution leaves this block, the guard is destroyed and the mutex is released.

### Thread Synchronization with `std::condition_variable`
A mutex allows threads to coordinate access to shared data, but it does not directly solve every synchronization problem.

Suppose one thread prepares a report while another thread must wait until the report is ready before displaying it.

The second thread could repeatedly check a flag:
```cpp
while (!reportReady) {
    // Keep checking.
}
```
This approach is called **busy waiting**. The thread repeatedly checks the condition even when nothing has changed. Depending on the situation, this can waste processing time that could be used for other work.

A better solution is to allow the thread to wait without continuously checking the condition and resume when another thread signals that the shared state may have changed. C++ provides `std::condition_variable` for this purpose.

A condition variable allows a thread to wait for a condition associated with shared state. Another thread can notify waiting threads after changing that state.
#### Waiting for a Condition
Let's return to our previous example consider an application in which a worker must wait until a report is ready.
```cpp
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex reportMutex;
std::condition_variable reportCondition;

bool reportReady = false;

void worker() {
    std::unique_lock<std::mutex> lock(reportMutex);

    reportCondition.wait(lock, [] {
        return reportReady;
    });

    std::cout << "The report is ready.\n";
}

int main() {
    std::thread consumer(worker);

    {
        std::lock_guard<std::mutex> lock(reportMutex);
        reportReady = true;
    }

    reportCondition.notify_one();

    consumer.join();

    return 0;
}
```
First, we declare a mutex and a condition variable:
```cpp
std::mutex reportMutex;
std::condition_variable reportCondition;
```
The shared state is represented by:
```cpp
bool reportReady = false;
```
The worker acquires the mutex using:
```cpp
std::unique_lock<std::mutex> lock(reportMutex);
```
We use `std::unique_lock` because the condition variable's waiting operation must be able to release the mutex while the thread is blocked and reacquire it before continuing.

The worker then waits:
```cpp
reportCondition.wait(lock, [] {
    return reportReady;
});
```
The lambda is a **predicate**: it describes the condition that must be true before the worker can proceed. If the predicate evaluates to `false`, the waiting operation releases the mutex and blocks the thread. This allows another thread to acquire the mutex and change the shared state.

When the thread wakes, it reacquires the mutex and checks the predicate again. It proceeds only when the predicate evaluates to `true`.

Meanwhile, the main thread updates the shared state under the same mutex:
```cpp
{
    std::lock_guard<std::mutex> lock(reportMutex);
    reportReady = true;
}
```
After the mutex is released, the main thread notifies one waiting thread:
```cpp
reportCondition.notify_one();
```
The worker can then resume, check the predicate, and continue because `reportReady` is true.
#### Why Use a Predicate?
It may seem sufficient to write:
```cpp
reportCondition.wait(lock);
```
However, condition variables can experience **spurious wakeups**: a waiting thread may resume even though the condition it needs has not become true.

There is also a timing issue. A notification is not a persistent record that a condition has been satisfied. If the shared state becomes ready before the consumer begins waiting, the consumer may have no notification left to receive.

The predicate-based form handles both situations:
```cpp
reportCondition.wait(lock, [] {
    return reportReady;
});
```
Conceptually, it behaves like a loop that keeps checking the condition until it becomes true.

If `reportReady` is already true when the worker reaches the wait, it does not need to block. Otherwise, it waits and checks the condition again when it resumes.

This highlights an essential principle: **A notification tells waiting threads that the state may have changed. The shared state determines whether they can proceed.**
#### `notify_one()` and `notify_all()`
C++ provides two commonly used notification operations:
```cpp
reportCondition.notify_one();
```
and:
```cpp
reportCondition.notify_all();
```
- `notify_one()` wakes one waiting thread, if any are waiting.
- `notify_all()` wakes all waiting threads.

The appropriate operation depends on the application's design. If one new item becomes available and only one consumer should process it, notifying one thread may be sufficient. If a state change allows several waiting threads to proceed, notifying all may be appropriate.

Waking a thread does not automatically grant it access to shared data. The thread must still reacquire its mutex and check its predicate.

### Asynchronous Tasks:
#### Introducing Asynchronous Execution
Threads provide a way to execute work concurrently, but we often need more than the ability to start another sequence of execution.

Suppose a program launches a calculation, continues performing other work, and later needs the result.

We could create a thread manually and use shared variables, mutexes, and condition variables to communicate that result. However, C++ provides abstractions that make many such tasks easier to express.

The `<future>` header provides several related components:

|Component|Main purpose|
|---|---|
|`std::async`|Launches or schedules a callable task and provides access to its result.|
|`std::future`|Represents access to a result that may become available later.|
|`std::promise`|Allows a program to explicitly supply a value or exception to an associated future.|

These components work together, but they serve different purposes.

#### Running a Task with `std::async`
the previous example, we saw how `std::thread` allows us to execute a function concurrently with the main thread. However, when a function produces a result, we also need a way to retrieve that result safely.

C++ provides `std::async` to simplify this process. It allows us to launch a function asynchronously and obtain its return value through a `std::future`.

Suppose we want to calculate the square of a number:
```cpp
#include <future>
#include <iostream>

int calculateSquare(int value) {
    return value * value;
}

int main() {
    std::future<int> result = std::async(
        std::launch::async,
        calculateSquare,
        12
    );

    std::cout << "The calculation has been requested.\n";
    std::cout << "Square: " << result.get() << '\n';

    return 0;
}
```
The task is requested through:
```cpp
std::async(
    std::launch::async,
    calculateSquare,
    12
);
```
The function receives three arguments:
- `std::launch::async` requests that the function execute asynchronously.
- `calculateSquare` specifies the function to execute.
- `12` is the argument passed to that function.

Consequently, the program requests execution of `calculateSquare(12)` without requiring us to create and manage a `std::thread` explicitly.

The result is represented by:
```cpp
std::future<int> result;
```
The type `std::future<int>` tells us that the task produces a result of type `int`.

A future represents a value that may not be available immediately. It provides a mechanism for accessing that value once the associated operation has completed.

After launching the task, the main thread can continue executing other code:
```cpp
std::cout << "The calculation has been requested.\n";
```

When we need the result, we call:
```cpp
result.get()
```
If the result is not ready, `get()` waits for it. When the operation completes, `get()` retrieves the value.
#### Understanding the Launch Policy
When using `std::async`, we can specify **how the task should be executed** through a launch policy.

In the previous example, we used:
```cpp
std::async(
    std::launch::async,
    calculateSquare,
    12
);
```
The policy `std::launch::async` requests that the function execute asynchronously, allowing it to run concurrently with the calling thread.

However, the launch policy is optional. Consider the following call:
```cpp
std::async(calculateSquare, 12);
```
Without an explicit launch policy, the implementation may choose between two execution strategies: **asynchronous execution** and **deferred execution**.


**Asynchronous execution** With `std::launch::async`, the function is invoked as part of asynchronous execution. The implementation starts the associated execution, allowing the task to progress independently of the calling thread.

**Deferred execution** With `std::launch::deferred`, the function is not executed immediately. Instead, its execution is deferred until the program requests the result through an operation such as `get()` or `wait()`.
```cpp
std::future<int> result = std::async(
    std::launch::deferred,
    calculateSquare,
    12
);

std::cout << "Before retrieving the result.\n";

std::cout << result.get() << '\n';
```
Here, `calculateSquare(12)` is executed when `result.get()` is called. The function runs in the thread that performs the waiting operation, which in this example is the main thread.

Consequently, deferred execution does not provide the same opportunity for concurrent progress as asynchronous execution.
#### Understanding `std::future::get()` and `wait()`
When a task executes asynchronously, the calling thread may need to determine whether its result is ready or retrieve the result itself. A `std::future` provides two operations for these purposes: `wait()` and `get()`.

Consider the following calls:
```cpp
result.wait();
```
and:
```cpp
result.get();
```
Although both operations can cause the calling thread to wait, they serve different purposes.
#### Waiting for completion
The `wait()` operation blocks the calling thread until the future's shared state becomes ready.
```cpp
result.wait();
```
It does not retrieve the result. Instead, it allows the program to synchronize with the completion of the task before continuing.

This is useful when we need to ensure that an operation has completed but do not yet need its return value.

#### Retrieving the result
The `get()` operation waits for the result if necessary and then retrieves it.
```cpp
int value = result.get();
```

If the task has already completed, the result can be retrieved immediately. Otherwise, the calling thread waits until the result becomes available.

Unlike `wait()`, calling `get()` consumes the future's shared state. For a `std::future`, the result can be retrieved only once. Afterward, the future no longer has a valid shared state, so another call to `get()` is invalid.

#### Handling exceptions
An asynchronous task can fail just like an ordinary function. For example, the function might throw an exception while performing a calculation.

When a task launched with `std::async` throws an exception, the exception is stored in the associated shared state. When `get()` is called, the exception is rethrown in the thread that calls it.

This means that exception handling can be performed where the result is retrieved:
```cpp
try {
    int value = result.get();
    std::cout << "Result: " << value << '\n';
}
catch (const std::exception& error) {
    std::cerr << "Task failed: " << error.what() << '\n';
}
```

Because `get()` may rethrow an exception originating in the task, retrieving a result is also an important point for handling task failures.

The distinction is straightforward: use `wait()` to wait for completion without retrieving the result, and use `get()` when you need the result itself.
### Passing Data to an Asynchronous Task
So far, our examples have passed individual values to asynchronous functions. In practice, tasks often need to process larger objects, such as vectors, matrices, or collections of sensor measurements.

Consider a function that calculates the sum of a collection of integers:
```cpp
#include <future>
#include <functional>
#include <iostream>
#include <vector>

long long calculateTotal(const std::vector<int>& values) {
    long long total = 0;

    for (int value : values) {
        total += value;
    }

    return total;
}

int main() {
    std::vector<int> values = {10, 20, 30, 40, 50};

    std::future<long long> result = std::async(
        std::launch::async,
        calculateTotal,
        std::cref(values)
    );

    std::cout << "Other work can be performed here.\n";

    std::cout << "Total: " << result.get() << '\n';

    return 0;
}
```
The function calculates the sum of the vector's elements and returns it as a `long long`. The interesting part is how we pass the vector to the asynchronous task.

Notice that the function accepts its parameter as a constant reference:
```cpp
long long calculateTotal(const std::vector<int>& values)
```
The `const` qualifier indicates that the function reads the vector without modifying its elements.

When using `std::async`, function arguments are normally stored by value for the eventual invocation. Passing the vector directly would therefore generally involve copying it into the asynchronous operation.

For a large collection, that copy could introduce unnecessary memory and processing costs.

Instead, we pass:
```cpp
std::cref(values)
```
The function `std::cref()` creates a `std::reference_wrapper` that refers to the original object. This allows the asynchronous invocation to pass the original vector to the function by reference rather than copying the entire collection.

#### Managing object lifetime and shared data
Passing a reference avoids copying the vector, but it introduces an important responsibility: **the original object must remain valid for as long as the task accesses it.**

In our example, the vector is created in `main()` and remains alive while the task executes. The call to `result.get()` ensures that the task has completed before `main()` returns. However, the lifetime of the vector alone is not enough. We must also consider concurrent access.

The asynchronous function reads the vector's elements. If another thread modifies those elements concurrently without appropriate synchronization, a data race may occur. Therefore, while the task is reading the vector, other threads must not modify its elements in a conflicting manner.


### Exchanging Results Explicitly with std::promise
In the previous examples, we used `std::async` to execute a function and obtain its return value through a `std::future`.

This approach works well when the result naturally comes from a function's return value. However, sometimes the code that produces a result is organized separately from the code that consumes it. In such cases, we need a way to communicate the result explicitly.

C++ provides `std::promise` for this purpose. A promise and a future work together through a shared state. The **producer** uses the promise to supply a value or an exception, while the **consumer** uses the associated future to wait for and retrieve that result.

#### Creating a Promise and Future
Consider a worker thread that performs a calculation and sends its result to the main thread.
```cpp
#include <future>
#include <iostream>
#include <thread>
#include <utility>

int main() {
    std::promise<int> promise;

    std::future<int> result = promise.get_future();

    std::thread worker(
        [p = std::move(promise)]() mutable {
            int calculatedValue = 6 * 7;

            p.set_value(calculatedValue);
        }
    );

    std::cout << "Waiting for the result...\n";

    std::cout << "Result: " << result.get() << '\n';

    worker.join();

    return 0;
}
```
We begin by creating a promise:
```cpp
std::promise<int> promise;
```
The type parameter `int` specifies the type of value that the promise will supply, at this point, the promise exists, but no result has been provided.

Next, we obtain the future associated with the promise:
```cpp
std::future<int> result = promise.get_future();
```
The call to `get_future()` provides access to the shared state through which the result will be communicated. The main thread can now use `result` to retrieve the value once the producer supplies it.

We then create a worker thread:
```cpp
std::thread worker(
    [p = std::move(promise)]() mutable {
        int calculatedValue = 6 * 7;

        p.set_value(calculatedValue);
    }
);
```
There are two important details in this lambda expression.

First, the capture:
```cpp
[p = std::move(promise)]
```
moves the promise into the lambda object. The worker therefore owns the promise it will use to communicate the result. Moving is necessary because `std::promise` is movable but not copyable.

Second, the keyword mutable allows the lambda to call non-constant member functions on its captured promise. In this example, the worker needs to call `set_value()`.

Inside the worker, the calculation is performed:
```cpp
int calculatedValue = 6 * 7;
```
The worker then supplies the result through the promise:
```cpp
p.set_value(calculatedValue);
```
This operation stores the value in the promise's shared state and makes that state ready, allowing the associated future to access the result.

Meanwhile, the main thread executes:
```cpp
std::cout << "Waiting for the result...\n";

std::cout << "Result: " << result.get() << '\n';
```
When `get()` is called, the main thread waits if the shared state is not yet ready. Once the worker supplies the value, `get()` retrieves it.

The program produces:
```
Waiting for the result...
Result: 42
```
The worker's execution may begin before or after the first message is printed. However, the future ensures that the main thread cannot retrieve the result until it becomes available.

Finally, we call:
```cpp
worker.join();
```
This ensures that the worker thread has finished before `main()` returns. In this particular example, `result.get()` already waits for the worker to supply its result, but `join()` serves a separate purpose: it ensures that the thread has terminated and allows its resources to be properly reclaimed.
#### Supplying an Exception
A producer does not always complete its operation successfully. A calculation might fail, a file might be unavailable, or an external operation might report an error.

A promise can communicate an exception through the same shared state used to communicate a normal value.

Consider the following code:
```cpp
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>

int main() {
    std::promise<int> promise;
    std::future<int> result = promise.get_future();

    try {
        throw std::runtime_error("Calculation failed.");
    }
    catch (...) {
        promise.set_exception(std::current_exception());
    }

    try {
        std::cout << result.get() << '\n';
    }
    catch (const std::exception& error) {
        std::cerr << "Task failed: " << error.what() << '\n';
    }

    return 0;
}
```
Here, the producer catches an exception and transfers it to the promise:
```cpp
promise.set_exception(std::current_exception());
```
The function `std::current_exception()` obtains a pointer to the currently handled exception, allowing it to be stored in the shared state.

When the consumer calls:
```cpp
result.get();
```
the stored exception is rethrown in the consumer's thread. The consumer can then handle the failure using an ordinary try/catch block.

#### Important Rules for Using std::promise
A promise must be fulfilled only once. It can supply either a value or an exception, but it cannot successfully supply both.

For example:
```cpp
promise.set_value(42);
```
fulfills the promise with a value. A subsequent attempt to call `set_value()` or `set_exception()` on the same promise will fail by throwing `std::future_error`.

There is another important case: what happens if the producer disappears without supplying a result?

Suppose a promise is destroyed while its shared state is still waiting for a value or exception. The shared state is then made ready with a `std::future_error` indicating a broken promise. Consequently, a consumer waiting on the associated future will not remain blocked indefinitely solely because the producer failed to fulfill the promise.

This behavior helps prevent consumers from waiting forever when a producer fails to complete its responsibility.

## Tasks

### Task 1: Parallel Sum

Write a program that sums a large vector of integers using four worker threads.

1. Create and fill a vector with integer values.
2. Divide the index range into four non-overlapping parts.
3. Let each thread calculate one partial sum and store it in a separate result slot.
4. Join every thread before combining and displaying the partial sums.
5. Compare the parallel result with a sequential sum.

**Requirements:** Do not let multiple threads write to the same result slot. Handle vectors whose size is not evenly divisible by four.

### Task 2: Thread-Safe Counter

Create a `Counter` class that stores an integer value and provides an `increment()` operation.

1. Protect the counter with a `std::mutex`.
2. Start several threads, each of which increments the counter many times.
3. Join all threads and display the final value.
4. Explain why the counter must be protected and why `std::lock_guard` is preferable to manually calling `lock()` and `unlock()`.

### Task 3: Wait for a Result

Create one producer thread and one consumer thread that exchange a single integer.

1. Share a `std::mutex`, a `std::condition_variable`, an integer value, and a Boolean flag.
2. The producer stores the integer while holding the mutex, updates the flag, and notifies the consumer.
3. The consumer waits with a predicate that checks the flag, then reads the value while holding the mutex.
4. Join both threads and display the received value.
5. Explain why the consumer must use a predicate instead of assuming every notification means the condition is true.

**Hint:** Include `<condition_variable>`, `<mutex>`, and `<thread>`. Keep all shared variables alive until both threads have finished.

