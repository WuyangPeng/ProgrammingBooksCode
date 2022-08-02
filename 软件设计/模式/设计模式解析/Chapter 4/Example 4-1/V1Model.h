#pragma once
#include "model.h"
#include <string>
using namespace std;

class V1Model : public Model
{
public:
Model(void);
static int openModel( string ModelName);
static Model* buildV1Model(string);
void buildModel();


private:
    void buildV1Model();
    int nElements;
    int myModelNumber;
    int getNumberOfElements();

public:
    ~V1Model(void);
};