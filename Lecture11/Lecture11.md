# File I/O and Stream Formatting

## Learning Objectives
- Read and write text files with standard file streams.
- Parse and format text with string streams.
- Understand the limits and portability risks of raw binary file I/O.
- Format console and file output with stream manipulators.
## Streams & File I/O
### Introduction
So far, most of our C++ programs have received input from the keyboard and displayed results on the screen. This works well when we want to experiment with an algorithm, but practical applications often need to store information after a program finishes or retrieve information that was recorded earlier.

Consider a program that measures temperature using a sensor. During execution, it might collect hundreds of measurements. Keeping these measurements only in memory means they disappear when the program terminates.

We need a mechanism that allows the program to store the measurements and retrieve them later.

C++ provides **streams** for this purpose. A stream represents a flow of data between a program and a source or destination. The source may be a keyboard, a file, or an in-memory string. The destination may be the screen, a file, or a string stored in memory.

We have already used streams when writing:
```cpp
std::cout << "Hello, world!\n";
```
Here, `std::cout` is an output stream connected to the standard output.

Similarly:
```cpp
int value;
std::cin >> value;
```
uses an input stream to read a value from the standard input.
### File Streams
C++ provides file streams through the `<fstream>` header. The three main file stream types are:

|Type|Purpose|
|---|---|
|`std::ifstream`|Reads data from a file.|
|`std::ofstream`|Writes data to a file.|
|`std::fstream`|Supports both reading and writing.|

The letter `i` in `ifstream` stands for input, while the `o` in `ofstream` stands for output. Unlike `std::cin` and `std::cout`, which are predefined streams, file streams must be connected to files.
#### Reading a File with `std::ifstream`
Suppose we have a file named `measurements.txt` containing:
```
23.5
24.1
22.8
25.0
```
We want to read the measurements into our program. We can manage that using `ifstream` , here example
```cpp
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::ifstream input("measurements.txt");

    if (!input) {
        std::cerr << "Error: Could not open the file.\n";
        return 1;
    }

    std::vector<double> measurements;
    double value;

    while (input >> value) {
        measurements.push_back(value);
    }

    if (!input.eof()) {
        std::cerr << "Error: Invalid data in the file.\n";
        return 1;
    }

    std::cout << "Measurements:\n";

    for (double measurement : measurements) {
        std::cout << measurement << '\n';
    }

    return 0;
}
```
First, we create the input stream:
```cpp
std::ifstream input("measurements.txt");
```
The stream attempts to open the specified file. If the file does not exist or cannot be accessed, the operation fails.

We therefore check the stream before reading:
```cpp
if (!input) {
    std::cerr << "Error: Could not open the file.\n";
    return 1;
}
```
This prevents the program from treating a failed file operation as a successful one. Here, `std::cerr` is used to report an error.

Next, we read the measurements:
```cpp
double value;

while (input >> value) {
    measurements.push_back(value);
}
```
The expression:
```cpp
input >> value
```
attempts to extract a numeric value from the file and store it in `value`. If the extraction succeeds, the loop continues. If it fails, the loop stops. This naturally handles a sequence of measurements separated by whitespace, including spaces and newlines.

The following line stores each successfully read measurement:
```cpp
measurements.push_back(value);
```
We also check whether the loop stopped for a reason other than reaching the end of the file:
```cpp
if (!input.eof()) {
    std::cerr << "Error: Invalid data in the file.\n";
    return 1;
}
```
This is useful when the file is expected to contain only numeric measurements. For production applications, parsing and reporting file-format errors can be made more precise, especially when files may contain malformed records or encounter low-level I/O errors.
#### Writing to a File with `std::ofstream`
Reading allows us to retrieve stored information. Writing allows us to preserve the results of a computation. Suppose we have calculated the average temperature and want to save it in a report.
```cpp
#include <fstream>
#include <iostream>

int main() {
    double averageTemperature = 23.85;

    std::ofstream output("report.txt");

    if (!output) {
        std::cerr << "Error: Could not create the report.\n";
        return 1;
    }

    output << "Temperature Report\n";
    output << "------------------\n";
    output << "Average temperature: " << averageTemperature << '\n';

    std::cout << "Report saved successfully.\n";

    return 0;
}
```
The output stream is created with:
```cpp
std::ofstream output("report.txt");
```
If the file can be opened, the program writes to it using the familiar insertion operator:
```cpp
output << "Temperature Report\n";
```
Notice that the syntax is almost identical to using `std::cout`. The difference is that the destination is a file rather than the screen.

