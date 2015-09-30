#ifndef FFTW_MOCK_HPP
#define FFTW_MOCK_HPP

#include "IFftw.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class FftwMock : public IFftw
{
public:
    MOCK_METHOD1(FftwMalloc, void*(std::size_t n));
    MOCK_METHOD1(FftwFree, void (void* p));
    MOCK_METHOD1(FftwExecute, void(const fftw_plan plan));
    MOCK_METHOD1(FftwDestroyPlan, void(fftw_plan plan));
    MOCK_METHOD5(FftwPlanDft1d, fftw_plan(int           n,
                                          fftw_complex* input,
                                          fftw_complex* output,
                                          int           sign,
                                          unsigned      flags));
};

#endif // FFTW_MOCK_HPP
