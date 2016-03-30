#include "HoldMaxBuffer.hpp"

HoldMaxBuffer::HoldMaxBuffer(int               bufferSize,
                             c64*              rawData,
                             QVector<QPointF>& buffer,
                             double            startFreq,
                             double            freqStep)
    : BasePlotBuffer(bufferSize, buffer, startFreq, freqStep),
      m_rawData(rawData)
{
}

void HoldMaxBuffer::UpdateValues()
{
    for(int idx = 0; idx < m_buffer.size(); ++idx)
    {
        const double rawAbs = std::abs(m_rawData[idx]);
        if(rawAbs > m_buffer[idx].y())
            m_buffer[idx].setY(rawAbs);
    }
}

double HoldMaxBuffer::GetGlobalMax()
{
    double max = 0.0;
    for(VecIterator it = m_buffer.begin(); it != m_buffer.end(); ++it)
    {
        if(it->y() > max)
            max = it->y();
    }

    return max;
}

