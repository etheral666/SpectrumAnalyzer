#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <boost/smart_ptr.hpp>

#include "FftwWrapper.hpp"
#include "FftwWrapperMock.hpp"

using namespace testing;

class FftwWrapperTest : public Test
{
public:
    FftwWrapperTest()
        : inputBuffer(0),
          outputBuffer(0),
          fftSize(1024),
          fftSign(FFTW_FORWARD),
          fftwFlags(FFTW_MEASURE)
    {
        EXPECT_CALL(fftwMock, FftwMalloc(_)).Times(2);
        EXPECT_CALL(fftwMock, FftwPlanDft1d(_,_,_,_,_));
        fftWrapper.reset(new FftwWrapper(fftwMock,
                                         fftSize,
                                         inputBuffer,
                                         outputBuffer,
                                         fftSign,
                                         fftwFlags));
    }

    ~FftwWrapperTest()
    {
        EXPECT_CALL(fftwMock, FftwFree(_)).Times(2);
        EXPECT_CALL(fftwMock, FftwDestroyPlan(_));
    }

    void ExpectPlanChange()
    {
        EXPECT_CALL(fftwMock, FftwDestroyPlan(_));
        EXPECT_CALL(fftwMock, FftwFree(_)).Times(2);
        EXPECT_CALL(fftwMock, FftwMalloc(_)).Times(2);
        EXPECT_CALL(fftwMock, FftwPlanDft1d(fftSize, _, _, fftSign, fftwFlags));
    }

protected:
    StrictMock<FftwMock>           fftwMock;
    boost::scoped_ptr<FftwWrapper> fftWrapper;
    std::complex<double>*          inputBuffer;
    std::complex<double>*          outputBuffer;
    int                            fftSize;
    int                            fftSign;
    unsigned int                   fftwFlags;
};

TEST_F(FftwWrapperTest, ComputingFFT)
{
    EXPECT_CALL(fftwMock, FftwExecute(_));
    fftWrapper->ComputeFFT();
}

TEST_F(FftwWrapperTest, ChangingFftwPlan)
{
    ExpectPlanChange();
    fftWrapper->ChangeFftwParameters(fftSize, fftSign, fftwFlags);
}



