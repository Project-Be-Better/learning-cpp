#include "calculator.h"
#include <iostream>

int main()
{
    svt::Calculator calc;

    std::cout << "Addition : " << calc.add(3, 2) << std::endl;
    std::cout << "Multiply : " << calc.multiply(3, 2) << std::endl;
    std::cout << "Subtract : " << calc.subtract(3, 2) << std::endl;
    std::cout << "Divide : " << calc.divide(3, 2) << std::endl;

    return 0;
}