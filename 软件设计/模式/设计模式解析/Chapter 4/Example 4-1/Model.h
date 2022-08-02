#pragma once
#include "Feature.h"

class Model
{
public:
    Model(void);
protected:
    Feature **features;
    int nElements;

public:
    virtual ~Model(void);
};
