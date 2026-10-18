#include <iostream>
#include <string>
#include <optional>
#include <expected>
#include <cassert>

std::expected<double, std::string> convertToNumber(const std::string& input){
    if (input.empty())
        return std::unexpected("Input cannot be empty.");

    double number;
    try{
        number = stoi(input);
    }
    catch(...){
        return std::unexpected("Failed to convert");
    }
    
    return number;
}

std::optional<double> validateRange(double number){
    if (number < 0 || number > 100)
        return std::nullopt;

    return number;
}

int main(){
    static_assert(100 >= 0, "The maximum must be non-negative.");

    std::string input;

    std::cout << "Enter a number between 0 and 100: ";
    std::cin >> input;

    auto result = convertToNumber(input);

    if (!result){
        std::cout << "Error: " << result.error() << '\n';
        return 1;
    }

    double number = result.value();

    assert(number == number); // Verify that the number is not NaN.

    auto validNumber = validateRange(number);

    if (!validNumber){
        std::cout << "Error: Number must be between 0 and 100.\n";
        return 1;
    }

    std::cout << "Converted number: " << validNumber.value() << '\n';

    return 0;
}