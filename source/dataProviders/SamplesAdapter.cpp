#include "SamplesAdapter.hpp"

void UInt8ToCplxFloat(uint8_t* input, c32* output, int32_t inputLength)
{
    int32_t outIdx = 0;
    for(int32_t inIdx = 1; inIdx < inputLength; ++outIdx)
    {
        output[outIdx].real() = static_cast<float>(input[inIdx-1]);
        output[outIdx].imag() = static_cast<float>(input[inIdx]);
        inIdx += 2;
    }
}
