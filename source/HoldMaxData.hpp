#ifndef HOLD_MAX_DATA_HPP
#define HOLD_MAX_DATA_HPP

#include "IBasePlotData.hpp"
#include "Types.hpp"

#include <QVector>
#include <QPointF>

#include <complex>

class HoldMaxData : public IBasePlotData
{
public:
    HoldMaxData(int bufferSize, c64* rawData, QVector<QPointF>& holdMaxBuffer);

    virtual void ResetValues();
    virtual void UpdateValues();
    virtual void UpdateFrequencies(const double startFreq, const double freqStep);
    virtual double GetGlobalMax();
private:
    c64*              m_rawData;
    QVector<QPointF>& m_holdMaxBuffer;
};

#endif // HOLD_MAX_DATA_HPP
