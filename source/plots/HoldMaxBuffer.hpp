#ifndef HOLD_MAX_BUFFER_HPP
#define HOLD_MAX_BUFFER_HPP

#include <QVector>
#include <QPointF>

#include "BasePlotBuffer.hpp"
#include "Types.hpp"

class HoldMaxBuffer : public BasePlotBuffer
{
public:
    HoldMaxBuffer(int               bufferSize,
                  c64*              rawData,
                  QVector<QPointF>& buffer,
                  double            startFreq,
                  double            freqStep);

    virtual void UpdateValues();
    virtual double GetGlobalMax();
private:
    c64* m_rawData;
};

#endif // HOLD_MAX_BUFFER_HPP
