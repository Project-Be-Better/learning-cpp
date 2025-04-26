#include <iostream>
#include "gnss.h"

int main()
{
    gnss::GNSS gnss;

    std::cout << "\nBefore Simulate: " << "\n"
              << ">>> latitude: " << gnss.latitude() << "\n"
              << ">>> longitude: " << gnss.longitude() << "\n";

    gnss.simulate();

    std::cout
        << "\nAfter Simulate: " << "\n"
        << ">>> latitude: " << gnss.latitude() << "\n"
        << ">>> longitude: " << gnss.longitude() << "\n";

    return 0;
}