#include "RawPointer.h"
#include <iostream>

int main()
{
    // Declare the list of arrays
    int *arr = allocate_array(5);

    // Fill Arrawy
    fill_array(arr, 5);

    // Print out Arrays
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    // Deallocate the arrays
    deallocate_array(arr);
    return 0;
}