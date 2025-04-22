So today is something extra ordinary and I am surprised and heartfelt by the amount of humiliation I can go through. Anyways, All is well and we will be building the ground work for the Reloaded version of the Teletrack Sim application which will be an embedded simulation which incorporates the use of different tools and best practices that I am learning from my current role as an embedded C++ developer

## Tool Set

| Tool  | Description           |
| ----- | --------------------- |
| CMake | For Building          |
| Conan | Dependency Management |
| GTest | For Unit Testing      |

## Learnings

I learned on how to create a CMakeLists.txt and its various parameters. I also learned to write a bash script which will building and executing the project itself.

Build and artifacts and source code are seperated as well

Project is now bootstrappable

We have a set of modules that can be stacked and can be compiled individually, which is the industry practice as well. So in theory, we will be having learncpp.com theory lessons as well as work here

## Improvements

I need to add flags for the bash script so that I can run it in various modes like --build or --clean or --release
