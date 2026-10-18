## Objectives :
- Learn About Comparison Operators
- Learn About Logical Operator
- Working with Bitwise Operator
- Learn Control Flow
- Learn About Loops

## Comparison Operators
C++ provides comparison operators to compare two values and determine the relationship between them.

The result of a comparison is a boolean (`bool`) value:
- `true` represented as `1` when printed as a normal boolean value.
- `false` represented as `0` when printed as a normal boolean value.
    

Comparison operators are commonly used in conditions, such as `if`, `while`, and `for` statements.
### Comparison Operators
- **`>` (Greater than):** Checks if the left operand is greater than the right operand.
- **`<` (Less than):** Checks if the left operand is less than the right operand.
- **`==` (Equal to):** Checks if both operands are equal.
- **`!=` (Not equal to):** Checks if the operands are different.
- **`>=` (Greater than or equal to):** Checks if the left operand is greater than or equal to the right operand.
- **`<=` (Less than or equal to):** Checks if the left operand is less than or equal to the right operand.
#### Example
```cpp
#include <iostream>
using namespace std;

int main() {

    int A = 5;
    int B = 6;

    cout << "Is B greater than A: " << (B > A) << endl;
    cout << "Is A less than B: " << (A < B) << endl;
    cout << "Is A equal to B: " << (A == B) << endl;
    cout << "Is A not equal to B: " << (A != B) << endl;
    cout << "Is B greater than or equal to A: " << (B >= A) << endl;
    cout << "Is A less than or equal to B: " << (A <= B) << endl;

    return 0;
}
```
## Logical Operators
Sometimes a program needs to check more than one condition at the same time. Imagine we want to check whether a number is between `1` and `10`.

We don't just need to know whether the number is greater than `1`. We also need to know whether it is less than `10`.

We can combine these conditions using logical operators. The result of a logical operation is a boolean (`bool`) value: `true` or `false`.

### `&&` Logical AND
The `&&` operator means "and". it returns `true` only when **all conditions are true**.    
For example
```cpp
B > A && B < 10
```
This asks two questions:
1. Is `B` greater than `A`?
2. Is `B` less than `10`?

The entire expression is true only when both answers are yes.

| Condition A | Condition B | `A && B` |
| ----------- | ----------- | -------- |
| `false`     | `false`     | `false`  |
| `false`     | `true`      | `false`  |
| `true`      | `false`     | `false`  |
| `true`      | `true`      | `true`   |

### `||` Logical OR
The `||` operator means **"or"**. Unlike `&&`, we don't need every condition to be true. The expression becomes true as long as **at least one condition is true**, It returns `false` only when **all conditions are false**.

| Condition A | Condition B | `A \|\| B` |
| ----------- | ----------- | ---------- |
| `false`     | `false`     | `false`    |
| `false`     | `true`      | `true`     |
| `true`      | `false`     | `true`     |
| `true`      | `true`      | `true`     |
Example:
```cpp
A < B || A > 0
```
This is true if A is less than B OR A is greater than 0.
### `!` Logical NOT
The `!` operator does something slightly different. Instead of combining conditions, it reverses the result of a condition.
```
!true  → false
!false → true
```
For example:
```cpp
int A = 5;
int B = 6;

cout << !(A == B);
```
`A == B` is false because `5` is not equal to `6`.
Applying `!` reverses that result:
```
!(false) → true
```
### Short-Circuit Evaluation
There is one more behavior we need to understand when working with logical operators: short-circuit evaluation.

When C++ evaluates an expression using `&&` or `||`, it does not always evaluate every condition.

Instead, it stops as soon as it already knows what the final result must be.
### Short-Circuiting with `&&`
Remember that:
```
false && anything
```
must always be `false`.

So if C++ evaluates the first condition and finds that it is false, there is no reason to evaluate the second condition.
For example:

```cpp
if (A > 10 && B > 5) {
    // ...
}
```
If `A > 10` is false, C++ already knows that the whole expression must be false.

Therefore:
```
B > 5
```
is never evaluated.

### Short-Circuiting with `||`
The same idea works in the opposite direction with `||`.

Remember:
```
true || anything
```
must always be `true`.

Therefore, if the first condition is already true, C++ does not need to evaluate the second condition.

