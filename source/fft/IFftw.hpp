#ifndef IFFTW_HPP
#define IFFTW_HPP

#include "fftw3.h"

class IFftw
{
public:
    virtual void*     FftwMalloc(size_t n) = 0;
    virtual void      FftwFree(void* p) = 0;
    virtual void      FftwExecute(const fftw_plan plan) = 0;
    virtual void      FftwDestroyPlan(fftw_plan plan) = 0;
    virtual fftw_plan FftwPlanDft1d(int n,
                                    fftw_complex* input,
                                    fftw_complex* output,
                                    int sign,
                                    unsigned flags) = 0;
};

#endif // IFFTW_HPP

