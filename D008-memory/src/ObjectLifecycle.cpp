#include "ObjectLifecycle.h"
#include <iostream>

Tracker::Tracker(const char *name) : name_(name)
{
    std::cout << "[Constructor] " << name_ << std::endl;
};

Tracker::~Tracker()
{
    std::cout << "[Destructor] " << name_ << std::endl;
};

// Static allocation (global variable)
static Tracker staticTracker("Static");

void createStatic()
{
    // The staticTracker is already created at program start
    std::cout << "Static object already created" << std::endl;
}

void createAutomatic()
{
    // Automatic allocation (stack)
    Tracker automaticTracker("Automatic");
    std::cout << "Automatic object created on stack" << std::endl;
    // Will be automatically destroyed when function returns
}

void createHeap()
{
    // Dynamic allocation (heap)
    Tracker *heapTracker = new Tracker("Heap");
    std::cout << "Heap object created with new" << std::endl;

    // Must be manually deleted to avoid memory leaks
    delete heapTracker;
}

void createTemporary()
{
    // Temporary object
    std::cout << "Creating temporary object..." << std::endl;
    Tracker("Temporary"); // Temporary object with no name
    std::cout << "Temporary object created and destroyed" << std::endl;
}