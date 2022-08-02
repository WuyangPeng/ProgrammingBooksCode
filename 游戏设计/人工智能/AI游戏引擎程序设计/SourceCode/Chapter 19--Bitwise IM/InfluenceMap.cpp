#pragma warning(disable: 4786)
#include <algorithm>
#include "InfluenceMap.h"
#include "GameSession.h"
#include "utility.h"
#include "GameObj.h"
#include <GL/glut.h>

//---------------------------------------------------------
InfluenceMap::~InfluenceMap()
{
    if(m_registeredObjects.size() == 0)
        return;
    RegObjectList::iterator listObj;
    for(listObj=m_registeredObjects.begin();listObj!=m_registeredObjects.end();++listObj)
    {
        delete (*listObj);
    }
    m_registeredObjects.clear();
    
}
//---------------------------------------------------------
void InfluenceMap::Init(int sizeX, int sizeY, int wSizeX, int wSizeY)
{
    m_dataSizeX     = sizeX;
    m_dataSizeY     = sizeY;
    m_numCels       = m_dataSizeX*m_dataSizeY;
    m_map           = new int[m_numCels];

    //clear out the map
    memset(m_map,0,m_numCels*sizeof(int));
    
    m_worldSizeX    = wSizeX;
    m_worldSizeY    = wSizeY;
    m_celResX       = m_worldSizeX / m_dataSizeX;
    m_celResY       = m_worldSizeY / m_dataSizeY;
}

//---------------------------------------------------------
void RemoveAll(RegObj* object)
{
    delete object;
}

//---------------------------------------------------------
void InfluenceMap::Reset()
{
    //clear out the map
    memset(m_map,0,m_numCels*sizeof(int));
    
    //get rid off all the objects
    if(m_registeredObjects.size() == 0)
        return;
    for_each(m_registeredObjects.begin(),m_registeredObjects.end(),RemoveAll);
    m_registeredObjects.clear();
}

//---------------------------------------------------------
void InfluenceMap::RegisterGameObj(GameObj* object)
{
    int sizeY,sizeX;
    sizeX = sizeY = 1;
    
    RegObj* temp;
    temp = new RegObj;
    temp->m_pObject      = object;
    temp->m_objSizeX     = sizeX;
    temp->m_objSizeY     = sizeY;
    temp->m_lastPosition = object->m_position;
    temp->m_stamped      = false;
    m_registeredObjects.push_back(temp);
}

//---------------------------------------------------------
void InfluenceMap::RemoveGameObj(GameObj* object)
{
    if(m_registeredObjects.size() == 0)
        return;

    RegObjectList::iterator listObj;
    for(listObj=m_registeredObjects.begin();listObj!=m_registeredObjects.end();++listObj)
    {
        RegObj* temp = *listObj;
        if((*listObj)->m_pObject == object)
        {
            m_registeredObjects.erase(listObj);
            delete temp;
            return;
        }
    }
    
}

//---------------------------------------------------------
void InfluenceMap::Draw()
{
    //Draw Grid lines
    if(m_drawGrid)
        DrawTheGrid();
    if(m_drawInfluence)
        DrawTheInfluence();
}

//---------------------------------------------------------
void InfluenceMap::DrawTheGrid()    
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(0,0,0);
    glColor3f(0.2f,0.2f,0.2f);
    //draw horizontal grid lines
    float pos = 0.0f;
    for(int i = 0;i<m_dataSizeY+1;i++)
    {
        glBegin(GL_LINE_STRIP);
        glVertex3f(0, pos,0);
        glVertex3f(Game.m_screenW, pos,0);
        glEnd();
        pos+=m_celResY;
    }   
    
    //draw vertical grid lines
    pos = 0.0f;
    for(i = 0;i<m_dataSizeX+1;i++)
    {
        glBegin(GL_LINE_STRIP);
        glVertex3f(pos, 0,0);
        glVertex3f(pos, Game.m_screenH,0);
        glEnd();
        pos+=m_celResX;
    }    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

//---------------------------------------------------------
void InfluenceMap::DrawTheInfluence()
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(0,0,0);
    glEnable(GL_BLEND);                                 
    glBlendFunc(GL_ONE, GL_ONE);                    
    for(int i=0;i<m_numCels;i++)
    {
        if(m_map[i])
        {
            int y = i / m_dataSizeY;
            int x = i - y*m_dataSizeY;
            glColor3f(0.5f,0.5f,0.5f);
            glBegin(GL_POLYGON);
            glVertex3f(x*m_celResX,          y*m_celResY,          0);
            glVertex3f(x*m_celResX,          y*m_celResY+m_celResY,0);
            glVertex3f(x*m_celResX+m_celResX,y*m_celResY+m_celResY,0);
            glVertex3f(x*m_celResX+m_celResX,y*m_celResY,          0);
            glEnd();
        }
    }
    glDisable(GL_BLEND);    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

//---------------------------------------------------------
void InfluenceMap::StampInfluenceShape(int* pMap,Point3f& location,int sizeX, int sizeY, int value)
{
    int gridX = location.x()/ m_celResX;
    int gridY = location.y()/ m_celResY;
    
    int startX = gridX - sizeX/2;
    if(startX < 0) startX += m_dataSizeX;
    int startY = gridY - sizeY/2;
    if(startY < 0) startY += m_dataSizeY;
    
    for(int y = startY;y<startY + sizeY;y++)
    {
        for(int x = startX;x<startX + sizeX;x++)
        {
            pMap[(y%m_dataSizeY)*m_dataSizeY + (x%m_dataSizeX)] += value;
        }
    }
}

//---------------------------------------------------------
int InfluenceMap::GetInfluenceValue(int* pMap,Point3f& location)
{
    int gridX = location.x()/ m_celResX;
    int gridY = location.y()/ m_celResY;
    return pMap[gridX,gridY];
}

//---------------------------------------------------------
int InfluenceMap::SumInfluenceShape(int* pMap,Point3f& location,int sizeX,int sizeY)
{
    int sum = 0;
    int gridX = location.x()/ m_celResX;
    int gridY = location.y()/ m_celResY;
    
    int startX = gridX - sizeX/2;
    if(startX < 0) startX += m_dataSizeX;
    int startY = gridY - sizeY/2;
    if(startY < 0) startY += m_dataSizeY;
    
    for(int y = startY;y<startY + sizeY;y++)
    {
        for(int x = startX;x<startX + sizeX;x++)
        {
            sum += pMap[(y%m_dataSizeY)*m_dataSizeY + (x%m_dataSizeX)];
        }
    }
    return sum;
}

//---------------------------------------------------------
void InfluenceMap::StampInfluenceGradient(int* pMap,Point3f& location, int initValue)
{
    int gridX = location.x()/ m_celResX;
    int gridY = location.y()/ m_celResY;
    
    int stopDist = fabsf(initValue)*0.75f;//*(m_dataSizeX/32);
    int halfStopDist = stopDist / 2;
    int startX = gridX - halfStopDist;
    if(startX < 0) startX += m_dataSizeX;
    int startY = gridY - halfStopDist;
    if(startY < 0) startY += m_dataSizeY;
    
    for(int y = startY;y<startY + stopDist;y++)
    {
        for(int x = startX;x<startX + stopDist;x++)
        {
            int value;

            int distX = fabs(x - (startX + halfStopDist));
            int distY = fabs(y - (startY + halfStopDist));

            value = initValue* (halfStopDist - MAX(distX,distY))/halfStopDist;
            pMap[(y%m_dataSizeY)*m_dataSizeY + (x%m_dataSizeX)] += value;
        }
    }
}
