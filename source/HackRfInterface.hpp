#ifndef HACKRF_INTERFACE_HPP
#define HACKRF_INTERFACE_HPP

#include <../externals/libhackrf/src/hackrf.h>

class HackRfInterface
{
public:
    HackRfInterface()
    {
        m_status = hackrf_init();
    }

    int GetStatus()
    {
        return m_status;
    }
private:
    int m_status;
};

#endif // HACKRF_INTERFACE_HPP