A file stream must also be checked before writing:
```cpp
if (!output) {
    std::cerr << "Error: Could not create the report.\n";
    return 1;
}
```
Opening successfully does not guarantee that every later write will succeed. Storage errors and other I/O failures can occur during execution, so programs that depend on reliable file output should check the stream after important writes and at the end of the operation.

When the stream is destroyed, the file is automatically closed. We can also close it explicitly using:
```cpp
output.close();
```
Explicit closing is useful when we need to finish writing before reopening the same file for another operation. In ordinary cases, automatic closing through the stream object's lifetime is sufficient.

#### Understanding File Opening Modes
Opening a file is not just about specifying its name. Sometimes we need to choose how the file should be accessed. C++ provides several file-opening modes.

| Mode               | Meaning                                                                      |
| ------------------ | ---------------------------------------------------------------------------- |
| `std::ios::in`     | Opens a file for reading.                                                    |
| `std::ios::out`    | Opens a file for writing.                                                    |
| `std::ios::app`    | Writes at the end of the file.                                               |
| `std::ios::ate`    | Opens the file and initially positions the stream at the end.                |
| `std::ios::trunc`  | Truncates the existing file when opening it, removing its previous contents. |
| `std::ios::binary` | Opens the file in binary mode.                                               |

These modes can be combined using the bitwise OR operator, `|`.
```cpp
#include <fstream>
#include <iostream>

int main() {
    std::ofstream logFile("application.log", std::ios::app);

    if (!logFile) {
        std::cerr << "Could not open the log file.\n";
        return 1;
    }

    logFile << "Application started.\n";

    return 0;
}
```
Here, the file is opened in append mode. The program adds a new line to the end of the existing file instead of replacing the previous contents, this behavior is useful for logs, measurement histories, and other records that must accumulate over time.

By contrast:
```cpp
std::ofstream output("report.txt");
```
normally opens the file for output and truncates an existing file. This distinction matters. If a program is expected to preserve historical records, accidentally opening a file in truncating mode can destroy the data it was supposed to retain.

For a file that must support both reading and writing, we can use:
```cpp
std::fstream file(
    "data.txt",
    std::ios::in | std::ios::out
);
```
The exact combination of modes should reflect the intended operation.

### String Streams with `std::stringstream`
Files are not the only source of data that requires parsing. Imagine that a program receives the following string:
```cpp
SENSOR_01 23.5 NORMAL
```
The string contains three separate pieces of information:
- The sensor identifier.
- The measured value.
- The sensor status.

We may want to extract these fields and store them in separate variables, we could manually search for spaces and divide the string into pieces. However, C++ already provides a mechanism that behaves like a stream but uses a string as its source or destination.

This mechanism is called a **string stream**. The `<sstream>` header provides three useful types:

