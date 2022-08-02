#include "HighResFact.h"

HighResFact::HighResFact(void)
{
}

HighResFact::~HighResFact(void)
{
}
DisplayDriver* HighResFact::getDispDrvr(void)
{
    return new HRDD;
}

PrintDriver* HighResFact::getPrtDrvr(void)
{
    return new HRPD;
}