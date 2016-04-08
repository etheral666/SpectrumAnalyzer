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
    Receiving
};

struct AnalysisParameters;

class HackRfInterface
{
public:
    static HackRfInterface* GetInstance();

    ~HackRfInterface(); //TODO check if destructor will be necessary

    bool ReceiveNextFrame();

    void WaitForNextFrame();

    bool SetAnalysisParameters(const AnalysisParameters& params);

    EHackRfState CheckState() const
    {
        return m_state;
    }

    const std::string& GetLastErrorDescription() const
    {
        return m_lastError;
    }

private:
    HackRfInterface();

    static HackRfInterface* s_instance;
    volatile static bool    s_isNextFrameReady;

    static int TransferCallback(hackrf_transfer* transfer);

    void SetErrorString(const std::string& description, const int errCode);

    bool IsConnected() const
    {
        return Connected == m_state;
    }

    hackrf_device* m_device;

    EHackRfState m_state;
    std::string  m_lastError;
};

#endif // HACKRF_INTERFACE_HPP
