#include "FakeAntenna.hpp"
#include "Constants.hpp"

#include <fstream>
#include <cstring>

FakeAntenna::FakeAntenna(const std::string& inputFilePath, double* rawSamples)
    : m_sequenceSize(0),
      m_currentStreamIdx(0),
      m_antennaSequence(NULL),
      m_rawSamples(rawSamples)
{
    if(FileExists(inputFilePath))
    {
        m_filePath     = inputFilePath;
        m_sequenceSize = GetFileSize() / sizeof(double);

        m_antennaSequence = new double[m_sequenceSize];
        ReadDataFromFile();
    }
}

FakeAntenna::~FakeAntenna()
{
    if(m_antennaSequence)
    {
        delete [] m_antennaSequence;
    }
}

void FakeAntenna::ProcessNextSamplesBlock()
{
    if(m_currentStreamIdx < m_sequenceSize)
    {
        std::memcpy(m_rawSamples,
                    m_antennaSequence + m_currentStreamIdx,
                    Const::fftSize1024 * sizeof(double));

        m_currentStreamIdx += Const::fftSize1024;
    }
}

bool FakeAntenna::FileExists(const std::string& filePath)
{
    std::fstream file(filePath.c_str());
    return file.good();
}

int FakeAntenna::GetFileSize()
{
    std::fstream file(m_filePath.c_str());
    file.seekg(0, file.end);

    return file.tellg();
}

void FakeAntenna::ReadDataFromFile()
{
    std::fstream file(m_filePath.c_str());
    file.read((char*)m_antennaSequence, GetFileSize());
}

