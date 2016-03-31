#include "SamplesAdapter.hpp"
#include "Types.hpp"

#include <stdint.h>
#include <complex>
#include <cstring>
#include <gtest/gtest.h>

TEST(SamplesAdapterTest, UInt8ToComplexFloat)
{
    const int32_t inputLength  = 260000;
    const int32_t outputLength = inputLength / 2;

    uint8_t inputBuffer[inputLength];
    c32     outBuffer[outputLength];

    std::memset(inputBuffer, 1, inputLength);
    std::memset(outBuffer, 0, sizeof(c32) * outputLength);

    UInt8ToCplxFloat(inputBuffer, outBuffer, inputLength);

    for(int32_t idx = 0; idx < outputLength; ++idx)
    {
        EXPECT_FLOAT_EQ(1.f, outBuffer[idx].real());
        EXPECT_FLOAT_EQ(1.f, outBuffer[idx].imag());
    }
}
