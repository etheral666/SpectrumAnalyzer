#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <complex>
#include <algorithm>
#include <cmath>

#include <QVector>
#include <QPointF>

#include "PhaseBuffer.hpp"
#include "Types.hpp"

using namespace testing;

#define BUFFERS_SIZE 1024

class PhaseBufferTest : public Test
{
public:
    PhaseBufferTest()
        : startFrequency(1000.0),
          frequencyStep(500.0)
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, c64(0, 0));
        buffer.insert(buffer.end(), BUFFERS_SIZE, QPointF(1, 1));
        phaseBuffer.reset(new PhaseBuffer(BUFFERS_SIZE,
                                          rawData,
                                          buffer,
                                          startFrequency,
                                          frequencyStep));
        CheckBufferInitialization();
    }

    void CheckBufferInitialization()
    {
        double frequency = startFrequency;
        for(VecIterator it = buffer.begin(); it != buffer.end(); ++it)
        {
            ASSERT_DOUBLE_EQ(frequency, it->x());
            ASSERT_DOUBLE_EQ(0.0,       it->y());
            frequency += frequencyStep;
        }
    }

    void UpdatePhaseValues(c64 newValue)
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, newValue);
        phaseBuffer->UpdateValues();
    }

    void CheckBuffer(double refValue, double startFreq, double freqStep)
    {
        QPointF refPoint = QPointF(startFreq, refValue);
        for(VecIterator it = buffer.begin(); it != buffer.end(); ++it)
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
    QVector<QPointF>               buffer;
    boost::scoped_ptr<PhaseBuffer> phaseBuffer;
};

TEST_F(PhaseBufferTest, UpdatePhase)
{
    UpdatePhaseValues(c64(1.0, 1.0));
    const double refPhase = std::atan2(1.0, 1.0);

    CheckBuffer(refPhase, startFrequency, frequencyStep);
}

TEST_F(PhaseBufferTest, FindingGlobalMax)
{
    const int maxValIdx   = BUFFERS_SIZE / 2;
    rawData[maxValIdx]    = c64(-1.0, 0.0);
    const double maxPhase = 0.0; //maximum phase is irrelevant to the plot
    phaseBuffer->UpdateValues();

    EXPECT_DOUBLE_EQ(maxPhase, phaseBuffer->GetGlobalMax());
}
