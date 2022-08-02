#include "V2Model.h"
#include "V2Slot.h"
#include "V2Hole.h"

V2Model::V2Model(void)
{
}

V2Model::~V2Model(void)
{
}
// segment of code that instantiates the features
// no error checking provided--for illustration 
// purposes only

Model* V2Model::buildV2Model (string modelName) 
{
    // open model
    int modNum;
    modNum= V2Model::openModel( modelName);
    if (modNum <= 0) return 0l;
    
    V2Model *myModel= new V2Model;
    if (!myModel->openModel( modelName)) return 0l;
    
    myModel->buildModel();
    return myModel;
}


void V2Model::buildModel()
{
    // each feature object needs to know the feature in the 
    // V2 system it corresponds to in order to retrieve 
    // information when requested. Note how this information
    // is passed into each object¡¯s constructor
    
    nElements= getNumberOfElements();
    
    OOGFeature *oogF= new OOGFeature;
    
    // do for each feature in the model
    int i;
    for (i= 0; i < nElements; i++) {
        // determine feature present and create 
        // appropriate feature object
        oogF= getElement(i);
        switch( oogF->getType()) 
        {
            case OOGFEATURE_SLOT:
                features[i]= new V2Slot( oogF);
                break;
    
            case OOGFEATURE_HOLE:
                features[i]= new V2Hole( oogF);
                break;
            // other cases
        }
    }
}

int V2Model::getNumberOfElements ()
{
    // get the number of Elements from V1
    // for code example, just return 1;
    return 1;
}