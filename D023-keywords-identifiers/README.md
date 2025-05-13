# Keywords and naming identifiers

> Summary <br>
> Code is read more often that written

| Concept        | Note                                                        |
| -------------- | ----------------------------------------------------------- |
| [[camelCase]]  | camelCase, can be used for functions and variables or both  |
| [[snake_case]] | snake_case, can be used for functions and variables or both |
|                |                                                             |

#### Note

- use [[camelCase]] or [[snake_case]] for functions
- Do not use the reserved keywords in C++
- It cannot have space in between and must start with a letter or an underscore
- Identifier names that start with a capital letter are typically used for user-defined types
- underScored identifiers should not be defined in a global scope

List of all reserved keywords

```

Here is a list of all the C++ keywords (through C++23):

-   alignas
-   alignof
-   and
-   and\_eq
-   asm
-   auto
-   bitand
-   bitor
-   bool
-   break
-   case
-   catch
-   char
-   char8\_t (since C++20)
-   char16\_t
-   char32\_t
-   class
-   compl
-   concept (since C++20)
-   const
-   consteval (since C++20)
-   constexpr
-   constinit (since C++20)
-   const\_cast
-   continue
-   co\_await (since C++20)
-   co\_return (since C++20)
-   co\_yield (since C++20)
-   decltype
-   default
-   delete
-   do
-   double
-   dynamic\_cast
-   else
-   enum
-   explicit
-   export
-   extern
-   false
-   float
-   for
-   friend
-   goto
-   if
-   inline
-   int
-   long
-   mutable
-   namespace
-   new
-   noexcept
-   not
-   not\_eq
-   nullptr
-   operator
-   or
-   or\_eq
-   private
-   protected
-   public
-   register
-   reinterpret\_cast
-   requires (since C++20)
-   return
-   short
-   signed
-   sizeof
-   static
-   static\_assert
-   static\_cast
-   struct
-   switch
-   template
-   this
-   thread\_local
-   throw
-   true
-   try
-   typedef
-   typeid
-   typename
-   union
-   unsigned
-   using
-   virtual
-   void
-   volatile
-   wchar\_t
-   while
-   xor
-   xor\_eq
```

# Whitespace and basic formatting

| Concept          | Note                                                                                                                                              |
| ---------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| [[Whitespace]]   | Whitespace is a term that refers to characters that are used for formatting purposes. In C++, this refers primarily to spaces, tabs, and newlines |
| [[Preprocessor]] |                                                                                                                                                   |

#### Note

##### Some language elements must be whitespace separated

The syntax of the language requires that some elements are separated by whitespace. This mostly occurs when two keywords or identifiers must be placed consecutively, so the compiler can tell them apart.

```cpp
int x; // int and x must be whitespace separated

int main(); // int and main must be whitespace separated

#include <iostream> // Must be placed on separate lines
#include <string>
```

##### Quoted space takes the amount of whitespace literally

```cpp
std::cout << "Hello world!";  // These are not the same
std::cout << "Hello                 world!";
```

##### Using whitespace to format code

Whitespaces can be used to enhance readability

```cpp
#include <iostream>
int main(){std::cout<<"Hello world";return 0;}

// Readable code
#include <iostream>
int main() {
	std::cout << "Hello world";
	return 0;
}
```

##### Basic Formatting

- C++ does not enforce formatting. So C++ can eb considered a whitespace independent language

1. We can use Tabs or Spaces for indentation
   Developers who prefer spaces tend to do so because it ensures that code is precisely aligned as intended regardless of which editor or settings are used. Proponents of using tabs wonder why you wouldn’t use the character designed to do indentation for indentation, especially as you can set the width to whatever your personal preference is
2. The styles of function

```c++
// we can use this
int main() {
    // statements here
}

// Or this (we will be using this)
int main()
{
    std::cout << "Hello world!\n"; // tabbed in one tab (4 spaces)
    std::cout << "Nice to meet you.\n"; // tabbed in one tab (4 spaces)
}
```

3. Each statement within curly braces should start one tab in from the opening brace of the function it belongs to

```c++
int main()
{
    std::cout << "Hello world!\n"; // tabbed in one tab (4 spaces)
    std::cout << "Nice to meet you.\n"; // tabbed in one tab (4 spaces)
}
```

4. Lines should not be too long. Typically, 80 characters has been the de facto standard for the maximum length a line should be. If a line is going to be longer, it should be split (at a reasonable spot) into multiple lines
5. If a long line is split with an operator (eg. << or +), the operator should be placed at the beginning of the next line, not the end of the current line

```c++
std::cout << 3 + 4
    + 5 + 6
    * 7 * 8;
```

6. Use whitespace to make your code easier to read by aligning values or comments or adding spacing between blocks of code.

```c++
cost = 57;
pricePerItem = 24;
value = 5;
numberOfItems = 17;

// vs
cost          = 57;
pricePerItem  = 24;
value         = 5;
numberOfItems = 17;
```

##### Automatic Formatting

##### Style Guides

A **style guide** is a concise, opinionated document containing (sometimes arbitrary) programming conventions, formatting guidelines, and best practices. The goal of a style guide is to ensure that all developers on a project are programming in a consistent manner

Some commonly referenced C++ style guides include:

- [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), maintained by Bjarne Stroustrup and Herb Sutter.
- [Google](https://google.github.io/styleguide/cppguide.html).
- [LLVM](https://llvm.org/docs/CodingStandards.html)
- [GCC/GNU](https://gcc.gnu.org/codingconventions.html)
