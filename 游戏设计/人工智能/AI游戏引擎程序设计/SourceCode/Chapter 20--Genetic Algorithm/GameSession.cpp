#include <GL/glut.h>
#include <stdlib.h>
#pragma warning(disable: 4786)
#include <algorithm>

#include "Bullet.h"
#include "Ship.h"
#include "Ast.h"
#include "Exp.h"
#include "Powerup.h"
#include "GameSession.h"
#include "utility.h"
#include "HumanControl.h"
#include "GAAIControl.h"
#include "GAMachine.h"

#define INITIAL_WORLD_SIZE 512

//---------------------------------------------------------
GameSession::GameSession()
{
    m_mainShip		= NULL;
    m_AIControl    = new GAAIControl();
    m_AIOn         = true;
    m_timeScale    = 1;
    m_humanControl = new HumanControl();
}

//---------------------------------------------------------
void GameSession::Draw()
{
	GameObjectList::iterator li;
	switch(m_state)
	{
		case STATE_STEPWAIT:
		case STATE_STEP:
		case STATE_PLAY:
			for(li=m_activeObj.begin();li!=m_activeObj.end();++li)
			{
				GameObj* temp = *li;
                GameObj* temp2;
                li++;
                if(li != m_activeObj.end())
                {
                    temp2 = *li;
                }
                li--;
				if((*li)->m_active)
					(*li)->Draw();	
			}
			glPrintf(COLOR_GREEN,5,Game.m_screenH-20,20,"Score: %d\n",m_score);
			DrawLives();
			if(m_AIOn)//debug text drawing
			{
				glPrintf(COLOR_GREEN,5,20,20,"AI ON\n");
				glPrintf(COLOR_GREEN,80,20,20,"%s\n",m_AIControl->m_debugTxt);
				m_AIControl->m_debugTxt = "";
			}
			break;
		case STATE_PAUSE:
			glPrintf(COLOR_BLUE,30,Game.m_screenH-100,75,"Game Paused\n");
			glPrintf(COLOR_BLUE,30,Game.m_screenH-200,75,"  Press p\n");
			break;
		case STATE_GAMEOVER:
			glPrintf(COLOR_RED,30,Game.m_screenH-100,75,"Game Over\n");
			glPrintf(COLOR_WHITE,30,Game.m_screenH-200,60,"Start Again(y/n)\n");
			glPrintf(COLOR_GREEN,30,Game.m_screenH-300,40,"Final Score: %d\n",m_score);
			break;
		case STATE_NEXTWAVE:
			glPrintf(COLOR_RED,30,Game.m_screenH-100,70,"Wave Completed\n");
			glPrintf(COLOR_WHITE,30,Game.m_screenH-200,60,"Press Space Bar\n");
			if(m_AIOn)
				Game.StartNextWave();
			break;
		default:
			break;
	}
    glFinish();
}

//---------------------------------------------------------
void GameSession::DrawLives()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glRotatef(90.0f,0,0,1);
	if(m_numLives <= 10)
    {	//life triangles
        
		Point3f location(m_screenW-15,-m_screenH + 10,0);
		glTranslate(location);
        glScalef(3,3,1);
        for(int i = 1;i< m_numLives;i++)
		{
			glBegin(GL_LINE_LOOP);
			glColor3f(.5,.5,.5);
			glVertex3f(-3,-2+(10*i),0);
			glVertex3f( 4, 0+(10*i),0);
			glVertex3f(-3, 2+(10*i),0);
			glEnd();
		}
	}
	else//just put up a number for more then 10 extra lives
	{
		glPrintf(COLOR_GREEN,Game.m_screenW-30,Game.m_screenH-20,20,"%d\n",m_numLives-1);
		Point3f location(m_screenW-15,-m_screenH +40,0);
		glTranslate(location);
        glScalef(3,3,1);
        glBegin(GL_LINE_LOOP);
		glColor3f(.5,.5,.5);
		glVertex3f(-3,-2,0);
		glVertex3f( 4, 0,0);
		glVertex3f(-3, 2,0);
		glEnd();
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
}

//---------------------------------------------------------
void GameSession::Clip(Point3f &p)
{
	if(p.x() > m_screenW) p.x() -=m_screenW; 
	if(p.y() > m_screenH) p.y() -=m_screenH; 
	if(p.x() < 0)         p.x() +=m_screenW; 
	if(p.y() < 0)         p.y() +=m_screenH; 
}

