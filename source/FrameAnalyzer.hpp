#ifndef FRAME_ANALYZER_HPP
#define FRAME_ANALYZER_HPP

//#include "fftw3.h"

class FrameAnalyzer
{
public:
    FrameAnalyzer();

    void ProcessFrame(int* frame)
    {
//        fftw_plan plan;

    }

private:
    int frameSize;
};

#endif // FRAME_ANALYZER_HPP
