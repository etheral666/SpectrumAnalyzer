#include "AbsBuffer.hpp"

AbsBuffer::AbsBuffer(int               bufferSize,
                     c64*              rawData,
                     QVector<QPointF>& buffer,
                     double            startFrequency,
                     double            frequencyStep)
    : BasePlotBuffer(bufferSize, buffer, startFrequency, frequencyStep),
      m_rawData(rawData)
{
}

void AbsBuffer::UpdateValues()
{
    for(int idx = 0; idx < m_buffer.size(); ++idx)
    {
        m_buffer[idx].setY(std::abs(m_rawData[idx]));
    }
}

double AbsBuffer::GetGlobalMax()
{
    double max = 0.0;
    for(VecIterator it = m_buffer.begin(); it != m_buffer.end(); ++it)
    {
        if(it->y() > max)
        {
            max = it->y();
        }
    }

    return max;
}

