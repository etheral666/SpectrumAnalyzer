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
    {
        std::fill(rawData, rawData + BUFFERS_SIZE, std::complex<double>(0, 0));
        holdMaxBuffer.insert(holdMaxBuffer.end(), BUFFERS_SIZE, QPointF(1, 1));
        holdMaxData.reset(new HoldMaxData(BUFFERS_SIZE, rawData, holdMaxBuffer));
        CheckBufferInitialization();
    }

    void CheckBufferInitialization()
    {
        ASSERT_EQ(BUFFERS_SIZE, std::count(holdMaxBuffer.begin(), holdMaxBuffer.end(), QPointF(0, 0)));
    }

protected:
    c64                            rawData[BUFFERS_SIZE];
    QVector<QPointF>               holdMaxBuffer;
    boost::scoped_ptr<HoldMaxData> holdMaxData;
};

TEST_F(HoldMaxDataTests, HoldMaxUpdateOneValue)
{
    const int maxValueIdx = BUFFERS_SIZE / 2;
    rawData[maxValueIdx] = c64(100.0, 100.0);
    holdMaxData->UpdateValues();
    const double refMax = std::abs(rawData[maxValueIdx]);

    EXPECT_EQ(refMax, holdMaxBuffer[maxValueIdx].y());
}
