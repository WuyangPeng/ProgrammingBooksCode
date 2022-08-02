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
			if(Game.m_state == GameSession::STATE_PLAY)
				Game.UseControl(GameSession::CONTROL_SHOOT);
			else if(Game.m_state == GameSession::STATE_NEXTWAVE)
				Game.StartNextWave();
            else if(Game.m_state == GameSession::STATE_STEPWAIT)
                Game.m_state = GameSession::STATE_STEP;
			break;
		case 'h':
			if(Game.m_state == GameSession::STATE_PLAY)
				Game.UseControl(GameSession::CONTROL_HYPERSPACE);	 
			break;
		
		//handle pause controls
		case 'p':
			if(Game.m_state != GameSession::STATE_GAMEOVER)
				Game.UseControl(GameSession::CONTROL_PAUSE);
			break;

        //handle "step" controls
        case 's':
            if(Game.m_state != GameSession::STATE_GAMEOVER)
                Game.UseControl(GameSession::CONTROL_STEP);
            break;
            
		//handle game over controls
		case 'y':
			if(Game.m_state == GameSession::STATE_GAMEOVER)
				Game.StartGame();
			break;
		case 'n':
			if(Game.m_state == GameSession::STATE_GAMEOVER)
				exit(0);
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
	case 'a':
		if(Game.m_AIOn)
			Game.UseControl(GameSession::CONTROL_AI_OFF);
		else
			Game.UseControl(GameSession::CONTROL_AI_ON);
		break;
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

//---------------------------------------------------------
// Glut Callback for down/up events of arrow keys.
void  SpecialKey(int key, int x, int y)
{
	if(Game.m_state != GameSession::STATE_PLAY)
		return;
	
	switch (key) 
	{
	case GLUT_KEY_LEFT: 
		Game.UseControl(GameSession::CONTROL_LEFT_ON);	 
		break;
	case GLUT_KEY_RIGHT: 
		Game.UseControl(GameSession::CONTROL_RIGHT_ON);	 
		break;
	case GLUT_KEY_UP: 
		Game.UseControl(GameSession::CONTROL_THRUST_ON);	 
		break;
	case GLUT_KEY_DOWN: 
		Game.UseControl(GameSession::CONTROL_STOP);	 
//		Game.UseControl(GameSession::CONTROL_THRUST_REVERSE);	 
		break;
	default:
		break;
	}
}

//---------------------------------------------------------
void SpecialKeyUp(int key, int x, int y)
{
	if(Game.m_state != GameSession::STATE_PLAY)
		return;
	
	switch (key) 
	{
	case GLUT_KEY_RIGHT: 
	case GLUT_KEY_LEFT: 
		Game.UseControl(GameSession::CONTROL_STOP_TURN);	 
		break;
	case GLUT_KEY_UP: 
	case GLUT_KEY_DOWN: 
		Game.UseControl(GameSession::CONTROL_THRUST_OFF);	 
		break;
	default:
		break;
	}
}
