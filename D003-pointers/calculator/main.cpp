#include "calculator.h"
#include <iostream>

int main()
{
    int a = 10, b = 5;

    std::cout << "Addition: " << execute(a, b, add) << std::endl;
    std::cout << "Subtraction: " << execute(a, b, subtract) << std::endl;
    std::cout << "Multiplication: " << execute(a, b, multiply) << std::endl;
    std::cout << "Division: " << execute(a, b, divide) << std::endl;
    std::cout << "Division by zero: " << execute(a, 0, divide) << std::endl; // Handle division by zero
}