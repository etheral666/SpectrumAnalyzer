#ifndef FAKE_ANTENNA_HPP
#define FAKE_ANTENNA_HPP

#include <string>

#include "IDataProvider.hpp"

class FakeAntenna : public IDataProvider
{
public:
    FakeAntenna(const std::string& inputFilePath, double* rawSamples);
    ~FakeAntenna();

    virtual void NotifyDataReceiver(const IDataReceiver& receiver) {}
    virtual void SetReceiverBuffer(const c64* buffer) {}

    void ProcessNextSamplesBlock();

private:
    bool FileExists(const std::string& filePath);
    int GetFileSize();
    void ReadDataFromFile();

    std::string m_filePath;
    int         m_sequenceSize;
    int         m_currentStreamIdx;
    double*     m_antennaSequence;
    double*     m_rawSamples;
};

#endif // FAKE_ANTENNA_HPP
