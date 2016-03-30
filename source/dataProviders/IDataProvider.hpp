#ifndef IDATA_PROVIDER_HPP
#define IDATA_PROVIDER_HPP

#include "Types.hpp"
#include "IDataReceiver.hpp"
#include "BasePlotBuffer.hpp"

class IDataProvider
{
public:
    virtual void NotifyDataReceiver(const IDataReceiver& receiver) = 0;
    virtual void SetReceiverBuffer(const c64* rawSamples) = 0;
};
#endif // IDATA_PROVIDER_HPP