| Type                 | Purpose                                                |
| -------------------- | ------------------------------------------------------ |
| `std::istringstream` | Reads data from a string.                              |
| `std::ostringstream` | Writes data into a string.                             |
| `std::stringstream`  | Supports both input and output operations on a string. |
#### Parsing Structured Text
Let's make simple example to illustrate how to parse  sensor measurement using `std::stringstream`.
```cpp
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string record = "SENSOR_01 23.5 NORMAL";

    std::stringstream input(record);

    std::string sensorId;
    double temperature;
    std::string status;

    if (input >> sensorId >> temperature >> status) {
        std::cout << "Sensor: " << sensorId << '\n';
        std::cout << "Temperature: " << temperature << '\n';
        std::cout << "Status: " << status << '\n';
    } else {
        std::cerr << "Invalid sensor record.\n";
        return 1;
    }

    return 0;
}
```
First, we create a string stream:
```cpp
std::stringstream input(record);
```
The stream takes its initial content from `record`. We can then extract values using the same operator we used with `std::cin` and file streams:
```cpp
input >> sensorId >> temperature >> status;
```
The stream reads the first whitespace-separated field into `sensorId`, the next into `temperature`, and the final one into `status`. The extraction also performs type conversion. The text `"23.5"` is converted to a `double` when it is successfully read into `temperature`.
#### Parsing Multiple Values from a String
We saw how we can parse and extract information from string but what if we want to get multiple values. Suppose a sensor sends a string containing several measurements:
```
21.5 22.0 21.8 22.4 23.1
```
We want to calculate their average. Instead of writing a separate parsing routine, we can use a string stream and a loop.
```cpp
#include <iostream>
#include <sstream>

int main() {
    std::string data = "21.5 22.0 21.8 22.4 23.1";

    std::stringstream input(data);

    double value;
    double total = 0.0;
    int count = 0;

    while (input >> value) {
        total += value;
        ++count;
    }

    if (count == 0) {
        std::cout << "No measurements found.\n";
        return 0;
    }

    double average = total / count;

    std::cout << "Number of measurements: " << count << '\n';

    std::cout << "Average: " << average << '\n';

    return 0;
}
```
The key expression is:
```
while (input >> value)
```
Each successful extraction obtains the next measurement. The program then adds the measurement to `total` and increases `count`. When the stream can no longer extract another numeric value, the loop stops.
#### Parsing Comma-Separated Fields
Many files and data sources use commas to separate fields. For example:
```
SENSOR_01,23.5,NORMAL
```
We can use `std::getline()` with a delimiter to extract the fields.
```cpp
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string record = "SENSOR_01,23.5,NORMAL";

    std::stringstream input(record);

    std::string sensorId;
    std::string temperatureText;
    std::string status;

    std::getline(input, sensorId, ',');
    std::getline(input, temperatureText, ',');
    std::getline(input, status);

    try {
        double temperature = std::stod(temperatureText);

        std::cout << "Sensor: " << sensorId << '\n';
        std::cout << "Temperature: " << temperature << '\n';
        std::cout << "Status: " << status << '\n';
    } catch (const std::exception&) {
        std::cerr << "Invalid temperature field.\n";
        return 1;
    }

    return 0;
}
```
The first operation:
```cpp
std::getline(input, sensorId, ',');
```
reads characters until the comma is encountered. The comma itself is consumed but is not included in the resulting string.

The following call extracts the next field:
```cpp
std::getline(input, temperatureText, ',');
```
Finally:
```cpp
std::getline(input, status);
```
reads the remaining field because we have not specified another delimiter.

The `temperatureText` is initially a string. We then convert it to a number.
```cpp
double temperature = std::stod(temperatureText);
```
The conversion is placed inside a `try` block because `std::stod()` can throw an exception if the string cannot be converted appropriately
#### Building Strings with `std::ostringstream`
String streams can also construct text. Suppose we want to generate a report in memory before displaying it or writing it to a file.
```cpp
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string sensorId = "SENSOR_01";
    double temperature = 23.5;
    bool operational = true;

    std::ostringstream report;

    report << "Sensor: " << sensorId << '\n';
    report << "Temperature: " << temperature << '\n';
    report << "Operational: " << std::boolalpha << operational << '\n';

    std::string result = report.str();

    std::cout << result;

    return 0;
}
```
The operations look similar to writing to `std::cout`:
```cpp
report << "Temperature: " << temperature << '\n';
```
The difference is that the resulting text is accumulated inside the string stream. We retrieve the completed string using:
```cpp
std::string result = report.str();
```
This becomes useful when we need to assemble messages, construct reports, prepare formatted records, or generate text that will later be transmitted or saved.
### Binary File I/O
So far, we have worked mainly with text files, where data is stored as readable characters. But applications often need to work with data that is not naturally represented as text, such as images, audio, video, or structured records. In these cases, we can store and retrieve data directly as bytes, without converting each value into a textual representation.

