#include "HackRfInterface.hpp"

#include <gtest/gtest.h>

using namespace testing;

class HackRfInterfaceTest : public Test
{

};

TEST(HackRfInterfaceTest, Initialization)
{
    HackRfInterface hackRf;
    EXPECT_EQ(HACKRF_SUCCESS, hackRf.GetStatus());
}
