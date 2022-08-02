#include "ControlInfluenceMap.h"
#include "GameObj.h"
#include <GL/glut.h>

//---------------------------------------------------------
void ControlInfluenceMap::Update(float dt)
{
    //bail out if nobody to update
    if(m_registeredObjects.size() == 0)
        return;
    
    //clear out map
    memset(m_map,0,m_numCels*sizeof(int));
    
    //stamp obj locations
    RegObjectList::iterator listObj;
    for(listObj=m_registeredObjects.begin();listObj!=m_registeredObjects.end();++listObj)
    {
        //only care about "control" objects, not miscellaneous
        if((*listObj)->m_objType == OT_MISC)
            continue;

        if((*listObj)->m_objType == OT_FRIENDLY)
            StampInfluenceGradient(m_map,(*listObj)->m_pObject->m_position, 16);
        else if((*listObj)->m_objType == OT_BULLET)
            StampInfluenceGradient(m_map,(*listObj)->m_pObject->m_position, 8);
        else
            StampInfluenceGradient(m_map,(*listObj)->m_pObject->m_position, -(((*listObj)->m_pObject->m_size)/2));
        (*listObj)->m_lastPosition = (*listObj)->m_pObject->m_position;
    }
}

//---------------------------------------------------------
void ControlInfluenceMap::RegisterGameObj(GameObj* object)
{
    int sizeX,sizeY;
    sizeX = sizeY = 1;
    
    RegObj* temp;
    temp = new RegObj;
    temp->m_pObject      = object;
    temp->m_objSizeX     = sizeX;
    temp->m_objSizeY     = sizeY;
    temp->m_lastPosition = object->m_position;
    temp->m_stamped      = false;
    if(object->m_type == GameObj::OBJ_SHIP || object->m_type == GameObj::OBJ_SAUCER)
        temp->m_objType = OT_FRIENDLY;
    else if(object->m_type == GameObj::OBJ_BULLET)
        temp->m_objType = OT_BULLET;
    else if(object->m_type == GameObj::OBJ_ASTEROID)
        temp->m_objType = OT_ENEMY;
    else
        temp->m_objType = OT_MISC;
    m_registeredObjects.push_back(temp);
}

//---------------------------------------------------------
void ControlInfluenceMap::DrawTheInfluence()
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
            float color = m_map[i]/16.0f;
            if(color > 0)
                glColor3f(0,0,color);
            else
                glColor3f(-color,0,0);
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