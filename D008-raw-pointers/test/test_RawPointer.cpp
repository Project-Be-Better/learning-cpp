#include <gtest/gtest.h>
#include "RawPointer.h"

TEST(PointerTest, AllocationAndValues)
{

    // Declare the list of arrays
    int *arr = allocate_array(5);

    // Fill Arrawy
    fill_array(arr, 5);

    // Print out Arrays
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(arr[i], i * 10);
    }

    deallocate_array(arr);
}