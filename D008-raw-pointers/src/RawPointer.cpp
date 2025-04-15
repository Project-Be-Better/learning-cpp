#include "RawPointer.h"
#include <iostream>

int *allocate_array(int size)
{
    return new int[size];
};

void fill_array(int *arr, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = i * 10;
    }
};

void deallocate_array(int *arr)
{
    delete arr;
};
