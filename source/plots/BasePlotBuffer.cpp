#include "BasePlotBuffer.hpp"
#include <iostream>

BasePlotBuffer::BasePlotBuffer(int               bufferSize,
                               QVector<QPointF>& buffer,
                               double            startFrequency,
                               double            frequencyStep)
    : m_buffer(buffer)
{
    m_buffer.clear();
    m_buffer.reserve(bufferSize);
    double frequency = startFrequency;
    for(int idx = 0; idx < bufferSize; ++idx)
    {
        m_buffer.push_back(QPointF(frequency, 0.0));
        frequency += frequencyStep;
    }
}

void BasePlotBuffer::ResetValues()
{
    for(VecIterator it = m_buffer.begin(); it != m_buffer.end(); ++it)
    {
        it->setY(0.0);
    }
}

void BasePlotBuffer::UpdateFrequencies(const double startFreq, const double freqStep)
{
    double frequency = startFreq;
    for(VecIterator it = m_buffer.begin(); it != m_buffer.end(); ++it)
    {
        it->setX(frequency);
        frequency += freqStep;
    }
}
