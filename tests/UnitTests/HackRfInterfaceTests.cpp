#include "HackRfInterface.hpp"

#include <gtest/gtest.h>

#include <stdint.h>
#include <algorithm>

using namespace testing;

extern hackrf_transfer g_lastTransferInfo;

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
    {
        m_hackRf = HackRfInterface::GetInstance();
        CheckInitialization();
    }

    void CheckInitialization()
    {
        ASSERT_EQ(Connected, m_hackRf->CheckState()) << m_hackRf->GetLastErrorDescription();
    }

protected:
    HackRfInterface* m_hackRf;
};

TEST_F(HackRfInterfaceTest, StartAndStopStreaming)
{
    ASSERT_EQ(Connected, m_hackRf->CheckState()) << m_hackRf->GetLastErrorDescription();

    m_hackRf->ReceiveNextFrame();
    EXPECT_EQ(Receiving, m_hackRf->CheckState()) << m_hackRf->GetLastErrorDescription();
    m_hackRf->WaitForNextFrame();
    EXPECT_EQ(Connected, m_hackRf->CheckState()) << m_hackRf->GetLastErrorDescription();
}

