#include "LowResFact.h"

LowResFact::LowResFact(void)
{
}

LowResFact::~LowResFact(void)
{
}

DisplayDriver* LowResFact::getDispDrvr(void)
{
    return new LRDD;
}

PrintDriver* LowResFact::getPrtDrvr(void)
{
    return new LRPD;
}