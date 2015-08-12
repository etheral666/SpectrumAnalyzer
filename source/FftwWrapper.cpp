#include "FftwWrapper.hpp"

FftwWrapper::FftwWrapper(IFftw& fftw, int fftSize, c64* input, c64* output, int fftSign, unsigned int fftFlags)
    : m_fftw(fftw),
      m_inputBuffer(input),
      m_outputBuffer(output),
      m_fftSize(fftSize)

{
    m_inputBuffer  = (c64*) m_fftw.FftwMalloc(sizeof(c64) * m_fftSize);
    m_outputBuffer = (c64*) m_fftw.FftwMalloc(sizeof(c64) * m_fftSize);
    m_fftwPlan     = m_fftw.FftwPlanDft1d(m_fftSize,
                                          reinterpret_cast<fftw_complex*>(m_inputBuffer),
                                          reinterpret_cast<fftw_complex*>(m_outputBuffer),
                                          FFTW_FORWARD,
                                          FFTW_MEASURE);
}

FftwWrapper::~FftwWrapper()
{
    m_fftw.FftwDestroyPlan(m_fftwPlan);
    m_fftw.FftwFree(m_inputBuffer);
    m_fftw.FftwFree(m_outputBuffer);
}

void FftwWrapper::ComputeFFT()
{
    m_fftw.FftwExecute(m_fftwPlan);
}

void FftwWrapper::ChangeFftwParameters(int fftSize, int newFftSign, unsigned int newFftFlags)
{
    m_fftw.FftwDestroyPlan(m_fftwPlan);
    m_fftw.FftwFree(m_inputBuffer);
    m_fftw.FftwFree(m_outputBuffer);

    m_inputBuffer  = (c64*) m_fftw.FftwMalloc(sizeof(c64) * m_fftSize);
    m_outputBuffer = (c64*) m_fftw.FftwMalloc(sizeof(c64) * m_fftSize);
    m_fftwPlan     = m_fftw.FftwPlanDft1d(fftSize,
                                          reinterpret_cast<fftw_complex*>(m_inputBuffer),
                                          reinterpret_cast<fftw_complex*>(m_outputBuffer),
                                          newFftSign,
                                          newFftFlags);
}