For example:
```cpp
if (age > 18 || checkSomething()) {
    // ...
}
```
If:
```
age > 18
```
is already true, `checkSomething()` is not called.
## Bitwise Operators
Computers ultimately represent integer values using **bits** `0`s and `1`s.

For example, the number `5` can be represented in binary as:
```
5 = 0101
```
And `3` is:
```
3 = 0011
```
Until now, we have mostly treated `5` and `3` as complete numbers.

Bitwise operators let us work with the individual bits that make up those numbers. This is particularly useful in areas such as embedded systems, hardware programming, networking, compression, permissions, and other low-level programming.

C++ provides several bitwise operators:

|Operator|Name|
|---|---|
|`&`|Bitwise AND|
|`|`|Bitwise OR|
|`^`|Bitwise XOR|
|`~`|Bitwise NOT|
|`<<`|Left shift|
|`>>`|Right shift|

### `&`  Bitwise AND
Bitwise AND performs an AND operation on each corresponding bit, it compares the bits one by one. A resulting bit is `1` only when **both corresponding bits are** `1`. 

For example:
```
  0101   // 5
& 0011   // 3
------
  0001   // 1
```
So:
```
5 & 3
```
produces:
```
1
```
### `|` Bitwise OR
Bitwise OR performs an OR operation on each corresponding bit, it compares bits one by one. This time, a resulting bit is `1` when **at least one of the corresponding bits is** `1`.
```
  0101   // 5
| 0011   // 3
------
  0111   // 7
```
So:
```
5 | 3
```
produces:
```
7
```
### `^` Bitwise XOR
XOR stands for **exclusive OR**. A resulting bit is `1` when the two corresponding bits are different.
```
  0101   // 5
^ 0011   // 3
------
  0110   // 6
```
So:
```
5 ^ 3
```
produces:
```
6
```
### `~` Bitwise NOT
Bitwise NOT flips every bit. Every `0` becomes `1`, and every `1` becomes `0`.

Conceptually:
```
0101
```
becomes:
```
1010
```
So:
```
~5
```
inverts the bits of `5`.

The exact decimal result depends on the integer type and its representation, so for now it is more useful to understand `~` as **"flip every bit."**
### `<<` Left Shift
The left-shift operator moves all bits to the left by a specified number of positions.

For example:
```
5 << 1
```
Start with:
```
0101
```
Shift everything one position to the left:
```
1010
```
which is `10`.

For unsigned integers, a left shift by one position corresponds to multiplying by `2`, provided no significant bits are lost.

```
5 << 1   // 10
5 << 2   // 20
```
### `>>` Right Shift
The right-shift operator moves the bits to the right.

For example:
```
10 >> 1
```
Start with:
```
1010
```
Shift one position to the right:
```
0101
```
which is `5`.
## Control Flow
Up to this point, our programs have mostly executed instructions from top to bottom.    
For example:
```cpp
cout << "First";
cout << "Second";
cout << "Third";
```
The program starts with the first instruction, then moves to the second, and finally to the third.

But real programs rarely work this way all the time. Sometimes we want the program to **make a decision**.

For example:
- If the user enters a positive number, print `"Positive"`.
- If the user is under 18, deny access.
- If the user enters `1`, perform one operation; if they enter `2`, perform another.
- If a condition is true, do something; otherwise, do something else.
    

This is what **control flow** allows us to do.

Control flow refers to the way a program decides which instructions to execute and in what order.
### Conditional Statements
A conditional statement allows us to execute code depending on whether a condition is `true` or `false`.

C++ provides several ways to do this:
- `if`
- `else if`
- `else`
- the **ternary operator** `?:`
#### `if` Statement
The `if` statement allow us to run instructions only if this condition is true.

The basic structure is:
```cpp
if (condition) {
    // instructions
}
```
The condition is placed inside parentheses `()`.

If the condition evaluates to `true`, C++ executes the code inside the curly braces `{}`. If the condition is `false`, C++ simply skips that block and continues with the next instruction.

For example:
```cpp
int age = 20;

if (age >= 18) {
    cout << "You are an adult.";
}
```
Here, C++ checks:
```cpp
age >= 18
```
Since `20 >= 18` is `true`, the message is printed.

If we change the value:
```cpp
int age = 15;
```
the condition becomes false, so the code inside the `if` block is skipped.
#### `else` Statement
Sometimes we don't want to simply skip the code when the condition is false. We want the program to do something else. This is where `else` comes in.

