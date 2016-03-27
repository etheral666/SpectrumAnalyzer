#include "HackRfInterface.hpp"

#include <cstring>
#include <iostream>

HackRfInterface::HackRfInterface()
    : m_device(0),
      m_state(UndefinedState)
{
    std::memset(&m_transferInfo, 0, sizeof(hackrf_transfer));
    m_transferInfo.device = m_device;

    int status = hackrf_init();
    if(HACKRF_SUCCESS != hackrf_init())
    {
        SetErrorString("Initialization failed: ", status);
        m_state = NotInitialized;
        return;
    }
    status = hackrf_open(&m_device);
    if(status != HACKRF_SUCCESS)
    {
        SetErrorString("Connection open failed: ", status);
        m_state = NotConnected;
        return;
    }

    m_state = Connected;
}

HackRfInterface::~HackRfInterface()
{
    hackrf_close(m_device);
    hackrf_exit();
}

void HackRfInterface::StartReceiving()
{
    if(IsConnected())
    {
        int result = hackrf_start_rx(m_device, ReceiveCallback, NULL);
        if(result < 0)
        {
            SetErrorString("Receiving could not be started: ", result);
        }
        else
        {
            m_state = Receiving;
        }
    }
}

void HackRfInterface::StopReceiving()
{
    if(IsReceiving())
    {
        int result = hackrf_stop_rx(m_device);
        if(result < 0)
        {
            SetErrorString("Receiving could not be stopped correctly: ", result);
            m_state = UndefinedState;
        }
        else
        {
            m_state = Connected;
        }
    }
}

void HackRfInterface::SetErrorString(const std::string description, const int errCode)
{
    std::stringstream errorStream;
    errorStream << "[HackRf] Error: " << description << hackrf_error_name(static_cast<hackrf_error>(errCode));
    m_lastError = errorStream.str();
}


int ReceiveCallback(hackrf_transfer* transfer)
{
    std::cout << "Started receiving - not yet implemented." << std::endl;
    return 0;
}
