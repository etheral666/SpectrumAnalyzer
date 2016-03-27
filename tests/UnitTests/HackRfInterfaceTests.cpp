#include "HackRfInterface.hpp"

#include <gtest/gtest.h>

#include <cstring>
#include <iostream>

using namespace testing;

class HackRfInterfaceTest : public Test
{
public:
    HackRfInterfaceTest()
    {
        CheckInitialization();
    }

    void CheckInitialization()
    {
        ASSERT_EQ(Connected, m_hackRf.CheckState()) << m_hackRf.GetLastErrorDescription();
    }

protected:
    HackRfInterface m_hackRf;
};

TEST_F(HackRfInterfaceTest, StreamingStartingAndStopping)
{
    ASSERT_EQ(Connected, m_hackRf.CheckState()) << m_hackRf.GetLastErrorDescription();

    m_hackRf.StartReceiving();
    EXPECT_EQ(Receiving, m_hackRf.CheckState()) << m_hackRf.GetLastErrorDescription();

    m_hackRf.StopReceiving();
    EXPECT_EQ(Connected, m_hackRf.CheckState()) << m_hackRf.GetLastErrorDescription();
}
