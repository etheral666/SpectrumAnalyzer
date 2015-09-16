#include "AbsData.hpp"

AbsData::AbsData(int               buffersSize,
                 c64*              rawData,
                 QVector<QPointF>& absOutput,
                 double            startFrequency,
                 double            frequencyStep)
    : m_rawData(rawData),
      m_absData(absOutput)
{
    m_absData.clear();
    m_absData.reserve(buffersSize);
    double frequency = startFrequency;
    for(int i = 0; i < buffersSize; ++i)
    {
        m_absData.push_back(QPointF(frequency, 0.0));
        frequency += frequencyStep;
    }
}

void AbsData::ResetValues()
{
    for(VecIterator it = m_absData.begin(); it != m_absData.end(); ++it)
    {
        it->setY(0.0);
    }
}

void AbsData::UpdateValues()
{
    for(int idx = 0; idx < m_absData.size(); ++idx)
        m_absData[idx].setY(std::abs(m_rawData[idx]));
}

void AbsData::UpdateFrequencies(const double startFreq, const double freqStep)
{
    double freqency = startFreq;
    for(VecIterator it = m_absData.begin(); it != m_absData.end(); ++it)
    {
        it->setX(freqency);
        freqency += freqStep;
    }
}

double AbsData::GetGlobalMax()
{
    double max = 0.0;
    for(VecIterator it = m_absData.begin(); it != m_absData.end(); ++it)
    {
        if(it->y() > max)
            max = it->y();
    }

    return max;
}

