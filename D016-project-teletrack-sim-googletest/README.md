| **Concept**         | **Note**                                                                                                                                                                                             |
| ------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **IO library**      | The input/output library (IO library) is part of the C++ standard library that deals with basic input and output. We use this library to get input from the keyboard and output data to the console. |
| **std::cout**       | Allows us to send data to the console to be printed as text. <br>**Note**: `std::cout` is buffered.                                                                                                  |
| **std::endl**       | Outputs a newline and flushes the output buffer.                                                                                                                                                     |
| **std::cin**        | Stands for "character input" and is used to read input from the keyboard.                                                                                                                            |
| **<<** (Insertion)  | Insertion operator. Used with `std::cout` to send data **to** the console. Direction of data: `cout << data`.                                                                                        |
| **>>** (Extraction) | Extraction operator. Used with `std::cin` to read data **from** the user. Direction of data: `cin >> variable`.                                                                                      |

# Google Test

GoogleTest is Google’s C++ testing and mocking framework

1. https://google.github.io/googletest/
2. https://www.youtube.com/watch?v=pxJoVRfpRPE

# D016 20250425

So Project Teletrack Sim is my struggle and tribulations in understanding my new assignment and final frontier of programming languages as far as I am concerned, C++. I am doing this as a project to get two birds with one stone: Understanding the Project I am working on as a new Embedded Engineer and Face off with the long dreaded C++ and conquer it.

While at it, I want to do it in style and follow industry standards. So I am using the following:

1. CMake as the build tool
2. Conan for dependency Managment
3. GTest for dependency Management

There will be CI and even CD coming up soon and there will be more to come. Hopefully there is something to the deliberate practice that I have believed in my entire adult life

Live Long and Prosper<br>
BR<br>
Sree
