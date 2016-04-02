#ifndef FFTW_HPP
#define FFTW_HPP

#include "fftw3.h"

#include "IFftw.hpp"

class Fftw : public IFftw
{
public:
    virtual void* FftwMalloc(size_t n)
    {
        return fftw_malloc(n);
    }

    virtual void FftwFree(void* p)
    {
        fftw_free(p);
    }

    virtual void FftwExecute(const fftw_plan plan)
    {
        fftw_execute(plan);
    }

    virtual void FftwDestroyPlan(fftw_plan plan)
    {
        fftw_destroy_plan(plan);
    }

    virtual fftw_plan FftwPlanDft1d(int           n,
                                    fftw_complex* input,
                                    fftw_complex* output,
                                    int           sign,
                                    unsigned      flags)
    {
        return fftw_plan_dft_1d(n, input, output, sign, flags);
    }
};

#endif // FFTW_HPP

