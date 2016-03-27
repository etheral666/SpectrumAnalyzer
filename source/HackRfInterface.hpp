#ifndef HACKRF_INTERFACE_HPP
#define HACKRF_INTERFACE_HPP

#include <hackrf.h>

#include <string>
#include <sstream>

enum EHackRfState
{
    UndefinedState,
    NotInitialized,
    NotConnected,
    Connected,
    Receiving,
    Transmitting
};

class HackRfInterface
{
public:
    HackRfInterface();

    ~HackRfInterface();

    void StartReceiving();

    void StopReceiving();

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
        return Receiving == m_state;
    }

    hackrf_transfer m_transferInfo;
    hackrf_device*  m_device;

    int          m_status;
    EHackRfState m_state;
    std::string  m_lastError;
};

int ReceiveCallback(hackrf_transfer* transfer);

#endif // HACKRF_INTERFACE_HPP
