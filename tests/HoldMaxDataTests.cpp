#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <complex>
#include <algorithm>

#include <QVector>
#include <QPointF>

#include "HoldMaxData.hpp"
#include "Types.hpp"

using namespace testing;

#define BUFFERS_SIZE 1024

class HoldMaxDataTests : public Test
{
public:
    HoldMaxDataTests()
        : startFrequency(1000.0),
          frequencyStep(500.0)
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, c64(0, 0));
        holdMaxBuffer.insert(holdMaxBuffer.end(), BUFFERS_SIZE, QPointF(1, 1));
        holdMaxData.reset(new HoldMaxData(BUFFERS_SIZE,
                                          rawData,
                                          holdMaxBuffer,
                                          startFrequency,
                                          frequencyStep));
        CheckBufferInitialization();
    }

    void CheckBufferInitialization()
    {
        double frequency = startFrequency;
        for(VecIterator it = holdMaxBuffer.begin(); it != holdMaxBuffer.end(); ++it)
        {
            ASSERT_DOUBLE_EQ(frequency, it->x());
            ASSERT_DOUBLE_EQ(0.0,       it->y());
            frequency += frequencyStep;
        }
    }

    void UpdateHoldMaxValues(c64 newValue)
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, newValue);
        holdMaxData->UpdateValues();
    }

    void CheckBuffer(double refValue, double startFreq, double freqStep)
    {
        QPointF refPoint = QPointF(startFreq, refValue);
        for(VecIterator it = holdMaxBuffer.begin(); it != holdMaxBuffer.end(); ++it)
        {
            EXPECT_DOUBLE_EQ(refPoint.x(), it->x());
            EXPECT_DOUBLE_EQ(refPoint.y(), it->y());
            refPoint.rx() += freqStep;
        }
    }

protected:
    const double startFrequency;
    const double frequencyStep;

    c64                            rawData[BUFFERS_SIZE];
    QVector<QPointF>               holdMaxBuffer;
    boost::scoped_ptr<HoldMaxData> holdMaxData;
};

TEST_F(HoldMaxDataTests, HoldMaxUpdateOneValue)
{
    const int maxValueIdx = BUFFERS_SIZE / 2;
    rawData[maxValueIdx] = c64(100.0, 100.0);
    holdMaxData->UpdateValues();
    QPointF refPoint = QPointF(startFrequency, 0.0);

    for(int idx = 0; idx < BUFFERS_SIZE; ++idx)
    {
        if(idx != maxValueIdx)
        {
            EXPECT_DOUBLE_EQ(refPoint.x(), holdMaxBuffer[idx].x());
            EXPECT_DOUBLE_EQ(refPoint.y(), holdMaxBuffer[idx].y());
        }
        refPoint.rx() += frequencyStep;
    }

    refPoint = QPointF(startFrequency + maxValueIdx * frequencyStep,
                       std::abs(rawData[maxValueIdx]));
    EXPECT_DOUBLE_EQ(refPoint.x(), holdMaxBuffer[maxValueIdx].x());
    EXPECT_DOUBLE_EQ(refPoint.y(), holdMaxBuffer[maxValueIdx].y());

}

TEST_F(HoldMaxDataTests, HoldMaxUpdateAllValues)
{
    const c64 maxSample = c64(100.0, 100.0);
    std::fill(rawData, rawData + BUFFERS_SIZE, maxSample);
    const double refMax = std::abs(maxSample);

    holdMaxData->UpdateValues();
    CheckBuffer(refMax, startFrequency, frequencyStep);
}

TEST_F(HoldMaxDataTests, ResetMaxValues)
{
    UpdateHoldMaxValues(c64(5, 5));
    const double refValue = 0.0;

    holdMaxData->ResetValues();
    CheckBuffer(refValue, startFrequency, frequencyStep);
}

TEST_F(HoldMaxDataTests, UpdateFrequencies)
{
    const double refValue  = 0.0;
    const double startFreq = 2 * startFrequency;
    const double freqStep  = 2 * frequencyStep;

    holdMaxData->UpdateFrequencies(startFreq, freqStep);
    CheckBuffer(refValue, startFreq, freqStep);
}

TEST_F(HoldMaxDataTests, FindingGlobalMax)
{
    const c64 maxSample       = c64(100.0, 100.0);
    rawData[BUFFERS_SIZE / 2] = maxSample;
    const double refMax       = std::abs(maxSample);

    holdMaxData->UpdateValues();
    EXPECT_DOUBLE_EQ(refMax, holdMaxData->GetGlobalMax());
}
