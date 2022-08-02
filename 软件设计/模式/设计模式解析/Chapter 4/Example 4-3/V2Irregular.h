#pragma once
#include "irregularfeature.h"
#include "OOGFeature.h"

class V2Irregular :
    public IrregularFeature
{
public:
    V2Irregular(OOGFeature *feature);
public:
    ~V2Irregular(void);
private:
    OOGFeature *myOOGFeature;
};