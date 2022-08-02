#include "BitwiseInfluenceMap.h"
#include "GameObj.h"
#include "utility.h"
#include <GL/glut.h>

//---------------------------------------------------------
void BitwiseInfluenceMap::Update(float dt)
{
    //bail out if nobody to update
    if(m_registeredObjects.size() == 0)
        return;
    
    //clear out map
    memset(m_map,0,m_numCels*sizeof(int));
    
    //stamp new data
    RegObjectList::iterator listObj;
    for(listObj=m_registeredObjects.begin();listObj!=m_registeredObjects.end();++listObj)
    {
        RegObj* temp = *listObj;
        //have to update the bits, since you can change direction continuously
        temp->m_objType = (char)temp->m_objType | GetVelocityDirectionMask(temp->m_pObject);
        StampInfluenceShape(m_map,(*listObj)->m_pObject->m_position,(*listObj)->m_objSizeX,(*listObj)->m_objSizeY,(*listObj)->m_objType);
        (*listObj)->m_stamped = true;
        (*listObj)->m_lastPosition = (*listObj)->m_pObject->m_position;
    }
}

//---------------------------------------------------------
void BitwiseInfluenceMap::RegisterGameObj(GameObj* object)
{
    int sizeX,sizeY;
    if(object->m_size <4)
    {
        sizeX = m_dataSizeX/16;// 2;
        sizeY = m_dataSizeY/16;// 2;
    }
    else if(object->m_size<11)
    {
        sizeX = m_dataSizeX/10;//3;
        sizeY = m_dataSizeY/10;//3;
    }
    else if(object->m_size<33)
    {
        sizeX = m_dataSizeX/8;//4;
        sizeY = m_dataSizeY/8;//4;
    }
    else if(object->m_size <49)
    {
        sizeX = m_dataSizeX/5;//6;
        sizeY = m_dataSizeX/5;//6;
    }
    else if(object->m_size <65)
    {
        sizeX = m_dataSizeX/4;//8;
        sizeY = m_dataSizeX/4;//8;
    }
    else
    {
        sizeX = m_dataSizeX/3;//10;
        sizeY = m_dataSizeX/3;//10;
    }
    
    //set minimum size of 1 in each direction
    sizeX = MAX(1,sizeX);
    sizeY = MAX(1,sizeY);

    
    RegObj* temp;
    temp = new RegObj;
    temp->m_objType = object->m_type;
    temp->m_objType |= GetVelocityDirectionMask(object);

    temp->m_pObject      = object;
    temp->m_objSizeX     = sizeX;
    temp->m_objSizeY     = sizeY;
    temp->m_lastPosition = object->m_position;
    temp->m_stamped      = false;
    m_registeredObjects.push_back(temp);
}

//---------------------------------------------------------
int BitwiseInfluenceMap::GetVelocityDirectionMask(GameObj* object)
{
    //set up the information bits
    //    bottom byte is the object type
    //    top byte is the velocity direction
    int velDir = 0;
    if(object->m_velocity.x() > 0)
    velDir |= DIR_RIGHT;
    else if (object->m_velocity.x() < 0)
    velDir |= DIR_LEFT;
    if(object->m_velocity.y() > 0)
    velDir |= DIR_UP;
    else if (object->m_velocity.y() < 0)
    velDir |= DIR_DOWN;
    return velDir<<8;
}

//---------------------------------------------------------
void BitwiseInfluenceMap::DrawTheInfluence()
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
            //determine color for type
            Point3f color(0,0,0);
            for(int index = 0;index<8;index++)
            {
                int bitset = (m_map[i] & (1<<index));
                if(bitset)
                    color += colorArray[index];
            }
            glColor3f(color.x(),color.y(),color.z());
            glBegin(GL_POLYGON);
            glVertex3f(x*m_celResX,          y*m_celResY,               0);
            glVertex3f(x*m_celResX,          y*m_celResY+m_celResY*0.5f,0);
            glVertex3f(x*m_celResX+m_celResX,y*m_celResY+m_celResY*0.5f,0);
            glVertex3f(x*m_celResX+m_celResX,y*m_celResY,               0);
            glEnd();

            color = Point3f(0,0,0);
            //get colors for direction
            int direction = m_map[i]>>8;
            if(direction & DIR_LEFT)
                color = colorArray[COLOR_SILVER];//left
            if(direction & DIR_RIGHT)
                color = colorArray[COLOR_PURPLE];//right
            glColor3f(color.x(),color.y(),color.z());
            glBegin(GL_POLYGON);
            glVertex3f(x*m_celResX,               y*m_celResY+m_celResY*0.5f,0);
            glVertex3f(x*m_celResX,               y*m_celResY+m_celResY,     0);
            glVertex3f(x*m_celResX+m_celResX*0.5f,y*m_celResY+m_celResY,     0);
            glVertex3f(x*m_celResX+m_celResX*0.5f,y*m_celResY+m_celResY*0.5f,0);
            glEnd();
            
            color = Point3f(0,0,0);
            if(direction & DIR_UP)
                color = colorArray[COLOR_OLIVE];//up
            if(direction & DIR_DOWN)
                color = colorArray[COLOR_TEAL];//down
            
            glColor3f(color.x(),color.y(),color.z());
            glBegin(GL_POLYGON);
            glVertex3f(x*m_celResX+m_celResX*0.5f,y*m_celResY+m_celResY*0.5f,0);
            glVertex3f(x*m_celResX+m_celResX*0.5f,y*m_celResY+m_celResY,     0);
            glVertex3f(x*m_celResX+m_celResX,     y*m_celResY+m_celResY,     0);
            glVertex3f(x*m_celResX+m_celResX,     y*m_celResY+m_celResY*0.5f,0);
            glEnd();
        }
    }
    glDisable(GL_BLEND);	
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

//---------------------------------------------------------
void BitwiseInfluenceMap::StampInfluenceShape(int* pMap,Point3f& location,int sizeX, int sizeY, int value, bool undo)
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
            if(undo)
                pMap[(y%m_dataSizeY)*m_dataSizeY + (x%m_dataSizeX)] &= ~value;
            else
                pMap[(y%m_dataSizeY)*m_dataSizeY + (x%m_dataSizeX)] |= value;
        }
    }
}

//---------------------------------------------------------
int BitwiseInfluenceMap::GetInfluenceType(int* pMap,Point3f& location)
{
    int gridX = location.x()/ m_celResX;
    int gridY = location.y()/ m_celResY;
    return pMap[gridX,gridY] & 0x0f;
}

//---------------------------------------------------------
int BitwiseInfluenceMap::GetInfluenceDirection(int* pMap,Point3f& location)
{
    int gridX = location.x()/ m_celResX;
    int gridY = location.y()/ m_celResY;
    return pMap[gridX,gridY] >> 8;
}
