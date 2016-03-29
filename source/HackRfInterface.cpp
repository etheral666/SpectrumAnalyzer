#include "HackRfInterface.hpp"
#include "AnalysisParameters.hpp"
#include "Defaults.hpp"

#include <cstring>

HackRfInterface::HackRfInterface(hackrf_device** device, hackrf_sample_block_cb_fn callback)
    : m_device(NULL),
      m_state(UndefinedState),
      m_rxCallback(callback)
{
    int32_t status = hackrf_init();
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

    status = hackrf_set_freq(m_device, Defaults::centerFrequency);
    if(status == HACKRF_SUCCESS)
    hackrf_set_sample_rate(m_device, Defaults::samplingRate);

    if(status == HACKRF_SUCCESS)
    m_state = Connected;
    *device = m_device;
}

HackRfInterface::~HackRfInterface()
{
    StopReceiving();
    hackrf_close(m_device);
    hackrf_exit();
}

bool HackRfInterface::SetAnalysisParameters(const AnalysisParameters& params)
{
    int result = hackrf_set_freq(m_device, params.centerFrequency);
    if(result != HACKRF_SUCCESS)
    {
        return false;
    }

    result = hackrf_set_sample_rate(m_device, static_cast<double>(params.samplingFrequency));
    if(result != HACKRF_SUCCESS)
    {
        return false;
    }

    return true;
}

void HackRfInterface::StartReceiving()
{
    if(IsConnected())
    {
        int result = hackrf_start_rx(m_device, m_rxCallback, NULL);
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