//---------------------------------------------------------
void GameSession::PostGameObj(GameObj *obj)
{
    m_activeObj.push_back(obj);
}


//---------------------------------------------------------
bool RemoveNotActive(GameObj* obj)
{
    if(!obj->m_active)
    {
        delete obj;
        return true;
    }
    return false;
}
    
//---------------------------------------------------------
void GameSession::Update(float dt)
{
    m_timeInGeneration+= dt;
    GameObjectList::iterator list1;
    for(list1=m_activeObj.begin();list1!=m_activeObj.end();++list1)
    {
        GameObj* temp = *list1;
        //update logic and positions
        if((*list1)->m_active)
        {
            (*list1)->Update(dt);
            Clip((*list1)->m_position);
        }
        else continue;
        
        //check for collisions, but don't actually kill off colliders
        if((*list1)->m_collisionFlags != GameObj::OBJ_NONE)
        {
            GameObjectList::iterator list2;
            for(list2=m_activeObj.begin();list2!=m_activeObj.end();++list2)
            {
                //the first obj may have already collided with something, making it inactive
                if(!(*list1)->m_active)
                    continue;
                
                //don't collide with yourself
                if(list1 == list2)
                    continue;
                
                if((*list2)->m_active							   && 
                    ((*list1)->m_collisionFlags & (*list2)->m_type) && 
                    (*list1)->IsColliding(*list2)) 
                {
                    (*list1)->DoCollision((*list2));
                }
            }
        }
        if(list1==m_activeObj.end()) break;
    }
    
    m_humanControl->Update(dt);
    m_AIControl->Update(dt);
}

//---------------------------------------------------------
void GameSession::UseControl(int control)
{
    switch(control)
    {
    case CONTROL_RESTART:
        m_AIControl->Reset();
        break;
    case CONTROL_STEP:
        if(m_state == STATE_STEPWAIT || m_state == STATE_STEP)
            m_state = STATE_PLAY;
        else
            m_state = STATE_STEP;
        break;
    default:
        break;
    }
}

//---------------------------------------------------------
void GameSession::StartGame()
{
    m_AIControl->Init();
    
    //create all the game objects 
    for(int i = 0;i< POPULATION_SIZE;i++)
    {
        Ship* temp = new Ship();
        m_ships.push_back(temp);
        temp->m_position.x()= randflt()*m_screenW;	
        temp->m_position.y()= randflt()*m_screenH;
        temp->m_position.z()= 0;
        PostGameObj(temp);
    }
    
    for(i = 0;i< NUM_ASTERIODS;i++)
    {
        Ast* temp = new Ast(8*(1+rand()%10));
        temp->m_position.x()= randflt()*m_screenW;	
        temp->m_position.y()= randflt()*m_screenH;
        temp->m_position.z()= 0;
        temp->m_velocity.x()= randflt()*70 - 30;	
        temp->m_velocity.y()= randflt()*70 - 30;
        temp->m_velocity.z()= 0;
        PostGameObj(temp);
    }
    m_state = STATE_PLAY;
}

//---------------------------------------------------------
void GameSession::StartNextWave()
{
	m_state			= STATE_PLAY;
	LaunchAsteroidWave();	
}

//---------------------------------------------------------
void GameSession::LaunchAsteroidWave()
{
	Ast *a;
	for(int i=0;i<2*m_waveNumber;i++)
	{
        a=new Ast(8*(1+rand()%10));
		do
		{
			a->m_position.x()= randflt()*m_screenW;	
			a->m_position.y()= randflt()*m_screenH;
		}
		while( m_mainShip && a->IsColliding(m_mainShip));
		a->m_position.z()= 0;
		a->m_velocity.x()= randflt()*70 - 30;	
		a->m_velocity.y()= randflt()*70 - 30;
		a->m_velocity.z()= 0;
		PostGameObj(a);
		m_numAsteroids++;
	}
}

//---------------------------------------------------------
void GameSession::GameOver()
{
	//kill everything
	GameObjectList::iterator list1;
	for(list1=m_activeObj.begin();list1!=m_activeObj.end();++list1)
	{
		GameObj* temp = *list1;
		delete temp;
	}
	m_activeObj.clear();
	m_state = STATE_GAMEOVER;
}

