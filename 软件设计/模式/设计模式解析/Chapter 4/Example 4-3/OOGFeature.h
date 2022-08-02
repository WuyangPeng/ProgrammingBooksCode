#pragma once
#include "definitions.h"

class OOGFeature
{
public:
    OOGFeature(void);
    double getX1();
    double getX2();
    OOGFEATURE_TYPES getType();

public:
    ~OOGFeature(void);
};