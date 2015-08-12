#ifndef FFTW_WRAPPER_HPP
#define FFTW_WRAPPER_HPP

#include "IFftw.hpp"

#include <complex>

class FftwWrapper
{
private:
    typedef std::complex<double> c64;

public:
    FftwWrapper(IFftw& fftw, int fftSize, c64* input, c64* output, int fftSign, unsigned int fftFlags);
    ~FftwWrapper();

    void ComputeFFT();
    void ChangeFftwParameters(int fftSize, int newFftSign, unsigned int newFftFlags);

private:
    IFftw&    m_fftw;
    fftw_plan m_fftwPlan;
    c64*      m_inputBuffer;
    c64*      m_outputBuffer;
    int       m_fftSize;
};

#endif // FFTW_WRAPPER_HPP
