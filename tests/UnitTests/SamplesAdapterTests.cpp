#include "SamplesAdapter.hpp"

#include <stdint.h>
#include <complex>
#include <cstring>
#include <gtest/gtest.h>

//MATCHER_P4(CplxArrayEq, arg, ref, arrayLength, "")
//{
//    for(int32_t idx = 0; idx < arrayLength; ++idx)
//    {
//        if(arg[idx].real() != ref.real() || arg[idx].imag() != ref.imag())
//        {
//            *result_listener << "idx=" << idx << ":"
//                             << " arg.real=" << arg[idx].real() << " ref.real=" << ref.real()
//                             << " arg.imag=" << arg[idx].imag() << " ref.imag=" << ref.imag()
//                             << '\n';
//            return false;
//        }
//    }
//    return true;
//}

TEST(SamplesAdapterTest, UInt8ToComplexFloat)
{
    const int32_t inputLength  = 2000;
    const int32_t outputLength = inputLength / 2;

    uint8_t             inputBuffer[inputLength];
    std::complex<float> outBuffer[outputLength];

    std::memset(inputBuffer, 1, inputLength);
    std::memset(outBuffer, 0, sizeof(std::complex<float>) * outputLength);

    UInt8ToCplxFloat(inputBuffer, outBuffer, inputLength);

//    EXPECT_TRUE(CplxArrayEq(outBuffer, std::complex<float>(1.f, 1.f), outputLength));
    for(int32_t idx = 0; idx < outputLength; ++idx)
    {
        EXPECT_FLOAT_EQ(1.f, outBuffer[idx].real());
        EXPECT_FLOAT_EQ(1.f, outBuffer[idx].imag());
    }
}
