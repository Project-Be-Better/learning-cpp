#include "ObjectLifecycle.h"
#include <iostream>

int main()
{
    std::cout << "\n=== MEMORY LIFECYCLE DEMONSTRATION ===\n"
              << std::endl;

    std::cout << "\n[1] STATIC ALLOCATION" << std::endl;
    createStatic();

    std::cout << "\n[2] AUTOMATIC ALLOCATION" << std::endl;
    createAutomatic();

    std::cout << "\n[3] HEAP ALLOCATION" << std::endl;
    createHeap();

    std::cout << "\n[4] TEMPORARY OBJECTS" << std::endl;
    createTemporary();

    std::cout << "\n=== PROGRAM ENDING ===\n"
              << std::endl;
    return 0;
}