The structure becomes:
```cpp
if (condition) {
    // runs if condition is true
}
else {
    // runs if condition is false
}
```
The `else` block does not have its own condition. It is automatically connected to the `if` before it.

For example:
```cpp
int age = 15;

if (age >= 18) {
    cout << "You are an adult.";
}
else {
    cout << "You are not an adult.";
}
```
The program checks:
```cpp
age >= 18
```
If it is true, the first block runs, If it is false, the `else` block runs.
#### `else if`
What if we have more than two possibilities?

For example, a number can be:
- positive
- negative
- zero
    

An `if` and an `else` are not enough because we have three different cases. This is where `else if` is useful.

The structure looks like this:
```cpp
if (condition1) {
    // condition1 is true
}
else if (condition2) {
    // condition2 is true
}
else {
    // none of the previous conditions are true
}
```
C++ checks the conditions from top to bottom.

As soon as it finds a condition that is true, it executes that block and skips the remaining `else if` and `else` blocks.

For example:
```cpp
#include <iostream>
using namespace std;

int main() {

    int number;

    cout << "Enter a number: ";
    cin >> number;

    if (number > 0) {
        cout << "Positive" << endl;
    }
    else if (number < 0) {
        cout << "Negative" << endl;
    }
    else {
        cout << "Zero" << endl;
    }

    return 0;
}
```
If the user enters `10`, the first condition is true:
```cpp
number > 0
```
so `"Positive"` is printed.

If the user enters `-5`, the first condition is false, so C++ checks:
```cpp
number < 0
```
This time it is true, so `"Negative"` is printed.

If the user enters `0`, both previous conditions are false, so the `else` block runs.


With an `if / else if / else` chain, C++ checks conditions in order:
```text
if
 ↓
else if
 ↓
else if
 ↓
else
```
Once one condition is satisfied, the rest of the chain is skipped. This is important because the order of your conditions can affect the result.

For example:
```cpp
if (number > 0) {
    // ...
}
else if (number > 10) {
    // ...
}
```
The second condition can never be reached for values greater than `10`, because those values already satisfy `number > 0`.

A better ordering would be:
```cpp
if (number > 10) {
    // ...
}
else if (number > 0) {
    // ...
}
```

#### The Ternary Operator
Sometimes we have a very small decision where we simply want to choose between **two values**.

For example:
```cpp
if (age >= 18) {
    status = "Adult";
}
else {
    status = "Minor";
}
```
This works perfectly well, but for a simple assignment like this, C++ provides a shorter form called the **ternary operator**.

Its syntax is:
```cpp
condition ? value_if_true : value_if_false;
```
So the previous example can become:
```cpp
string status = (age >= 18) ? "Adult" : "Minor";
```

### Switch Statements
There is another situation where `if/else` isn't always the clearest option. Imagine we have a variable representing a menu choice:
```cpp
int choice;
```
and we want to do something different for:
```text
1 → Start
2 → Settings
3 → Help
4 → Exit
```
We could write:
```cpp
if (choice == 1) {
    // ...
}
else if (choice == 2) {
    // ...
}
else if (choice == 3) {
    // ...
}
else if (choice == 4) {
    // ...
}
```
This works, but when we're simply comparing one value against several fixed values, a `switch` statement can make the intention much clearer.

A better way to represent this is using `switch`  which help use to look at value and chose the matching case.   
The basic structure is:
```cpp
switch (value) {

    case value1:
        // instructions
        break;

    case value2:
        // instructions
        break;

    case value3:
        // instructions
        break;

    default:
        // no case matched
        break;
}
```
The expression inside `switch` is evaluated once. C++ then looks through the `case` labels for a matching value.   
A `switch` works with integral and enumeration types, such as:
```cpp
int
char
enum
```
#### `case`
Each `case` represents one possible value.

For example:
```cpp
switch (number) {

    case 1:
        cout << "One";
        break;

    case 2:
        cout << "Two";
        break;

    case 3:
        cout << "Three";
        break;
}
```
If `number` is `2`, C++ jumps to:
```cpp
case 2:
```
and executes the code there.

#### `break`
We use `break` at the end of each case because, by default, C++ does **not** automatically stop after executing a case.

