#include "HackRfInterface.hpp"

#include <gtest/gtest.h>

#include <stdint.h>
#include <algorithm>

using namespace testing;

int TestReceiveCallback(hackrf_transfer* transfer)
{
    int32_t result = std::count(&transfer->buffer[0], &transfer->buffer[transfer->valid_length], 0);
    EXPECT_NE(transfer->valid_length, result); // assert, that zeroed buffer means no transmission
    return 0;
}

class HackRfInterfaceTest : public Test
{
public:
    HackRfInterfaceTest()
        : m_device(NULL),
          m_hackRf(&m_device, TestReceiveCallback)
    {
        CheckInitialization();
    }

    void CheckInitialization()
    {
        ASSERT_EQ(Connected, m_hackRf.CheckState()) << m_hackRf.GetLastErrorDescription();
    }

protected:
    hackrf_device*  m_device;
    HackRfInterface m_hackRf;
};

TEST_F(HackRfInterfaceTest, StartAndStopStreaming)
{
    ASSERT_EQ(Connected, m_hackRf.CheckState()) << m_hackRf.GetLastErrorDescription();

    m_hackRf.StartReceiving();
    EXPECT_EQ(Receiving, m_hackRf.CheckState()) << m_hackRf.GetLastErrorDescription();

    m_hackRf.StopReceiving();
    EXPECT_EQ(Connected, m_hackRf.CheckState()) << m_hackRf.GetLastErrorDescription();
}

TEST_F(HackRfInterfaceTest, StreamingData)
{
    m_hackRf.StartReceiving();
    m_hackRf.StopReceiving();
}
