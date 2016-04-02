#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "Constants.hpp"
#include "Types.hpp"
#include "HackRfInterface.hpp"
#include "Fftw.hpp"
#include "FftwWrapper.hpp"

class Process
{
public:
    Process();

    ~Process();

    void Start();

private:
    HackRfInterface m_hackRf;
    Fftw            m_fftw;
    FftwWrapper     m_fftwWrapper;

    c64* m_fftInputBuffer;
};

int TransferCallback(hackrf_transfer* transfer);

#endif // PROCESS_HPP
