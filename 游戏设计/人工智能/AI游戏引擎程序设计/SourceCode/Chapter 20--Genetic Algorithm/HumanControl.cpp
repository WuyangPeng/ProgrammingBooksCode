#include "HumanControl.h"
#include "GameSession.h"
#include "Ship.h"
#include "utility.h"
#include <GL/glut.h>

//---------------------------------------------------------
HumanControl::HumanControl(Ship* ship):
Control(ship)
{
	if(m_ship)
		m_ship->m_control = this;
	m_type = CONTROLTYPE_HUMAN;
}


//---------------------------------------------------------
//Global functions used for GLUT keyboard callbacks--------
//---------------------------------------------------------

//---------------------------------------------------------
// Glut Callback for down event of normal key input.
void Key(unsigned char key, int x, int y)
{
	switch (tolower(key)) 
	{
		//handle normal controls
		case 27:
			exit(0);
			break;
		case ' ':
			if(Game.m_state == GameSession::STATE_STEPWAIT)
                Game.m_state = GameSession::STATE_STEP;
			break;
		//handle pause controls
		case 'p':
			if(Game.m_state != GameSession::STATE_GAMEOVER)
				Game.UseControl(GameSession::CONTROL_PAUSE);
			break;

        //handle "step" controls
        case 'r':
            if(Game.m_state != GameSession::STATE_GAMEOVER)
                Game.UseControl(GameSession::CONTROL_RESTART);
            break;
        
        //handle "step" controls
        case 's':
            if(Game.m_state != GameSession::STATE_GAMEOVER)
                Game.UseControl(GameSession::CONTROL_STEP);
            break;
        default:
			break;
	}
}

//---------------------------------------------------------
// Glut Callback for up event of normal key input.
void KeyUp(unsigned char key, int x, int y)
{
	switch (tolower(key) )
	{
        case '.':
            if(Game.m_state == GameSession::STATE_PLAY)
                Game.m_timeScale++;
            break;
        case ',':
            if(Game.m_state == GameSession::STATE_PLAY)
                Game.m_timeScale = MAX(1,Game.m_timeScale-1);
            break;
        default:
            break;
    }
}

