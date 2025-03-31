# 100 Days of C++ – Learning Summary (Up to Day 2)

## Day 2 – Include Guards, MISRA Practices & Calculator Class

### Concepts Covered

- Demonstrated compiler error by including a header with function definitions twice
- Fixed the error using include guards and declaration-only headers (MISRA-compliant)
- Created a clean `utils.h` and `utils.cpp` using namespace `svt`
- Built a full `Calculator` class with `add`, `subtract`, `multiply`, and `divide` methods
- Implemented safe division (checking for divide-by-zero)
- Updated the Bash script to support clean builds using `command.bash clean`
- Discussed how access specifiers (`public:`, `private:`) work in C++

### Files Created

- `include-guard-demo/broken/utils.h` and `main.cpp`
- `include-guard-demo/fixed/utils.h`, `utils.cpp`, and `main.cpp`
- `calculator/calculator.h`, `calculator.cpp`, `main.cpp`, `CMakeLists.txt`, and `command.bash`

### Key Learnings

- Redefining a function in headers causes a compiler error
- MISRA does not allow function definitions in headers
- `namespace` helps prevent symbol clashes and is required in your codebase
- `public:` and `private:` are access control keywords declared in the header file only
- CMake builds incrementally unless cleaned manually
- Constructor and destructor logic is written in `.cpp`, not in the header

### Coming Up in Day 3

- Add a constructor and destructor to `Calculator`
- Log object creation and destruction
- Understand object lifetime (stack vs heap)
- Prepare for GoogleTest setup
