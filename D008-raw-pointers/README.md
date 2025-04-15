
## 🧠 Day 008 – Raw Pointers in C++

Raw pointers are a fundamental construct in C++ that enable direct manipulation of memory. They are central to systems programming but must be used with care due to the risks of memory mismanagement.


### 🧾 Key Concepts

| **Concept**                 | **Description** |
|----------------------------|-----------------|
| **Pointer Declaration**    | A pointer is a variable that stores the **address** of another variable. <br>Example: `int* ptr = &x;` |
| **Dereferencing (`*`)**    | Accesses the **value at the memory location** the pointer refers to. <br>`*ptr = 5;` changes the value at the address held by `ptr`. |
| **Address-of (`&`)**       | Returns the memory address of a variable. <br>Example: `&value` returns the location of `value`. |
| **Dynamic Allocation**     | Using `new` and `delete` allows allocation of memory on the heap at runtime. <br>`int* ptr = new int;` |
| **Array Allocation**       | Heap arrays are created with `new[]` and freed with `delete[]`. <br>`int* arr = new int[5]; delete[] arr;` |
| **Pointer Arithmetic**     | Operations like `ptr + i` move the pointer `i` elements forward (based on data type size). |
| **Dangling Pointers**      | Occur when memory is freed but the pointer still holds the old address. Accessing this is undefined behavior. |
| **`nullptr`**              | Use `nullptr` (not `NULL`) to represent a null pointer in C++11+. Safer and type-aware. |
| **Memory Safety**          | Manual memory management requires discipline to avoid memory leaks, dangling pointers, and double deletes. |
| **Smart Pointers**         | `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr` offer safer alternatives by managing memory automatically. |


## 📏 Array Size Computation

### ✅ Compile-Time Arrays (Stack Allocation)
```cpp
int arr[] = {1, 2, 3, 4, 5};
int length = sizeof(arr) / sizeof(arr[0]);  // ✅ returns 5
```

| Term | Meaning |
|------|---------|
| `sizeof(arr)` | Total bytes of array (e.g., 5×4 = 20 bytes for 5 ints) |
| `sizeof(arr[0])` | Size of one element (4 bytes for int) |
| `length` | Total elements = total size / element size |

### ❌ Heap-Allocated Arrays
```cpp
int* arr = new int[5];
int length = sizeof(arr) / sizeof(arr[0]);  // ❌ returns 1 or 2 (pointer size), not array length
```

You must track the size manually:
```cpp
int size = 5;
```


## 🆚 Raw Pointers vs Smart Pointers

| Feature             | **Raw Pointers** | **Smart Pointers (`unique_ptr`, `shared_ptr`)** |
|---------------------|------------------|--------------------------------------------------|
| Ownership tracking  | ❌ Manual         | ✅ Automatic (RAII)                              |
| Memory leaks        | ⚠️ Likely         | ✅ Prevented                                     |
| Null safety         | ❌ `NULL`, unsafe | ✅ `nullptr`, safe                               |
| Copy semantics      | ✅ Allowed freely | ⚠️ Limited (`unique_ptr` is move-only)          |
| Use in containers   | ❌ Manual cleanup | ✅ Works seamlessly                              |
| Performance         | ✅ Faster (bare-bones) | ⚠️ Slight overhead due to reference counting or deleters |


## 🧼 Best Practices with Raw Pointers

| Practice                        | Why it matters |
|---------------------------------|----------------|
| Always pair `new` with `delete` | Prevents memory leaks |
| Use `delete[]` for arrays       | `delete` only frees one object |
| Set pointer to `nullptr` after deletion | Avoids use-after-free (dangling pointers) |
| Avoid pointer arithmetic unless necessary | Safer alternatives exist (`std::vector`, `std::array`) |
| Prefer smart pointers when ownership semantics are needed | Modern and safer idiom in C++11+ |


## 🧪 Practice Code Pattern

```cpp
int* arr = new int[5];

for (int i = 0; i < 5; ++i)
    arr[i] = i * 10;

for (int i = 0; i < 5; ++i)
    std::cout << "arr[" << i << "] = " << arr[i] << "\n";

delete[] arr;
arr = nullptr;  // ✅ Prevents future access
```


## 🧪 Suggested Exercises

1. Implement a dynamic array allocation + deletion with `new[]` and `delete[]`.
2. Write a function that takes a pointer and prints values using pointer arithmetic.
3. Compare the behavior of raw pointers and `std::unique_ptr` for the same task.
4. Use tools like **Valgrind**, **AddressSanitizer**, or **GDB** to explore memory layout and leaks.


## 🔁 Real-World Use Cases

| Use Case                     | Why Pointers?                      |
|------------------------------|------------------------------------|
| Embedded Systems / Drivers   | Fine-grained control over memory   |
| Game Engines                 | Performance-critical asset handling|
| OS Kernel / Device Drivers   | Manual resource control            |
| Dynamic Plugin Loaders       | Late-binding via function pointers |


## 📌 Final Notes

- Raw pointers are powerful but risky. Mastering them gives you deep insight into how memory and execution work in C++.
- For safety and maintainability, always consider modern constructs like smart pointers or containers unless raw pointers are required for performance or control.
