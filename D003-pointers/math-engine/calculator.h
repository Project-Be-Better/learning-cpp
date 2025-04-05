#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator
{
private:
    int a, b;

public:
    // Constructor
    Calculator(int a, int b);

    // Typedef
    typedef int (*Operation)(int, int);

    // Method to apply operation
    int execute(Operation op);

    // Static function
    static int add(int, int);
    static int subtract(int, int);
    static int multiply(int, int);
    static int divide(int, int);
};

#endif // CALCULATOR_H