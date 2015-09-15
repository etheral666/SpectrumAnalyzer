#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <complex>
#include <algorithm>

#include <QVector>
#include <QPointF>

#include "AbsData.hpp"

#define BUFFERS_SIZE 1024

typedef std::complex<double> c64;
typedef QVector<QPointF>::Iterator QVecIterator;

using namespace testing;

class AbsPlotDataTests : public Test
{
public:
    AbsPlotDataTests()
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, c64(1, 1));
        absBuffer.insert(absBuffer.end(), BUFFERS_SIZE, QPointF(1, 1));
        absData.reset(new AbsData(BUFFERS_SIZE, rawData, absBuffer));

        CheckBufferInitialization();
    }

    void CheckBufferInitialization()
    {
        ASSERT_EQ(BUFFERS_SIZE, std::count(absBuffer.begin(), absBuffer.end(), QPointF(0, 0)));
    }

    void UpdateAbsValues(c64 newValue)
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, newValue);
        absData->UpdateValues();
    }

protected:
    c64                        rawData[BUFFERS_SIZE];
    QVector<QPointF>           absBuffer;
    boost::scoped_ptr<AbsData> absData;
};

TEST_F(AbsPlotDataTests, UpdateMagnitudeValues)
{
    UpdateAbsValues(c64(5, 5));
    const double referenceY = std::abs(c64(5, 5));
    for(QVecIterator it = absBuffer.begin(); it != absBuffer.end(); ++it)
    {
        EXPECT_DOUBLE_EQ(referenceY, it->y());
    }
}

TEST_F(AbsPlotDataTests, ResetMagnitudeValues)
{
    UpdateAbsValues(c64(5, 5));
    absData->ResetValues();
    const double referenceY = 0.0;
    for(QVecIterator it = absBuffer.begin(); it != absBuffer.end(); ++it)
    {
        EXPECT_DOUBLE_EQ(referenceY, it->y());
    }
}

TEST_F(AbsPlotDataTests, UpdateFrequencyValues)
{
    const double startFreq = 5000;
    const double freqStep  = 1000;
    absData->UpdateFrequencies(startFreq, freqStep);
    double expectedFreq = startFreq;
    for(int i = 0; i < BUFFERS_SIZE; ++i)
    {
        EXPECT_DOUBLE_EQ(expectedFreq, absBuffer[i].x());
        expectedFreq += freqStep;
    }
}

TEST_F(AbsPlotDataTests, FindGlobalMax)
{
    const int maxValueIdx  = BUFFERS_SIZE / 2;
    rawData[maxValueIdx]   = c64(100.0, 100.0);
    const double refMaxAbs = std::abs(rawData[maxValueIdx]);
    absData->UpdateValues();

    EXPECT_EQ(refMaxAbs, absData->GetGlobalMax());
}

