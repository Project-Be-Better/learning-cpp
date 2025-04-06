# Day 003: 2025_04_06 – Mastering Pointers and Function Pointers in C++

## 🧠 Concepts Covered

| Concept                 | Description                                                                                  |
| ----------------------- | -------------------------------------------------------------------------------------------- |
| `Pointer`               | A variable that stores the **memory address** of another variable                            |
| `&` (Address-of)        | Used to get the memory address of a variable (`int* p = &x;`)                                |
| `*` (Dereference)       | Used to access the value at a memory address (`int value = *p;`)                             |
| Function Pointer        | Stores the **address of a function** with a specific signature                               |
| Declaring Function Ptr  | `int (*func)(int, int);` means `func` can point to a function taking two ints, returning int |
| Calling Function Ptr    | `func(2, 3)` calls the function via the pointer                                              |
| `using` vs `typedef`    | `using MathOp = int (*)(int, int);` is the modern way to create function pointer aliases     |
| Assignment              | Always **right-to-left** in C++ (`MathOp ptr = add;`)                                        |
| Function Arguments Eval | From **left to right** since C++17                                                           |
| Can't nest named funcs  | C++ **does not allow function definitions inside functions** (like `execute()` in `main()`)  |

## 🧪 Practice Project: Function Pointer Calculator

**Folder Structure:**

```
day_03_calculator/
├── CMakeLists.txt
├── main.cpp
├── operations.h
├── operations.cpp
```

### operations.h

```cpp
#ifndef OPERATIONS_H
#define OPERATIONS_H

using MathOp = int (*)(int, int);

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int execute(int a, int b, MathOp op);

#endif
```

### operations.cpp

```cpp
#include "operations.h"

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int execute(int a, int b, MathOp op) {
    return op(a, b);
}
```

### main.cpp

```cpp
#include <iostream>
#include "operations.h"

int main() {
    int a = 20, b = 5;

    std::cout << "Add: " << execute(a, b, add) << std::endl;
    std::cout << "Subtract: " << execute(a, b, subtract) << std::endl;
    std::cout << "Multiply: " << execute(a, b, multiply) << std::endl;
    std::cout << "Divide: " << execute(a, b, divide) << std::endl;

    return 0;
}
```

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.10)
project(FunctionPointerCalculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator
    main.cpp
    operations.cpp
)
```

## ✅ Key Learnings

- Function pointers allow us to pass functions as arguments — like callbacks in Python
- `using` creates clean and readable pointer aliases
- Assignment is right to left (`ptr = &x;`)
- You **must declare function pointer types** in function parameter lists
- Pointer logic applies to memory layout, value access, and function-level behavior
- `execute(a, b, add)` is a great example of runtime behavior switching

## 🔜 Next Steps (Day 004 Preview)

- `int**` (pointer to pointer)
- Pointer and arrays
- Dynamic memory: `new`, `delete`
- `const` with pointers
- Function pointer arrays (dispatch table!)
