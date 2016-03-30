#include <cmath>

#include "PhaseBuffer.hpp"

PhaseBuffer::PhaseBuffer(int               bufferSize,
                         c64*              rawData,
                         QVector<QPointF>& buffer,
                         double            startFrequency,
                         double            frequencyStep)
    : BasePlotBuffer(bufferSize, buffer, startFrequency, frequencyStep),
      m_rawData(rawData)
{

}

void PhaseBuffer::UpdateValues()
{
    for(int idx = 0; idx < m_buffer.size(); ++idx)
    {
        const double phase = std::atan2(m_rawData[idx].imag(), m_rawData[idx].real());
        m_buffer[idx].setY(phase);
    }
}

double PhaseBuffer::GetGlobalMax()
{
    return 0.0; //maximum phase is irrelevant to the plot
}

