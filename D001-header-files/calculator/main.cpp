#include <iostream>
#include "calculator.h"

int main()
{
    Calculator calc;
    std::cout << "addition 2 + 3" << calc.add(2, 3) << std::endl;
    std::cout << "subtraction 5 - 2" << calc.subtract(5, 2) << std::endl;
};