For example:
```cpp
switch (number) {

    case 1:
        cout << "One" << endl;

    case 2:
        cout << "Two" << endl;

    case 3:
        cout << "Three" << endl;
}
```
If `number` is `1`, C++ starts at `case 1` and then continues into `case 2` and `case 3`. This behavior is called **fallthrough**.   
If we don't want that behavior, we normally use `break`:
```cpp
switch (number) {

    case 1:
        cout << "One" << endl;
        break;

    case 2:
        cout << "Two" << endl;
        break;

    case 3:
        cout << "Three" << endl;
        break;
}
```
Now, once the matching case finishes, `break` exits the `switch`.

If we want to apply fallthrough in our switch we can use  the `[[fallthrough]]` attribute to make intentional fallthrough explicit.
```cpp
switch (number) {

    case 1:
        cout << "One";
        [[fallthrough]];

    case 2:
        cout << "Two";
        break;
}
```
The `[[fallthrough]]` attribute tells both the compiler and other programmers that this fallthrough is intentional.


#### `default`
What happens if none of the cases match? That's what `default` is for.
```cpp
switch (number) {

    case 1:
        cout << "One";
        break;

    case 2:
        cout << "Two";
        break;

    default:
        cout << "Something else";
        break;
}
```
If `number` is neither `1` nor `2`, the `default` block executes.  `default` is similar to the final `else` in an `if/else if/else` chain.
## Loops

So far, our programs have mostly executed each instruction once. But what if we want to perform the same operation **many times**?

For example, imagine we want to print `"Hello"` five times:
```cpp
cout << "Hello" << endl;
cout << "Hello" << endl;
cout << "Hello" << endl;
cout << "Hello" << endl;
cout << "Hello" << endl;
```
This works, but it becomes a terrible solution if we need to repeat the operation 100 or 1,000 times.

Instead of writing the same instructions over and over again, we can tell C++ to Repeat  block of code for us.

This is what a **loop** does.

A loop allows us to execute a block of code repeatedly according to some rule.

The rule might be:
- Repeat while a condition is true.
- Repeat a specific number of times.
- Repeat once for every element in a collection.

C++ provides several types of loops:
- `while`
- `do-while`
- `for`
- **range-based `for`**

The first three are the traditional loop structures. The range-based `for` loop was introduced in **C++11** and provides a much simpler way to iterate through collections and ranges of values.

### `while` Loop
A `while` loop is useful when we know the condition that should keep the loop running, but we don't necessarily know how many iterations will be needed.

Its basic structure is:
```cpp
while (condition) {
    // instructions to repeat
}
```
C++ follows a simple process:
1. Check the condition.
2. If the condition is `true`, execute the loop body.
3. Go back and check the condition again.
4. Repeat until the condition becomes `false`.

For example:
```cpp
int i = 0;

while (i < 5) {
    cout << "Hello" << endl;
    i++;
}
```
The variable `i` starts at `0`.

The program checks:
```cpp
i < 5
```
Since the condition is true, `"Hello"` is printed.

Then:
```cpp
i++;
```
changes `i` to `1`.

The condition is checked again and continues until `i` becomes `5`.

At that point:
```cpp
5 < 5
```
is false, so the loop stops.

### `do-while` Loop
The `while` loop checks its condition **before** executing the loop body. Sometimes, however, we want the code to run **at least once**, and only then decide whether it should continue.

That's where the `do-while` loop comes in.  
Its structure is:
```cpp
do {
    // instructions to repeat
} while (condition);
```
The `do-while` loop always executes its body at least once.

For example:
```cpp
int i = 0;

do {
    cout << "Hello" << endl;
    i++;
} while (i < 5);
```
This behaves similarly to our previous example.

But the difference becomes obvious when the condition is false from the beginning:
```cpp
int i = 10;

do {
    cout << "Hello" << endl;
} while (i < 5);
```
The condition:
```cpp
i < 5
```
is already false. However, `"Hello"` is still printed once because the body executes **before** the condition is checked.

### `for` Loop
The `for` loop is often the most convenient loop when we know how many times we want to repeat something, or when we are working through a sequence of values.

