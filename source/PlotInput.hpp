#ifndef PLOT_INPUT_HPP
#define PLOT_INPUT_HPP

#include <complex>

class PlotInput
{
private:
    typedef std::complex<double> c64;

public:
    PlotInput(int buffersSize, c64* valuesBuffer, c64* maxValuesBuffer);

    double GetMaxAbs();
    void UpdateMaxValues();
    void ResetMaxValues();

private:
    int  m_buffersSize;
    int  m_maxValueIdx;
    c64* m_values;
    c64* m_maxValues;
};

#endif // PLOT_INPUT_HPP
