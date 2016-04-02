#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <stdint.h>

struct Const
{
    static const int32_t fftSize1024 = 1024;

    static const int32_t hackRfTransfersCount     = 4;
    static const int32_t hackRfTransferBufferSize = 262144;
};

#endif // CONSTANTS_HPP