A **binary file** stores data as a sequence of bytes, preserving the byte values written to it rather than representing them as formatted characters.

C++ uses the same file stream classes for binary operations, but we open the file with the std::ios::binary flag to indicate that we want to handle its contents as binary data.

Two member functions are central to this process:
```cpp
output.write(data, numberOfBytes);
```
and:
```cpp
input.read(data, numberOfBytes);
```
Unlike the formatted extraction operator >>, which interprets input according to the type of the variable receiving it, `read()` and `write()` transfer a specified number of bytes directly between a file and a memory buffer.

This gives us more direct control over how data is stored and retrieved. However, it also means that we must understand the representation of the data in memory and ensure that the bytes are interpreted correctly when read back.
### Writing a Binary Record
Consider an application that manages products in an inventory. Each product has an identifier and a price:
```cpp
struct ProductRecord {
    std::int32_t id;
    double price;
};
```
We could store these values as readable text, but we can also write the record's memory representation directly to a binary file.

Let's see how C++ allows us to write a record and reconstruct it later.
```cpp
#include <cstdint>
#include <fstream>
#include <iostream>
#include <type_traits>

struct ProductRecord {
    std::int32_t id;
    double price;
};

int main() {
    static_assert(
        std::is_trivially_copyable_v<ProductRecord>,
        "ProductRecord must be trivially copyable."
    );

    ProductRecord original{101, 49.99};

    {
        std::ofstream output("product.bin", std::ios::binary);

        if (!output) {
            std::cerr << "Could not open the binary file.\n";
            return 1;
        }

        output.write(
            reinterpret_cast<const char*>(&original),
            static_cast<std::streamsize>(sizeof(original))
        );

        if (!output) {
            std::cerr << "Failed to write the record.\n";
            return 1;
        }
    }

    ProductRecord loaded{};

    std::ifstream input("product.bin", std::ios::binary);

    if (!input) {
        std::cerr << "Could not open the binary file.\n";
        return 1;
    }

    input.read(
        reinterpret_cast<char*>(&loaded),
        static_cast<std::streamsize>(sizeof(loaded))
    );

    if (!input ||
        input.gcount() !=
            static_cast<std::streamsize>(sizeof(loaded))) {
        std::cerr << "Incomplete binary record.\n";
        return 1;
    }

    std::cout << "Product ID: " << loaded.id << '\n';
    std::cout << "Price: " << loaded.price << '\n';

    return 0;
}
```
First, we define the record and create an instance:
```cpp
ProductRecord original{101, 49.99};
```
The object holds the product identifier and price in memory. Instead of converting these values into text, we will write the object's underlying bytes directly to the file.

Before doing so, we use:
```cpp
static_assert(
    std::is_trivially_copyable_v<ProductRecord>,
    "ProductRecord must be trivially copyable."
);
```
This asks the compiler to verify that the record type is _trivially copyable_. Such types support copying their object representation under the rules of C++, making them suitable for this kind of raw-byte operation. However, this does not guarantee that the representation will be portable between different systems.

Next, we open the file in binary mode:
```cpp
std::ofstream output("product.bin", std::ios::binary);
```
We can then write the record:
```cpp
output.write(
    reinterpret_cast<const char*>(&original),
    static_cast<std::streamsize>(sizeof(original))
);
```
Here, `&original` obtains the address of the object, while `sizeof(original)` determines its size in bytes.

The `reinterpret_cast` provides the `const char*` pointer required by `write()`. This allows the function to access the object's memory representation as a sequence of characters representing its bytes.

