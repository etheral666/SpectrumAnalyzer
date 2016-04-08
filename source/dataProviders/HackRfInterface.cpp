#include "HackRfInterface.hpp"
#include "AnalysisParameters.hpp"
#include "Defaults.hpp"

HackRfInterface* HackRfInterface::s_instance         = NULL;
volatile bool    HackRfInterface::s_isNextFrameReady = false;

hackrf_transfer g_lastTransferInfo;

HackRfInterface::HackRfInterface()
    : m_device(NULL),
      m_state(UndefinedState)
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
}

HackRfInterface::~HackRfInterface()
{
    hackrf_close(m_device);
    hackrf_exit();
}

HackRfInterface* HackRfInterface::GetInstance()
{
    if(s_instance != NULL)
    {
        return s_instance;
    }
    else
    {
        s_instance = new HackRfInterface();
        return s_instance;
    }
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

bool HackRfInterface::ReceiveNextFrame()
{
    s_isNextFrameReady = false;
    if(IsConnected())
    {
        int result = hackrf_start_rx(m_device, TransferCallback, NULL);
        if(result < 0)
        {
            SetErrorString("Receiving could not be started: ", result);
            return false;
        }
        else
        {
            m_state = Receiving;
            return true;
        }
    }
    return false;
}

int HackRfInterface::TransferCallback(hackrf_transfer* transfer)
{
    g_lastTransferInfo = *transfer;
    s_instance->m_state = Connected;
    s_isNextFrameReady = true;
    return -1;
}

void HackRfInterface::WaitForNextFrame()
{
    // TODO add timeout to avoid infinite loop risk
    while(s_isNextFrameReady != true)
    {
        // wait longer
    }
}

void HackRfInterface::SetErrorString(const std::string& description, const int errCode)
{
    std::string state = "";
    switch(m_state)
    {
        case UndefinedState:
            state = "UndefinedState";
            break;
        case NotInitialized:
            state = "NotInitialized";
            break;
        case NotConnected:
            state = "NotConnected";
            break;
        case Connected:
            state = "Connected";
            break;
        case Receiving:
            state = "Receiving";
            break;
    }
    std::stringstream errorStream;
    errorStream << "[HackRf] State: " << state << " Error: " << description << hackrf_error_name(static_cast<hackrf_error>(errCode));
    m_lastError = errorStream.str();
}
