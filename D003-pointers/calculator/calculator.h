#ifndef CALCULATOR_H
#define CALCULATOR_H

using MathOp = int (*)(int, int);

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int execute(int a, int b, MathOp op);

#endif