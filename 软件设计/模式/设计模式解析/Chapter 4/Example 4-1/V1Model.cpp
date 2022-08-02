#include "V1Model.h"
#include "Feature.h"
#include "V1.h"
#include "V1Slot.h"
#include "V1Hole.h"

V1Model::V1Model(void)
{
}

V1Model::~V1Model(void)
{
}

// segment of code that instantiates the features
// no error checking provided--for illustration 
// purposes only

Model* V1Model::buildV1Model (string modelName) 
{
    int modNum;
    modNum= V1Model::openModel( modelName);
    if (modNum <= 0) return 0l;
	
    V1Model *myModel= new V1Model;
    myModel->myModelNumber= modNum;
    myModel->buildModel();
    return myModel;
}

void V1Model::buildModel()
{
    // each feature object needs to know the model number 
    // and feature ID it corresponds to in order to
    // retrieve information when requested. Note how 
    // this information is passed to each object¡¯s
    // constructor
	
    nElements= getNumberOfElements();
    features= new Feature*[ nElements];
	
    // do for each feature in the model
    int i;
    int ID;
    for (i= 0; i < nElements; i++) 
    {
        // determine feature present and create 
        // appropriate feature object
        ID= V1::getFeatureID( myModelNumber, i);
        switch( V1::getFeatureType( myModelNumber, ID)) 
        {
            case FEATURE_SLOT:
                features[i]= new V1Slot( myModelNumber, ID);
	break;
	
            case FEATURE_HOLE:
                features[i]= new V1Hole( myModelNumber, ID);
                break;
             // Other cases
                }
        }
}

int V1Model::getNumberOfElements ()
{
    // get the number of Elements from V1
    // for code example, just return 1;
    return 1;
}