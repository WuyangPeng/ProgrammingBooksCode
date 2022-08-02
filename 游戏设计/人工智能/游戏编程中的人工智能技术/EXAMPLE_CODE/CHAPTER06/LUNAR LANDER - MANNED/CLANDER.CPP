#include "CLander.h"

//this defines the vertices for the lander shape
const int	 NumLanderVerts = 30;

const SPoint lander[NumLanderVerts] = {//middle of lander
                                       SPoint(-1, 0),
                                       SPoint(1, 0),    
                                       SPoint(1, -0.5),
                                       SPoint(-1, -0.5),
                                       //top of lander
                                       SPoint(-0.5, 0),
                                       SPoint(-1, 0.3),
                                       SPoint(-1, 0.7),
                                       SPoint(-0.5, 1),
                                       SPoint(0.5, 1),
                                       SPoint(1, 0.7),
                                       SPoint(1, 0.3),
                                       SPoint(0.5, 0),
                                       //legs
                                       SPoint(-1, -0.4),
                                       SPoint(-1.3, -0.8),
                                       SPoint(-1.3, -1.2),
                                       SPoint(-1.5, -1.2),
                                       SPoint(-1.1, -1.2),
                                       SPoint(-0.9, -0.5),
                                       SPoint(-1.3, -0.8),

                                       SPoint(1, -0.4),
                                       SPoint(1.3, -0.8),
                                       SPoint(1.3, -1.2),
                                       SPoint(1.5, -1.2),
                                       SPoint(1.1, -1.2),
                                       SPoint(0.9, -0.5),
                                       SPoint(1.3, -0.8),
                                       //rocket
                                       SPoint(-0.2, -0.5),
                                       SPoint(-0.3, -0.8),
                                       SPoint(0.3, -0.8),
                                       SPoint(0.2, -0.5)};

//and the vertices for the jet
const NumJetVerts = 5;

const SPoint jet[NumJetVerts] = {SPoint(-0.1, -0.9),
                                 SPoint(-0.2, -1.2),
                                 SPoint(0, -1.6),
                                 SPoint(0.2, -1.2),
                                 SPoint(0.1, -0.9)};



                                       

//macro for the user input when controlling a ship manually
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//----------------------------------- ctor -------------------------------
//
//------------------------------------------------------------------------

CLander::CLander(int       cxClient,
				         int       cyClient,
				         double    rot,
                 SVector2D pos,
                 SVector2D pad):m_vPos(pos),
                                m_vPadPos(pad),
                                m_vVelocity(SVector2D(0,0)),
  						                  m_dRotation(rot),
						                    m_dMass(SHIPS_MASS),
						                    m_dScale(LANDER_SCALE),
						                    m_cxClient(cxClient),
						                    m_cyClient(cyClient),
                                m_bCheckedIfLanded(false)
                           
{

   //set up the vertex buffer for the lander shape
  for (int i=0; i<NumLanderVerts; ++i)
	{
		m_vecShipVB.push_back(lander[i]);
	}

  m_vecShipVBTrans = m_vecShipVB;

  //and for the jet shape
  for (i=0; i<NumJetVerts; ++i)
  {
    m_vecJetVB.push_back(jet[i]);
  }

  m_vecJetVBTrans = m_vecJetVB;
}

//------------------------Reset-------------------------------------
//
//	just resets variables back to starting position
//------------------------------------------------------------------
void CLander::Reset(SVector2D &NewPadPos)
{
	m_vPos		     = SVector2D(WINDOW_WIDTH/2, m_cyClient-50);
	m_dRotation	   = PI;
	m_vVelocity.x  = 0;
	m_vVelocity.y  = 0;
  m_vPadPos      = NewPadPos;
  m_bCheckedIfLanded = false;

}


//---------------------WorldTransform--------------------------------
//
//	sets up the translation matrices for the ship and applies the
//	world transform to the ships vertex buffer
//-------------------------------------------------------------------
void CLander::WorldTransform(vector<SPoint> &ship)
{
	//create a transformation matrix
	C2DMatrix matTransform;
	
	//scale
	matTransform.Scale(m_dScale, m_dScale);

	//rotate -  remember, because the mapping mode is set so that the y
  //axis is pointing up, the rotation is reversed.
	matTransform.Rotate(-m_dRotation);

	//and translate
	matTransform.Translate(m_vPos.x, m_vPos.y);
	
  //now transform the ships vertices
  matTransform.TransformSPoints(ship);

}


