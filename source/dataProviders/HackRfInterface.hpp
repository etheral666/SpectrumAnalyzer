#ifndef HACKRF_INTERFACE_HPP
#define HACKRF_INTERFACE_HPP

#include <hackrf.h>

#include <string>
#include <sstream>
#include <stdint.h>

enum EHackRfState
{
    UndefinedState,
    NotInitialized,
    NotConnected,
    Connected,
    Receiving,
    Transmitting
};

struct AnalysisParameters;

class HackRfInterface
{
public:
    HackRfInterface(hackrf_device** device, hackrf_sample_block_cb_fn callback);

    ~HackRfInterface();

    bool SetAnalysisParameters(const AnalysisParameters& params);

    bool StartReceiving();

    bool StopReceiving();

    EHackRfState CheckState() const
    {
        return m_state;
    }

    const std::string& GetLastErrorDescription() const
    {
        return m_lastError;
    }

private:
    void SetErrorString(const std::string description, const int errCode);

    bool IsConnected() const
    {
        return Connected == m_state;
    }

    bool IsReceiving() const
    {
        return Receiving == m_state && HACKRF_TRUE == hackrf_is_streaming(m_device);
    }

    hackrf_device* m_device;

    EHackRfState m_state;
    std::string  m_lastError;

    int (*m_rxCallback)(hackrf_transfer*);
};

#endif // HACKRF_INTERFACE_HPP
