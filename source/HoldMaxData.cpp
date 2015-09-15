#include "HoldMaxData.hpp"

HoldMaxData::HoldMaxData(int bufferSize, c64* rawData, QVector<QPointF>& holdMaxBuffer)
    : m_rawData(rawData),
      m_holdMaxBuffer(holdMaxBuffer)
{
    m_holdMaxBuffer.clear();
    m_holdMaxBuffer.insert(m_holdMaxBuffer.end(), bufferSize, QPointF(0, 0));
}

void HoldMaxData::ResetValues()
{

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

}

double HoldMaxData::GetGlobalMax()
{

}

