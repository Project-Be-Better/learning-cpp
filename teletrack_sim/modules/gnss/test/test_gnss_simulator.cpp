#include <gtest/gtest.h>
#include "gnss_simulator.h"

TEST(GnssSimulatorTest, GeneratesNonEmptyLocation)
{
    GNSSSimulator sim;
    std::string loc = sim.generateMockLocation();
    ASSERT_FALSE(loc.empty());
    ASSERT_NE(loc.find("latitude"), std::string::npos);
    ASSERT_NE(loc.find("longitude"), std::string::npos);
}