The file stream is enclosed in a separate scope. When execution leaves that scope, the stream is destroyed and the file is closed automatically.

We can then open the file for reading and transfer the stored bytes into a new object
```cpp
ProductRecord loaded{};

input.read(
    reinterpret_cast<char*>(&loaded),
    static_cast<std::streamsize>(sizeof(loaded))
);
```
The destination object, `loaded`, receives the bytes read from the file. But what happens if the file does not contain enough data to reconstruct the complete record?

To detect this, the program checks:
```cpp
if (!input ||
    input.gcount() !=
        static_cast<std::streamsize>(sizeof(loaded))) {
    std::cerr << "Incomplete binary record.\n";
    return 1;
}
```
The stream's state indicates whether the read operation failed, while `gcount()` reports how many characters were extracted by the most recent unformatted input operation. Together, these checks help us detect incomplete records.

If the read succeeds, we can access the restored fields just as we would with any other object:
```cpp
std::cout << "Product ID: " << loaded.id << '\n';
std::cout << "Price: " << loaded.price << '\n';
```
The important idea is that `write()` and `read()` transfer bytes rather than converting individual values into formatted text.
### Reading and Writing Binary Data Safely

> **Portability warning:** Writing a structure with `write(reinterpret_cast<const char*>(&object), sizeof object)` is suitable only for controlled cases where the same program, compiler ABI, and data representation are expected. Padding, endianness, type sizes, and floating-point representation can vary. For long-lived or cross-platform files, serialize each field explicitly in a documented format instead of dumping a structure.
Writing an object's raw memory representation is useful for understanding binary file I/O, but it comes with important limitations.

**First, an object's memory layout is not necessarily portable.** A compiler may insert padding bytes between structure members to satisfy alignment requirements. Consequently, two systems can use different layouts for the same structure.

**Second, byte order can differ between systems.** Multibyte values may be represented with the most significant byte first or the least significant byte first. A file written on one system may therefore require conversion before its numerical values can be interpreted correctly on another.

**Third, not every object can be stored by writing its raw memory.** Consider a string:
```cpp
std::string message = "Hello";
```
The string object contains implementation-managed state and typically refers to separately managed character storage. Writing the bytes of the `std::string` object does not reliably save the text itself. Instead, we should write the actual character data according to a defined format. One approach is to store the string's length, followed by its characters.

The same principle applies to containers such as `std::vector`: their contents must be stored explicitly rather than assuming that copying the container object's memory will preserve its elements.

**Finally, input must be validated.** Binary files can be incomplete or malformed. If a file contains a record count or a data length, the program should validate it before allocating memory or attempting to process the corresponding data.

For a portable binary format, we should define how each field is represented, including its size, byte order, and position in the file. Explicit serialization rules are more reliable than writing entire structures directly.

The example above demonstrates raw binary operations in a controlled environment where the writing and reading programs use compatible data representations. For long-term storage or file exchange between different systems, a defined serialization format is generally the safer choice
### Stream Manipulators
When displaying information, calculating the correct result is only part of the task. We must also decide how that result should be presented.

For example, suppose an application calculates the price of a product:
```cpp
double price = 23.5;
```
By default, the output stream chooses a suitable representation for the value. But when generating an invoice, we may want every price to display exactly two digits after the decimal point:

```
23.50
```
Likewise, when displaying a list of products, we may want their names and prices to appear in aligned columns. We might also need to display Boolean values as words or represent integers in different number systems.

C++ provides **stream manipulators** to control these aspects of input and output formatting. Many commonly used formatting manipulators, including `std::setw()` and `std::setprecision()`, are provided by `<iomanip>`.
#### Controlling Decimal Precision
Suppose we want to display a product's price with exactly two digits after the decimal point.
```cpp
#include <iomanip>
#include <iostream>

int main() {
    double price = 23.5;

    std::cout << price << '\n';

    std::cout << std::fixed << std::setprecision(2) << price << '\n';

    return 0;
}
```
The first statement uses the stream's default floating-point formatting. The second applies two manipulators:
```cpp
std::fixed << std::setprecision(2)
```

