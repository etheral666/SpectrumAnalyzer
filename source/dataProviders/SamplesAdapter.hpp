#ifndef SAMPLESADAPTER_HPP
#define SAMPLESADAPTER_HPP

#include "Types.hpp"

void UInt8ToCplxFloat(uint8_t* input, c32* output, int32_t inputLength);

void UInt8ToCplxDouble(uint8_t* input, c64* output, int32_t inputLength);

#endif // SAMPLESADAPTER_HPP
