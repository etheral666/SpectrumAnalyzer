#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <complex>
#include <algorithm>

#include <QVector>
#include <QPointF>

#include "AbsData.hpp"
#include "Types.hpp"

#define BUFFERS_SIZE 1024

using namespace testing;

class AbsPlotDataTests : public Test
{
public:
    AbsPlotDataTests()
        : startFrequency(1000.0),
          frequencyStep(500.0)
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, c64(1, 1));
        absBuffer.insert(absBuffer.end(), BUFFERS_SIZE, QPointF(1, 1));
        absData.reset(new AbsData(BUFFERS_SIZE,
                                  rawData,
                                  absBuffer,
                                  startFrequency,
                                  frequencyStep));

        CheckBufferInitialization();
    }

    void CheckBufferInitialization()
    {
        double frequency = startFrequency;
        for(VecIterator it = absBuffer.begin(); it != absBuffer.end(); ++it)
        {
            ASSERT_DOUBLE_EQ(frequency, it->x());
            ASSERT_DOUBLE_EQ(0.0,       it->y());
            frequency += frequencyStep;
        }
    }

    void UpdateAbsValues(c64 newValue)
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, newValue);
        absData->UpdateValues();
    }

    void CheckBuffer(double refValue, double startFreq, double freqStep)
    {
        QPointF refPoint = QPointF(startFreq, refValue);
        for(VecIterator it = absBuffer.begin(); it != absBuffer.end(); ++it)
        {
            EXPECT_DOUBLE_EQ(refPoint.x(), it->x());
            EXPECT_DOUBLE_EQ(refPoint.y(), it->y());
            refPoint.rx() += freqStep;
        }
    }

protected:
    const double startFrequency;
    const double frequencyStep;

    c64                        rawData[BUFFERS_SIZE];
    QVector<QPointF>           absBuffer;
    boost::scoped_ptr<AbsData> absData;
};

TEST_F(AbsPlotDataTests, UpdateMagnitudeValues)
{
    UpdateAbsValues(c64(5, 5));
    const double refVal = std::abs(c64(5, 5));

    CheckBuffer(refVal, startFrequency, frequencyStep);
}

TEST_F(AbsPlotDataTests, ResetMagnitudeValues)
{
    UpdateAbsValues(c64(5, 5));
    absData->ResetValues();
    const double refVal = 0.0;

    CheckBuffer(refVal, startFrequency, frequencyStep);
}

TEST_F(AbsPlotDataTests, UpdateFrequencyValues)
{
    const double startFreq = 2 * startFrequency;
    const double freqStep  = 2 * frequencyStep;
    absData->UpdateFrequencies(startFreq, freqStep);
    const double refVal = 0.0;

    CheckBuffer(refVal, startFreq, freqStep);
}

TEST_F(AbsPlotDataTests, FindGlobalMax)
{
    const int maxValueIdx  = BUFFERS_SIZE / 2;
    rawData[maxValueIdx]   = c64(100.0, 100.0);
    const double refMaxAbs = std::abs(rawData[maxValueIdx]);

    absData->UpdateValues();
    EXPECT_DOUBLE_EQ(refMaxAbs, absData->GetGlobalMax());
}

