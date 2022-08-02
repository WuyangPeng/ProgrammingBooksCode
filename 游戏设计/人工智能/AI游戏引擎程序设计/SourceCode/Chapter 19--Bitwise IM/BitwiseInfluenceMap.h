#ifndef __BITWINFLUENCEMAP
#define __BITWINFLUENCEMAP

#pragma warning(disable: 4786)
#include "InfluenceMap.h"

class BitwiseInfluenceMap:public InfluenceMap
{
public:
    //constructor/functions
    BitwiseInfluenceMap():InfluenceMap(IM_BITWISE){}
    ~BitwiseInfluenceMap();
    virtual void Update(float dt);
    virtual void RegisterGameObj(GameObj* object);
    virtual void DrawTheInfluence();
    virtual void StampInfluenceShape(int* pMap,Point3f& location,int sizeX,int sizeY, int value, bool undo = false);
    int GetVelocityDirectionMask(GameObj* object);
    int  GetInfluenceType(int* pMap,Point3f& location);
    int  GetInfluenceDirection(int* pMap,Point3f& location);
};
#endif