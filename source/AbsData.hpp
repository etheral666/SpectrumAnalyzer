#ifndef ABS_DATA_HPP
#define ABS_DATA_HPP

#include "IBasePlotData.hpp"
#include "Types.hpp"

#include <QVector>
#include <QPointF>

#include <complex>

class AbsData : public IBasePlotData
{
public:
    AbsData(int               buffersSize,
            c64*              rawData,
            QVector<QPointF>& absOutput,
            double            startFrequency,
            double            frequencyStep);

    virtual void ResetValues();
    virtual void UpdateValues();
    virtual void UpdateFrequencies(const double startFreq, const double freqStep);
    virtual double GetGlobalMax();

private:
    std::complex<double>* m_rawData;
    QVector<QPointF>&     m_absData;
};

#endif // ABS_DATA_HPP
