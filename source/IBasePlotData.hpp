#ifndef IBASEPLOTDATA_HPP
#define IBASEPLOTDATA_HPP

class IBasePlotData
{
public:
    IBasePlotData() {}

    virtual ~IBasePlotData() {}

    virtual void ResetValues() = 0;
    virtual void UpdateValues() = 0;
    virtual void UpdateFrequencies(const double startFreq, const double freqStep) = 0;
    virtual double GetGlobalMax() = 0;
};

#endif // IBASEPLOTDATA_HPP
