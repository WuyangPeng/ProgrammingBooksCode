#pragma once
#include "definitions.h"

class V1
{
public:
    V1(void);		
    static FEATURE_TYPES getFeatureType( int, int);
    static int getFeatureID( int, int );
    static double getXforHole( int, int);
    static double getX1forSlot( int, int);
    static double getX2forSlot( int, int);

public:
    ~V1(void);
};