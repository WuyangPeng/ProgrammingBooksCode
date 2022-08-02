#ifndef __INFLUENCEMAP
#define __INFLUENCEMAP

#pragma warning(disable: 4786)
#include <list>
#include "Point3.h"

using namespace std;
class GameObj;
class Point3;

enum
{
    OT_FRIENDLY,
    OT_BULLET,
    OT_ENEMY,
    OT_MISC
};

struct RegObj
{
    GameObj*    m_pObject;
    int         m_objSizeX;
    int         m_objSizeY;
    int         m_objType;
    Point3f     m_lastPosition;
    bool        m_stamped;
};

typedef std::list<RegObj*> RegObjectList;

class InfluenceMap
{
public:
    //constructor/functions
    InfluenceMap(int type):m_influenceType(type){m_drawGrid = false;m_drawInfluence = false;}
    ~InfluenceMap();
    virtual void Update(float dt) {}
    virtual void Draw();
    virtual void DrawTheGrid();
    virtual void DrawTheInfluence();
    virtual void Init(int sizeX, int sizeY, int wSizeX, int wSizeY);
    virtual void Reset();
    virtual void RegisterGameObj(GameObj* object);
    virtual void RemoveGameObj(GameObj* object);
    virtual void StampInfluenceShape(int* pMap,Point3f& location,int sizeX,int sizeY, int value);
    virtual void StampInfluenceGradient(int* pMap,Point3f& location, int initValue);
    int  SumInfluenceShape(int* pMap,Point3f& location,int sizeX,int sizeY);
    int  GetInfluenceValue(int* pMap,Point3f& location);
    void SetType(int type) {m_influenceType = type;}
    void DrawGrid(bool on = true){m_drawGrid = on;}
    void DrawInfluence(bool on = true){m_drawInfluence = on;}
    int  GetSizeX(){return m_dataSizeX;}
    int  GetSizeY(){return m_dataSizeY;}

    //influence map types
    enum
    {
        IM_NONE,
        IM_OCCUPANCE,
        IM_CONTROL,
        IM_BITWISE
    };

protected:
    //data members
    int*    m_map;
    RegObjectList m_registeredObjects;

    int     m_dataSizeX;     
    int     m_dataSizeY;
    int     m_numCels;
    int     m_worldSizeX;
    int     m_worldSizeY;
    float   m_celResX;
    float   m_celResY;
    int     m_influenceType;

    bool    m_drawGrid;
    bool    m_drawInfluence;
};
#endif