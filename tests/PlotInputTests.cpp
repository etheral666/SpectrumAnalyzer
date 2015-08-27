#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>
#include <vector>
#include <complex>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "PlotInput.hpp"

#define BUFFERS_SIZE 1024

typedef std::complex<double> c64;

const c64 c0 = c64(0, 0);
const c64 c1 = c64(1, 1);

using namespace testing;

c64 GenerateRandomComplexInt()
{
    return c64(rand() % 100 - 50, rand() % 100 - 50);
}

class PlotInputTests : public Test
{
public:

    PlotInputTests()
    {
        std::fill(maxValuesBuffer, maxValuesBuffer + BUFFERS_SIZE, c1);
        std::fill(valuesBuffer, valuesBuffer + BUFFERS_SIZE, c1);
        plotInput.reset(new PlotInput(BUFFERS_SIZE, valuesBuffer, maxValuesBuffer));
        srand(time(0));
    }

    ~PlotInputTests()
    {}

    void UpdateMaxValues(c64 newValue)
    {
        std::fill(valuesBuffer, valuesBuffer + BUFFERS_SIZE, newValue);
        plotInput->UpdateMaxValues();
    }

protected:
    c64                          maxValuesBuffer[BUFFERS_SIZE];
    c64                          valuesBuffer[BUFFERS_SIZE];
    boost::scoped_ptr<PlotInput> plotInput;

};

TEST_F(PlotInputTests, NewPlotInputInitializesMaxValueBufffer)
{
    EXPECT_EQ(BUFFERS_SIZE, std::count(valuesBuffer,    valuesBuffer + BUFFERS_SIZE,    c1));
    EXPECT_EQ(BUFFERS_SIZE, std::count(maxValuesBuffer, maxValuesBuffer + BUFFERS_SIZE, c0));
}

TEST_F(PlotInputTests, FindingGlobalMaxAbs)
{
    std::generate(maxValuesBuffer, maxValuesBuffer + BUFFERS_SIZE, GenerateRandomComplexInt);
    c64 max = c64(100, 100);
    maxValuesBuffer[BUFFERS_SIZE - BUFFERS_SIZE/3] = max;
    double referenceMaxAbs = std::abs(max);
    EXPECT_DOUBLE_EQ(referenceMaxAbs, plotInput->GetMaxAbs());
}

TEST_F(PlotInputTests, UpdateMaxValues)
{
    UpdateMaxValues(c64(5, 5));
    EXPECT_EQ(BUFFERS_SIZE, std::count(maxValuesBuffer, maxValuesBuffer + BUFFERS_SIZE, c64(5, 5)));
}

TEST_F(PlotInputTests, ResetMaxValues)
{
    UpdateMaxValues(c64(5, 5));
    plotInput->ResetMaxValues();
    EXPECT_EQ(BUFFERS_SIZE, std::count(maxValuesBuffer, maxValuesBuffer + BUFFERS_SIZE, c0));
    double referenceMaxAbs = std::abs(c0);
    EXPECT_DOUBLE_EQ(referenceMaxAbs, plotInput->GetMaxAbs());
}

