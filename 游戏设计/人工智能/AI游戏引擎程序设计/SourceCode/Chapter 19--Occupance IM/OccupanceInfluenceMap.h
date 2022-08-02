#ifndef __OCCINFLUENCEMAP
#define __OCCINFLUENCEMAP

#pragma warning(disable: 4786)
#include "InfluenceMap.h"

class OccupanceInfluenceMap:public InfluenceMap
{
public:
    //constructor/functions
    OccupanceInfluenceMap():InfluenceMap(IM_OCCUPANCE){}
    ~OccupanceInfluenceMap();
    virtual void Update(float dt);
    virtual void RegisterGameObj(GameObj* object);
    virtual void RemoveGameObj(GameObj* object);
    virtual void DrawTheInfluence();
};
#endif