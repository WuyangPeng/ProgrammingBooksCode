#include "ResFactory.h"
#include "HighResFactory.h"
#include "LowResFactory.h"

ResFactory::ResFactory(void)
{
}

ResFactory::~ResFactory(void)
{
}

ResFactory* ResFactory::getFactory (void)
{
    // Logic to decide which resolution to use
    // If are to use High Resolution
    return new HighResFactory;
    // if are to use Low Resolution
    return new LowResFactory;
}