#pragma once
#include "model.h"
#include <string>
using namespace std;
#include "OOGFeature.h"
#include "definitions.h"

class V2Model :
    public Model
{
public:
    V2Model(void);
    static int openModel( string ModelName);
    static Model* buildV2Model(string);
    void buildModel();
    int getNumberOfElements();
    OOGFeature *getElement(int);

public:
    ~V2Model(void);

};