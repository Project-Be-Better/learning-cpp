#include <iostream>

int add(int a, int b)
{
    return a + b;
}

using MathOp = int (*)(int, int);

int execute(int a, int b, MathOp op)
{
    return op(a, b);
}

int main()
{
    MathOp addPtr = add;

    int rltAdd = execute(5, 40, addPtr);

    std::cout << "Result of add is: " << rltAdd << std::endl;
}