//----------------------TestForImpact------------------------------
//
//	checks each vertex of the ship to see if it's reached ground-
//	level.
//-----------------------------------------------------------------
bool CLander::TestForImpact(vector<SPoint> &ship)
{
	const int GroundLevel = 55;

  for (int vrtx=0; vrtx<ship.size(); ++vrtx)
	{
		if ( (ship[vrtx].y) < GroundLevel)
		{
			return true;
			
		}
	}

  return false;
}

//-----------------------LandedOK------------------------------------
//
// calculates if the ship has made it down safetly or not.
//-------------------------------------------------------------------
bool CLander::LandedOK()
{

	//calculate distance from pad
  double DistFromPad = fabs(m_vPadPos.x - m_vPos.x);
  
  //calculate speed of lander
  double speed = sqrt((m_vVelocity.x*m_vVelocity.x) 
					           +(m_vVelocity.y*m_vVelocity.y));


  //check if we have a successful landing
  if( (DistFromPad            < DIST_TOLERANCE)       && 
      (speed                  < SPEED_TOLERANCE)      && 
      (fabs(m_dRotation)      < ROTATION_TOLERANCE))
  {
    return true;
  }

  return false;
}

//------------------------- Render ---------------------------------------
//
//------------------------------------------------------------------------
void CLander::Render(HDC &surface)
{
   
  //draw the vertices for the landers base
	MoveToEx(surface, (int)m_vecShipVBTrans[0].x, (int)m_vecShipVBTrans[0].y, NULL);

	for (int vert=1; vert<4; ++vert)
	{
		LineTo(surface, (int)m_vecShipVBTrans[vert].x, (int)m_vecShipVBTrans[vert].y);
	}
  
  LineTo(surface, (int)m_vecShipVBTrans[0].x, (int)m_vecShipVBTrans[0].y);

  //landers top
  MoveToEx(surface, (int)m_vecShipVBTrans[4].x, (int)m_vecShipVBTrans[4].y, NULL);

  for (vert=5; vert<12; ++vert)
	{
		LineTo(surface, (int)m_vecShipVBTrans[vert].x, (int)m_vecShipVBTrans[vert].y);
	}

  //left leg
  MoveToEx(surface, (int)m_vecShipVBTrans[12].x, (int)m_vecShipVBTrans[12].y, NULL);
  LineTo(surface, (int)m_vecShipVBTrans[13].x, (int)m_vecShipVBTrans[13].y);
  LineTo(surface, (int)m_vecShipVBTrans[14].x, (int)m_vecShipVBTrans[14].y);
  MoveToEx(surface, (int)m_vecShipVBTrans[15].x, (int)m_vecShipVBTrans[15].y, NULL);
  LineTo(surface, (int)m_vecShipVBTrans[16].x, (int)m_vecShipVBTrans[16].y);
  MoveToEx(surface, (int)m_vecShipVBTrans[17].x, (int)m_vecShipVBTrans[17].y, NULL);
  LineTo(surface, (int)m_vecShipVBTrans[18].x, (int)m_vecShipVBTrans[18].y);

  //right leg
  MoveToEx(surface, (int)m_vecShipVBTrans[19].x, (int)m_vecShipVBTrans[19].y, NULL);
  LineTo(surface, (int)m_vecShipVBTrans[20].x, (int)m_vecShipVBTrans[20].y);
  LineTo(surface, (int)m_vecShipVBTrans[21].x, (int)m_vecShipVBTrans[21].y);
  MoveToEx(surface, (int)m_vecShipVBTrans[22].x, (int)m_vecShipVBTrans[22].y, NULL);
  LineTo(surface, (int)m_vecShipVBTrans[23].x, (int)m_vecShipVBTrans[23].y);
  MoveToEx(surface, (int)m_vecShipVBTrans[24].x, (int)m_vecShipVBTrans[24].y, NULL);
  LineTo(surface, (int)m_vecShipVBTrans[25].x, (int)m_vecShipVBTrans[25].y);

  //the burner
  MoveToEx(surface, (int)m_vecShipVBTrans[26].x, (int)m_vecShipVBTrans[26].y, NULL);
  for (vert=27; vert<30; ++vert)
	{
		LineTo(surface, (int)m_vecShipVBTrans[vert].x, (int)m_vecShipVBTrans[vert].y);
	}

  //if the last action was thrust then we need to draw the jet from the burner
  if (m_bJetOn)
  {
    //first transform the verts 
    m_vecJetVBTrans = m_vecJetVB;

    WorldTransform(m_vecJetVBTrans);

    MoveToEx(surface, m_vecJetVBTrans[0].x, m_vecJetVBTrans[0].y, NULL);

    for (int vert=1; vert<m_vecJetVBTrans.size(); ++vert)
    {
      LineTo(surface, m_vecJetVBTrans[vert].x, m_vecJetVBTrans[vert].y);
    }
  }

  if (m_bCheckedIfLanded)
  {
    if(LandedOK())
    {
      string s = "Great Landing!";
      TextOut(surface, 150, 160, s.c_str(), s.size());
    }

    else
    {
      string s = "Crashed!";
      TextOut(surface, 160, 160, s.c_str(), s.size());
    }
  }
}
//-----------------------UpdateShip---------------------------------------
//
//	first checks if user is pressing an action key then updates the physics
//  and tests to see if the ship has landed or not.
//------------------------------------------------------------------------
void CLander::UpdateShip(double TimeElapsed)
{
  //just return if ship has crashed or landed
  if (m_bCheckedIfLanded)
  {
    return;
  }
  
  //switch the jet graphic off
  m_bJetOn = false;
  	
	//test for user input and update accordingly
	if (KEYDOWN(VK_SPACE))
	{
    //the lander's acceleration per tick calculated from the force the
    //thruster exerts, the lander's mass and the time elapsed since the
    //last frame
    double ShipAcceleration = (THRUST_PER_SECOND * TimeElapsed) / m_dMass;

		//resolve the acceleration vector into its x, y components
    //and add to the lander's velocity vector
    m_vVelocity.x += ShipAcceleration * sin(m_dRotation);
		m_vVelocity.y += ShipAcceleration * cos(m_dRotation);

    //switch the jet graphic on
    m_bJetOn = true;
	}
  
	if (KEYDOWN(VK_LEFT))
	{
		m_dRotation -= ROTATION_PER_SECOND * TimeElapsed;

		if (m_dRotation < -PI)
		{
			m_dRotation += 2*PI;
		}
		
	}

	if (KEYDOWN(VK_RIGHT))
	{
	
		m_dRotation += ROTATION_PER_SECOND * TimeElapsed;

		if (m_dRotation > 2*PI)
		{
			m_dRotation -= 2*PI;
		}
		
	}

	
  //now add in the gravity vector
	m_vVelocity.y += GRAVITY * TimeElapsed;

	//update the lander's position
  m_vPos += m_vVelocity * TimeElapsed * SCALING_FACTOR;

  

	//bounds checking
	if (m_vPos.x > WINDOW_WIDTH)
	{
		m_vPos.x = 0;
	}

	if (m_vPos.x < 0)
	{
		m_vPos.x = WINDOW_WIDTH;
	}


  //now we check to see if the lander has crashed or landed
  
  //create a copy of the landers verts before we transform them
	m_vecShipVBTrans = m_vecShipVB;

	//transform the vertices
  WorldTransform(m_vecShipVBTrans);

	//if we are lower than the ground then we have finished this run
	if (TestForImpact(m_vecShipVBTrans))
  {
    //check if user has landed ship
    if (!m_bCheckedIfLanded)
    {
      if(LandedOK())
      {
        PlaySound("landed", NULL, SND_ASYNC|SND_FILENAME);;
      }

      else
      {
        PlaySound("explosion", NULL, SND_ASYNC|SND_FILENAME);
      }

      m_bCheckedIfLanded = true;
    }

  }

  return;	
}

