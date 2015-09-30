#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <string>
#include <algorithm>
#include <fstream>

#include "FakeAntenna.hpp"
#include "Types.hpp"
#include "Constants.hpp"

using namespace testing;

class FakeAntennaTest : public Test
{
public:
    FakeAntennaTest()
    {
        std::fill(rawSamplesBuffer, rawSamplesBuffer + Const::fftSize1024, 0.0);
    }

    void SetInputFile(const std::string& inputFile)
    {
        ASSERT_EQ(true, DoesFileExists(inputFile));

        fakeAntenna.reset(new FakeAntenna(inputFile, rawSamplesBuffer));
    }

    bool DoesFileExists(const std::string& filePath)
    {
        std::fstream file(filePath.c_str());
        return file.good();
    }

protected:
    double                         rawSamplesBuffer[Const::fftSize1024];
    boost::scoped_ptr<FakeAntenna> fakeAntenna;
};

TEST_F(FakeAntennaTest, SimpleInputFile)
{
    const std::string filePath = "D:\\projekty\\!QT\\SpectrumAnalyzer\\tests\\UnitTests\\Vectors\\onesDouble.dat";
    SetInputFile(filePath);
    const double refValue = 1.0;

    fakeAntenna->ProcessNextSamplesBlock();

    EXPECT_EQ(Const::fftSize1024, std::count(rawSamplesBuffer,
                                             rawSamplesBuffer + Const::fftSize1024,
                                             refValue));
}