By default, `std::setprecision(n)` specifies the number of **significant digits** used to represent a floating-point value. When we apply `std::fixed`, it instead specifies the number of **digits after the decimal point**.

After applying this formatting, subsequent floating-point values written to the same stream will use two digits after the decimal point, unless the formatting is changed.

Notice that we do not need to repeat these manipulators before every number. Their formatting settings persist on the stream, allowing us to configure the output once and then display several values consistently.
#### Aligning Output with std::setw()
Formatting individual values is useful, but its importance becomes even clearer when displaying multiple records.

Consider an inventory report containing product names and prices. Without alignment, differences in the lengths of names and numbers can make the output difficult to read and scan.

We can use `std::setw()` to give each field a minimum width and combine it `with std::left` and `std::right` to control alignment.
```cpp
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::cout << std::left
              << std::setw(15) << "Product"
              << std::right
              << std::setw(12) << "Unit Price"
              << '\n';

    std::cout << std::string(27, '-') << '\n';

    std::cout << std::left
              << std::setw(15) << "Notebook"
              << std::right
              << std::fixed
              << std::setprecision(2)
              << std::setw(12) << 3.5
              << '\n';

    std::cout << std::left
              << std::setw(15) << "Keyboard"
              << std::right
              << std::setw(12) << 27.25
              << '\n';

    return 0;
}
```
The output is:
```
Product          Unit Price
---------------------------
Notebook               3.50
Keyboard              27.25
```
Let's understand how the formatting works.

The expression:
```cpp
std::setw(15)
```
specifies a minimum width of 15 characters for the next formatted field. Similarly:
```cpp
std::setw(12)
```
gives the next field a minimum width of 12 characters. These widths allow the values to occupy consistent spaces even when their actual lengths differ.

However, `std::setw()` generally affects only the next formatted field. Once that field has been written, the width setting is reset. This is why we apply it separately to each product name and price.

The alignment manipulators control how values appear within those fields:
```cpp
std::left
```
aligns values to the left, while:
```cpp
std::right
```
aligns them to the right.

Unlike `std::setw()`, these alignment settings persist on the stream until changed.
#### Filling Unused Width
Sometimes we want to control not only a field's width but also the characters used to fill the remaining space.

For example, when displaying an invoice number or a fixed-width identifier, we may want to add leading zeros. C++ provides `std::setfill()` for this purpose:
```cpp
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::setfill('0')
              << std::setw(5)
              << 42 << '\n';

    return 0;
}
```
The output is:
```
00042
```
Here, `std::setfill('0')` changes the stream's fill character to '0'. When the value 42 is written into a field five characters wide, the unused positions are filled with zeros.

The fill character persists until changed. Also, `std::setfill()` does not determine the field width itself; it specifies which character fills any unused width.
#### Displaying Boolean Values
By default, a Boolean value is normally displayed as 1 or 0. While this representation is compact, it may be less readable in a report.

Consider an application that tracks whether an order has been shipped:
```cpp
#include <iostream>

int main() {
    bool orderShipped = true;

    std::cout << orderShipped << '\n';

    std::cout << std::boolalpha << orderShipped << '\n';

    return 0;
}
```
The first output is:
```
1
```
The second output is:
```
true
```
The manipulator `std::boolalpha` changes the textual representation of Boolean values from 1 and 0 to true and false.

This setting persists on the stream until changed. We can restore the default numerical representation with `std::noboolalpha`.
#### Displaying Different Number Bases
Formatting also allows us to display integers in different number systems.

Most everyday numerical output uses **decimal notation**, which is base 10. However, hexadecimal notation (base 16) and octal notation (base 8) are also useful, particularly when examining memory values, bit patterns, and protocol fields.

