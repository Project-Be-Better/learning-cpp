#include <iostream>

int main()
{
    int x = 10;
    int *ptr = &x; // pointer ptr has the address of x

    std::cout << "Value of x is   : " << x << std::endl;
    std::cout << "Address of x is : " << ptr << std::endl;
    std::cout << "Value of ptr is : " << *ptr << std::endl;
    std::cout << "Address of ptr is: " << &ptr << std::endl;
}