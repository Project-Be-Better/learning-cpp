#include "gnss_simulator.h"
#include <iostream>

void GNSSSimulator::sayHello()
{
    std::cout << "[GNSS]: Hello from GNSS Simulator!" << std::endl;
};

std::string GNSSSimulator::generateMockLocation()
{
    return R"({"latitude":1.3521,"longitude":103.8198})";
}