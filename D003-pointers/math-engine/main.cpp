#include "calculator.h"
#include <iostream>

int main()
{

    Calculator calc(20, 5);

    // Function pointer to static method
    Calculator::Operation op = Calculator::add;
    int result = calc.execute(op);

    std::cout << "Result of multiply : " << result << std::endl; // Output: 25
}