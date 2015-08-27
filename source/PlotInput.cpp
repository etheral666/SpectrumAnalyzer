#include "PlotInput.hpp"

#include <cmath>

double PlotInput::GetMaxAbs()
{
    m_maxValueIdx = 0;
    for(int i = 0; i < m_buffersSize; ++i)
    {
        if(std::abs(m_maxValues[i]) > std::abs(m_maxValues[m_maxValueIdx]))
            m_maxValueIdx = i;
    }
    return std::abs(m_maxValues[m_maxValueIdx]);
}

void PlotInput::UpdateMaxValues()
{
    for(int idx = 0; idx < m_buffersSize; ++idx)
    {
        if(std::abs(m_values[idx]) > std::abs(m_maxValues[idx]))
        {
            m_maxValues[idx] = m_values[idx];
        }
    }
}

void PlotInput::ResetMaxValues()
{
    m_maxValueIdx = 0;
    std::fill(m_maxValues, m_maxValues + m_buffersSize, c64(0, 0));
}
