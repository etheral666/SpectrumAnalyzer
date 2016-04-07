#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <complex>
#include <algorithm>

#include <QVector>
#include <QPointF>

#include "BasePlotBuffer.hpp"
#include "Types.hpp"

#define BUFFERS_SIZE 1024

using namespace testing;

class PlotBuffer : public BasePlotBuffer
{
public:
    PlotBuffer(int               bufferSize,
               QVector<QPointF>& buffer,
               double            startFrequency,
               double            frequencyStep)
        : BasePlotBuffer(bufferSize,
                         buffer,
                         startFrequency,
                         frequencyStep)
    {}

    // no implementations required, since tested are only BasePlotBuffer functions
    virtual void UpdateValues()
    {}

    virtual double GetGlobalMax()
    {
        return 0.f;
    }
};

class PlotBufferTest : public Test
{
public:
    PlotBufferTest()
        : startFrequency(1000.0),
          frequencyStep(500.0)
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, c64(1, 1));
        buffer.insert(buffer.end(), BUFFERS_SIZE, QPointF(1, 1));
        basePlotBuffer.reset(new PlotBuffer(BUFFERS_SIZE,
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

    c64                           rawData[BUFFERS_SIZE];
    QVector<QPointF>              buffer;
    boost::scoped_ptr<PlotBuffer> basePlotBuffer;
};

TEST_F(PlotBufferTest, ResetBuffer)
{
    for(VecIterator it = buffer.begin(); it != buffer.end(); ++it)
    {
        it->setY(5.0);
    }

    basePlotBuffer->ResetValues();
    CheckBuffer(0.0, startFrequency, frequencyStep);
}

TEST_F(PlotBufferTest, UpdateFrequencies)
{
    const double startFreq = 2 * startFrequency;
    const double freqStep  = 2 * frequencyStep;
    basePlotBuffer->UpdateFrequencies(startFreq, freqStep);
    const double refVal = 0.0;

    CheckBuffer(refVal, startFreq, freqStep);
}
