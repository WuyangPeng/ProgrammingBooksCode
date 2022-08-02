#include "OccupanceInfluenceMap.h"
#include "GameObj.h"
#include "utility.h"
#include <GL/glut.h>

//---------------------------------------------------------
void OccupanceInfluenceMap::Update(float dt)
{
    //bail out if nobody to update
    if(m_registeredObjects.size() == 0)
        return;
 
    //clear out map
//    memset(m_map,0,m_numCels*sizeof(int));
    
    RegObjectList::iterator listObj;
    //unstamp old locations
    for(listObj=m_registeredObjects.begin();listObj!=m_registeredObjects.end();++listObj)
    {
        if((*listObj)->m_stamped)
            StampInfluenceShape(m_map,(*listObj)->m_lastPosition,(*listObj)->m_objSizeX,(*listObj)->m_objSizeY, -1);
    }
    
    //stamp new locations
    for(listObj=m_registeredObjects.begin();listObj!=m_registeredObjects.end();++listObj)
    {
        RegObj* temp = *listObj;
        StampInfluenceShape(m_map,(*listObj)->m_pObject->m_position,(*listObj)->m_objSizeX,(*listObj)->m_objSizeY, 1);
        (*listObj)->m_stamped = true;
        (*listObj)->m_lastPosition = (*listObj)->m_pObject->m_position;
    }
}

//---------------------------------------------------------
void OccupanceInfluenceMap::RemoveGameObj(GameObj* object)
{
    if(m_registeredObjects.size() == 0)
        return;
    
    RegObjectList::iterator listObj;
    for(listObj=m_registeredObjects.begin();listObj!=m_registeredObjects.end();++listObj)
    {
        RegObj* temp = *listObj;
        if((*listObj)->m_pObject == object)
        {
            if((*listObj)->m_stamped)
                StampInfluenceShape(m_map,(*listObj)->m_lastPosition,(*listObj)->m_objSizeX,(*listObj)->m_objSizeY, -1);
            m_registeredObjects.erase(listObj);
            delete temp;
            return;
        }
    }
    
}

//---------------------------------------------------------
void OccupanceInfluenceMap::RegisterGameObj(GameObj* object)
{
    int sizeX,sizeY;
    if(object->m_size <4)
    {
        sizeX = m_dataSizeX/16;
        sizeY = m_dataSizeY/16;
    }
    else if(object->m_size<11)
    {
        sizeX = m_dataSizeX/10;
        sizeY = m_dataSizeY/10;
    }
    else if(object->m_size<33)
    {
        sizeX = m_dataSizeX/8;
        sizeY = m_dataSizeY/8;
    }
    else if(object->m_size <49)
    {
        sizeX = m_dataSizeX/5;
        sizeY = m_dataSizeX/5;
    }
    else if(object->m_size <65)
    {
        sizeX = m_dataSizeX/4;
        sizeY = m_dataSizeX/4;
    }
    else
    {
        sizeX = m_dataSizeX/3;
        sizeY = m_dataSizeX/3;
    }
    
    //set minimum size of 1 in each direction
    sizeX = MAX(1,sizeX);
    sizeY = MAX(1,sizeY);
    
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
void OccupanceInfluenceMap::DrawTheInfluence()
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
            float grayscale = m_map[i]/10.0f;
            glColor3f(grayscale,grayscale,grayscale);
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



