#ifndef PHASE_BUFFER_HPP
#define PHASE_BUFFER_HPP

#include <QVector>
#include <QPointF>

#include "BasePlotBuffer.hpp"
#include "Types.hpp"

class PhaseBuffer : public BasePlotBuffer
{
public:
    PhaseBuffer(int               bufferSize,
                c64*              rawData,
                QVector<QPointF>& buffer,
                double            startFrequency,
                double            frequencyStep);

    virtual void UpdateValues();
    virtual double GetGlobalMax();

private:
    c64* m_rawData;
};

#endif // PHASE_BUFFER_HPP
