#ifndef __CONTINFLUENCEMAP
#define __CONTINFLUENCEMAP

#pragma warning(disable: 4786)
#include "InfluenceMap.h"

class ControlInfluenceMap:public InfluenceMap
{
public:
    //constructor/functions
    ControlInfluenceMap():InfluenceMap(IM_CONTROL){}
    ~ControlInfluenceMap();
    virtual void Update(float dt);
    virtual void RegisterGameObj(GameObj* object);
    virtual void DrawTheInfluence();
    
};
#endif