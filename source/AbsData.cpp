#include "AbsData.hpp"

AbsData::AbsData(int buffersSize, std::complex<double>* rawData, QVector<QPointF>& absOutput)
    : m_rawData(rawData),
      m_absData(absOutput)
{
   m_absData.clear();
   m_absData.insert(m_absData.end(), buffersSize, QPointF(0, 0));
}

void AbsData::ResetValues()
{
    const int size = m_absData.size();
    m_absData.clear();
    m_absData.insert(m_absData.end(), size, QPointF(0, 0));
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