Its traditional form is:
```cpp
for (initialization; condition; update) {
    // instructions to repeat
}
```
There are three parts inside the parentheses.
#### Initialization
The initialization happens once, before the loop starts. It is commonly used to create and initialize a counter:
```cpp
int i = 0
```
#### Condition
The condition is checked before every iteration. If it is `true`, the loop body runs. If it is `false`, the loop stops.
```cpp
i < 5
```
#### Update
The update happens after each iteration. It is commonly used to increase or decrease the counter:
```cpp
i++
```
Putting everything together:
```cpp
for (int i = 0; i < 5; i++) {
    cout << "Hello" << endl;
}
```
The update doesn't have to be `i++`. We can increase by different amounts:
```cpp
for (int i = 0; i < 10; i += 2) {
    cout << i << endl;
}
```
We can also count backwards:
```cpp
for (int i = 5; i > 0; i--) {
    cout << i << endl;
}
```
### Range-Based `for` Loop
The traditional `for` loop is excellent when we need to control a counter. But sometimes we don't actually care about the counter.

Imagine we have a collection of numbers:
```cpp
int numbers[] = {10, 20, 30, 40, 50};
```
Suppose we simply want to print every number. With a traditional `for` loop, we might write:
```cpp
for (int i = 0; i < 5; i++) {
    cout << numbers[i] << endl;
}
```
This works, but we are not really interested in `i`, we just want loop and get the element of the array.   
C++11 introduced the **range-based `for` loop** to make this kind of iteration much simpler.

The syntax is:
```cpp
for (element : range) {
    // instructions
}
```
For our array:
```cpp
for (int number : numbers) {
    cout << number << endl;
}
```
This means for every element in `numbers`, place that element into `number` and execute the loop body.
#### References in Range-Based `for`

By default the range based loop creates a copy of each element.
```cpp
for (int number : numbers)
```
If we want to work with the original elements instead, we can use a reference:
```cpp
for (int& number : numbers) {
    number *= 2;
}
```
Now `number` refers directly to each element in the array.

For example:
```cpp
int numbers[] = {1, 2, 3, 4, 5};

for (int& number : numbers) {
    number *= 2;
}
```
If we only want to read the values without copying them, a `const` reference is often appropriate:
```cpp
for (const int& number : numbers) {
    cout << number << endl;
}
```
### Break and Continue :

#### `break`
Our loops have stopped naturally when their conditions became false. But sometimes we want to stop a loop immediately, before its normal condition tells it to stop.

The `break` statement does exactly that.

When C++ reaches `break`, it immediately exits the **nearest loop or `switch` statement**.

For example:

```cpp
for (int i = 0; i < 10; i++) {

    if (i == 5) {
        break;
    }

    cout << i << endl;
}
```
The loop normally could continue until `i` reaches `10`, but when `i` becomes `5`, `break` is executed, the loop stops immediately.

The output is:
```text
0
1
2
3
4
```
Notice that `5` is never printed.
#### `continue`
`continue` help us to skip the rest of this iteration and move to the next one.

For example:
```cpp
for (int i = 1; i <= 10; i++) {

    if (i % 2 == 0) {
        continue;
    }

    cout << i << endl;
}
```
When `i` is even, `continue` is executed, everything below it in the current iteration is skipped. the loop then continues with the next iteration.

The output is:
```text
1
3
5
7
9
```

#### Early `return`
Unlike `break` and `continue`, `return` is not specifically a loop statement, Instead, `return` ends the execution of the current function. This becomes especially useful when a loop is inside a function.

For example:
```cpp
bool contains(int numbers[], int size, int target) {

    for (int i = 0; i < size; i++) {

        if (numbers[i] == target) {
            return true;
        }
    }

    return false;
}
```
When the target is found:
```cpp
return true;
```
immediately ends the function, there is no reason to continue searching.

This is sometimes called an **early return** because the function returns before reaching the end of its normal flow.

## Tasks :
### Task 1 :

Write a C++ program that reads three numbers, **a**, **b**, and **c**, from the user, and then solves the quadratic equation:
$$
a^2+bx+c =0
$$
The program should handle the following cases:
1. When the discriminant $b^2 - 4ac$ is positive, there are two real and distinct roots.
2. When the discriminant is zero, there is one real root .
3. When the discriminant is negative, the equation has no real solutions.
### Task 2:
Write a program that reads a number **n** from the user and displays all the prime numbers from 0 to **n**.
#### Hint :
A prime number is a number that can only be divided by 1 and itself.