#include "HoldMaxData.hpp"

HoldMaxData::HoldMaxData(int               bufferSize,
                         c64*              rawData,
                         QVector<QPointF>& holdMaxBuffer,
                         double            startFreq,
                         double            freqStep)
    : m_rawData(rawData),
      m_holdMaxBuffer(holdMaxBuffer)
{
    m_holdMaxBuffer.clear();
    m_holdMaxBuffer.reserve(bufferSize);
    double frequency = startFreq;
    for(int i = 0; i < bufferSize; ++i)
    {
        m_holdMaxBuffer.push_back(QPointF(frequency, 0.0));
        frequency += freqStep;
    }
}

void HoldMaxData::ResetValues()
{
    for(VecIterator it = m_holdMaxBuffer.begin(); it != m_holdMaxBuffer.end(); ++it)
    {
        it->setY(0.0);
    }
}

void HoldMaxData::UpdateValues()
{
    for(int idx = 0; idx < m_holdMaxBuffer.size(); ++idx)
    {
        const double rawAbs = std::abs(m_rawData[idx]);
        if(rawAbs > m_holdMaxBuffer[idx].y())
            m_holdMaxBuffer[idx].setY(rawAbs);
    }
}

void HoldMaxData::UpdateFrequencies(const double startFreq, const double freqStep)
{
    double frequency = startFreq;
    for(VecIterator it = m_holdMaxBuffer.begin(); it != m_holdMaxBuffer.end(); ++it)
    {
        it->setX(frequency);
        frequency += freqStep;
    }
}

double HoldMaxData::GetGlobalMax()
{
    double max = 0.0;
    for(VecIterator it = m_holdMaxBuffer.begin(); it != m_holdMaxBuffer.end(); ++it)
    {
        if(it->y() > max)
            max = it->y();
    }

    return max;
}

