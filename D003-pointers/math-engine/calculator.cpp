#include "calculator.h"
#include <iostream>

Calculator::Calculator(int a, int b) : a(a), b(b) {}

int Calculator::execute(Operation op) { return op(a, b); };

int Calculator::add(int x, int y) { return x + y; }
int Calculator::subtract(int x, int y) { return x - y; }
int Calculator::multiply(int x, int y) { return x * y; }
int Calculator::divide(int x, int y) { return (y != 0) ? x / y : 0; }