#ifndef GNSS_SIMULATOR_H
#define GNSS_SIMULATOR_H
#include <string>

class GNSSSimulator
{
public:
    void sayHello();
    std::string generateMockLocation();
};

#endif // GNSS_SIMULATOR_H