Consider the following example:
```cpp
#include <iostream>

int main() {
    int value = 255;

    std::cout << std::dec << value << '\n';
    std::cout << std::hex << value << '\n';
    std::cout << std::oct << value << '\n';

    return 0;
}
```
The output is:
```
255
ff
377
```
The same integer is displayed differently depending on the selected base.

|Manipulator|Number system|Representation of 255|
|---|---|---|
|std::dec|Decimal, base 10|255|
|std::hex|Hexadecimal, base 16|ff|
|std::oct|Octal, base 8|377|

Each manipulator changes how subsequent integer values are formatted. The selected base persists on the stream until another base manipulator is applied. For example, after `using std::hex`, we can return to decimal notation with `std::dec`.

By default, hexadecimal output uses lowercase letters. The additional manipulator `std::uppercase` makes hexadecimal letters uppercase, while `std::nouppercase` restores lowercase formatting.

## Tasks
### Task 1 : 
Write a program in C++ that manages student grades using file streams.

1. Ask the user to enter the number of students and their names and grades.
2. Store the student names and grades in a file named `students.txt` using `std::ofstream`.
3. Open the file using `std::ifstream` and read the stored information.
4. Calculate and display the average grade, the highest grade, and the lowest grade.
5. Save a report containing the results in a file named `report.txt`.
6. Check whether each file opens successfully and handle possible file errors.

#### Hint :
Use `std::ofstream` to write data and `std::ifstream` to read data. Check the stream state before performing file operations.

### Task 2 : 
Write a program in C++ that processes employee records stored as comma-separated strings.

Each record follows this format:

```
101,Ahmed,25000
102,Sara,32000
103,Yacine,28000
104,Lina,35000
```

The fields represent the employee ID, name, and salary.

1. Store the records in a collection of strings.
2. Use `std::stringstream` and `std::getline()` to extract the fields from each record.
3. Convert the employee ID and salary into numerical values.
4. Display each employee's ID, name, and salary.
5. Calculate and display the average salary.
6. Find and display the employee with the highest salary.
7. Detect invalid records and report conversion errors.

#### Hint :

Use `std::getline(stream, field, ',')` to extract comma-separated fields and `std::stoi()` or `std::stod()` to convert strings into numbers.

### Task 3 : 

Write a program in C++ that stores and retrieves product records using a binary file.

Each product contains an integer ID, a quantity, and a price.

1. Define a `Product` structure containing the product ID, quantity, and price.
2. Create at least five products and write their records to a file named `products.bin` using binary output.
3. Open the file in binary input mode and read the stored records.
4. Display the ID, quantity, and price of each product.
5. Calculate and display the total value of the inventory.
6. Find and display the product with the highest price.
7. Detect incomplete records and handle failed read or write operations.

#### Hint :
Use `std::ios::binary`, `write()`, `read()`, and `sizeof()` to transfer raw bytes. Use `std::is_trivially_copyable_v` to verify that the structure supports raw-byte copying, and use `gcount()` to check how many bytes were read.

### Task 4: 

Write a program in C++ that generates a formatted invoice for a small shop.

Each product has a name, a product ID, a quantity, a unit price, and an availability status.

1. Create at least five products with different quantities, prices, and availability statuses.
2. Display the products in aligned columns using `std::setw()`, `std::left`, and `std::right`.
3. Display all prices with exactly two digits after the decimal point using `std::fixed` and `std::setprecision(2)`.
4. Display availability as `true` or `false` instead of `1` or `0`.
5. Display product IDs using leading zeros so that each ID occupies at least five characters.
6. Display the quantities in decimal, hexadecimal, and octal notation.
7. Save the formatted invoice to a file named `invoice.txt`.
#### Hint :
Use `<iomanip>` for formatting manipulators. Remember that `std::setw()` applies only to the next formatted field, while `std::fixed`, `std::setprecision()`, `std::boolalpha`, and the number-base manipulators affect subsequent output until changed.