//---------------------------------------------------------
bool RemoveBulletOrExplosion(GameObj* obj)
{
	if(obj->m_type == GameObj::OBJ_BULLET || obj->m_type == GameObj::OBJ_EXP)
	{
        delete obj;
		return true;
	}
	return false;
}

//---------------------------------------------------------
void GameSession::WaveOver()
{
	//kill all the bullets and explosions
	GameObjectList::iterator end    = m_activeObj.end();
	GameObjectList::iterator newEnd = remove_if(m_activeObj.begin(),m_activeObj.end(),RemoveBulletOrExplosion);
	if(newEnd != end)
		m_activeObj.erase(newEnd,end);
	
	//reset the main ship stuff
	if(m_mainShip)
		m_mainShip->Init();
	m_state = STATE_NEXTWAVE;
}

//---------------------------------------------------------
void GameSession::KillShip(GameObj *ship)
{
	if(!ship)
		return;
	
	if(ship == m_mainShip)
	{
		m_mainShip = NULL;
		m_humanControl->m_ship = NULL;
		m_AIControl->m_ship = NULL;
		m_numLives--;
	}
	
	//go through the obj list and make sure nobody is still pointing to
	//this ship
	GameObjectList::iterator list1;
	for(list1=m_activeObj.begin();list1!=m_activeObj.end();++list1)
	{
		if((*list1)->m_type == GameObj::OBJ_BULLET && ((Bullet*)(*list1))->m_parent == ship)
            ((Bullet*)(*list1))->m_parent = NULL;
    }
    
}

//---------------------------------------------------------
GameObj* GameSession::GetClosestGameObj(GameObj* obj, int type)
{
    //go through the list, find the closest object of param "type"
    //to the param "obj"
    float closeDist = 100000000.0f;
    GameObj* closeObj = NULL;
    
    GameObjectList::iterator list1;
    for(list1=m_activeObj.begin();list1!=m_activeObj.end();++list1)
    {
        //watch out for yourself
        if(*list1 == obj)
            continue;
        
        float dist = (*list1)->m_position.Distance(obj->m_position);
        if((*list1)->m_type == type && dist< closeDist)
        {
            closeDist = dist;
            closeObj = *list1;
        }
    }
    return closeObj;
    
}

//---------------------------------------------------------
GameObj* GameSession::GetClosestGameObj(Point3f &point, int type)
{
    //go through the list, find the closest object of param "type"
    //to the param "point"
    float closeDist = 100000000.0f;
    GameObj* closeObj = NULL;
    
    GameObjectList::iterator list1;
    for(list1=m_activeObj.begin();list1!=m_activeObj.end();++list1)
    {
        float dist = (*list1)->m_position.Distance(point);
        if((*list1)->m_type == type && dist< closeDist)
        {
            closeDist = dist;
            closeObj = *list1;
        }
    }
    return closeObj;
    
}

//---------------------------------------------------------
int GameSession::GetNumGameObj(int type)
{
    //go through the list, count up all the objects of param "type"
    //to the param "point"
    int count =0;
    GameObjectList::iterator list1;
    for(list1=m_activeObj.begin();list1!=m_activeObj.end();++list1)
    {
        if((*list1)->m_type == type)
            count++;
    }
    return count;
    
}

//---------------------------------------------------------
void GameSession::ApplyForce(int type, Point3f &force, float dt)
{
    GameObjectList::iterator list1;
    for(list1=m_activeObj.begin();list1!=m_activeObj.end();++list1)
    {
        if((*list1)->m_type != type)
            continue;
        
        (*list1)->m_velocity += force*dt;
    }
}

//---------------------------------------------------------
void GameSession::ApplyForce(int type,Point3f &p1, Point3f &p2, Point3f &force, float dt)
{
    GameObjectList::iterator list1;
    for(list1=m_activeObj.begin();list1!=m_activeObj.end();++list1)
    {
        if((*list1)->m_type != type)
            continue;

        //check if the object is colliding with 
        //the force line segment
        if((*list1)->m_boundSphere.Intersect(p1,p2))
            (*list1)->m_velocity += force*dt;
    }
}

