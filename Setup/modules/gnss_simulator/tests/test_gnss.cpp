#include <gtest/gtest.h>
#include "gnss.h"

using gnss::GNSS;

TEST(GNSS_Default_Constuctor, Starts_At_Origin)
{
    GNSS gnss;
    EXPECT_DOUBLE_EQ(gnss.latitude(), 0.0);
    EXPECT_DOUBLE_EQ(gnss.latitude(), 0.0);
};

TEST(GNSS_Parametrized_Contructor, Contructor_with_Non_Default_values)
{
    GNSS gnss(10.0, 11.0);
    EXPECT_DOUBLE_EQ(gnss.latitude(), 10.0);
    EXPECT_DOUBLE_EQ(gnss.longitude(), 11.0);
}

TEST(GNSS_Moves_By_Delta, Moves_By_Delta)
{
    GNSS gnss(10.0, 11.0);
    gnss.simulate();
    EXPECT_DOUBLE_EQ(gnss.latitude(), 10.0001);
    EXPECT_DOUBLE_EQ(gnss.longitude(), 11.0001);
}