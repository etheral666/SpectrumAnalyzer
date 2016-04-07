#ifndef ABS_BUFFER_HPP
#define ABS_BUFFER_HPP

#include <QVector>
#include <QPointF>

#include "BasePlotBuffer.hpp"
#include "Types.hpp"

class AbsBuffer : public BasePlotBuffer
{
public:
    AbsBuffer(int               bufferSize,
              c64*              rawData,
              QVector<QPointF>& buffer,
              double            startFrequency,
              double            frequencyStep);

    virtual void UpdateValues();
    virtual double GetGlobalMax();

private:
    c64* m_rawData;
};

#endif // ABS_BUFFER_HPP
