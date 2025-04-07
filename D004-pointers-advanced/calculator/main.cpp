#include "calculator.h"
#include <iostream>

int main()
{
    int a = 10, b = 5;

    // Dispatch table
    MathOp operations[] = {add, subtract, multiply, divide};

    // Pointer to Pointer
    int *resultPtr = new int;     // Dynamically allocate result to a pointer
    int **doublePtr = &resultPtr; // Pointer to result pointer

    *resultPtr = operations[0](a, b); // result of operation 0 (add) is stored into the value of resultPtr

    std::cout << "Addition: " << **doublePtr << std::endl; // Dereference twice to get the value

    delete resultPtr; // remove the pointer (no need to remove doublePtr?)

    return 0;
}