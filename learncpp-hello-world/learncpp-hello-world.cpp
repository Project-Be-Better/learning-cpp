// learncpp-hello-world.cpp : Defines the entry point for the application.
//

#include "learncpp-hello-world.h"
#include <iostream>

using namespace std;

int main()
{
	// STD::COUT 

	//Can include text 
	std::cout << "Hello World \n";

	// Can include numbers 
	std::cout << 4 << std::endl;	// Causes the cursor to move to the new line  

	// Print the valuye of variables
	int z{ 5 };						// Defines the integer 5
	std::cout << z;					// Prints the value to the console

	// STD CIN
	std::cout << "\nEnter two numbers seperated by space\n";

	int x{};
	int y{};

	std::cin >> x >> y;
	std::cout << "You have entered " << x
		<< " and " << y << "\n";
	return 0; 

}
