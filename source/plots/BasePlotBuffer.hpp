#ifndef BASE_PLOT_BUFFER_HPP
#define BASE_PLOT_BUFFER_HPP

#include <QVector>
#include <QPointF>

#include "Types.hpp"

class BasePlotBuffer
{
public:
    BasePlotBuffer(int             bufferSize,
                 QVector<QPointF>& buffer,
                 double            startFrequency,
                 double            frequencyStep);

    virtual ~BasePlotBuffer() {}

    virtual void ResetValues();
    virtual void UpdateFrequencies(const double startFreq, const double freqStep);
    virtual void UpdateValues() {}
    virtual double GetGlobalMax() {}

protected:
    QVector<QPointF>& m_buffer;
};

#endif // BASE_PLOT_BUFFER_HPP



