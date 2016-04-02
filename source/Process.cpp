#include "Process.hpp"
#include "SamplesAdapter.hpp"

#include <cstring>
#include <iostream>
#include <chrono>

hackrf_device*   g_hackRfDevice;
HackRfInterface* g_hackRfInterface;
FftwWrapper*     g_fftw;

c64 g_fftInput[Const::hackRfTransferBufferSize];
c64 g_fftOutput[Const::hackRfTransferBufferSize];

volatile int32_t g_processNext;

Process::Process()
    : m_hackRf(&g_hackRfDevice, TransferCallback),
      m_fftwWrapper(m_fftw, Const::hackRfTransferBufferSize, g_fftInput, g_fftOutput, 0, 0)
{
    g_hackRfInterface = &m_hackRf;
    g_fftw            = &m_fftwWrapper;
    m_fftInputBuffer = new c64[Const::hackRfTransferBufferSize];
}

Process::~Process()
{
    delete [] m_fftInputBuffer;
}

void Process::Start()
{
    g_processNext = 1;
    if(m_hackRf.StartReceiving())
    {
        while(g_processNext != 0)
        {

        }
        m_hackRf.StopReceiving();
    }
    else
    {
        std::cout << "[Process] Error:" << m_hackRf.GetLastErrorDescription() << std::endl;
        return;
    }

    std::cout << "[Process] Info: Stopped processing samples." << std::endl;
}

int TransferCallback(hackrf_transfer* transfer)
{
//    g_hackRfInterface->StopReceiving();
    int32_t invalidSamplesCount = Const::hackRfTransferBufferSize - transfer->valid_length;
    if(invalidSamplesCount > 0)
    {
        std::memset(&transfer->buffer[transfer->valid_length], 0, invalidSamplesCount * sizeof(uint8_t));
    }
    // here comes processing samples

    using namespace std::chrono;
    high_resolution_clock::time_point start = high_resolution_clock::now();
    UInt8ToCplxDouble(transfer->buffer, g_fftInput, Const::hackRfTransferBufferSize);
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double> difference = end - start;
    std::cout << "[TransferCallback] Info: preparing fft input took " << std::fixed << difference.count() * 1000 << " ms" << std::endl;

    start = high_resolution_clock::now();
    g_fftw->ComputeFFT();
    end = high_resolution_clock::now();
    difference = end - start;
    std::cout << "[TransferCallback] Info: computing fft took " << std::fixed << difference.count() * 1000 << " ms" << std::endl;

    int32_t processNext = 0;
    std::cout << "[TransferCallback] Continue? 0/1" << std::endl;
    std::cin >> processNext;
    if(!processNext)
    {
        g_hackRfInterface->StopReceiving();
    }
    g_processNext = processNext;

//    g_hackRfInterface->StartReceiving();
    return 0;
}
