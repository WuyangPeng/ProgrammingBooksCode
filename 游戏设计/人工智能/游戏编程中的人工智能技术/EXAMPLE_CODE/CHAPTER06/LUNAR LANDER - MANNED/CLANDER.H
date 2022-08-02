#ifndef CLANDER_H
#define CLANDER_H

//-----------------------------------------------------------------------
//
//  Name: CLander.h
//
//  Author: Mat Buckland 2002
//
//	Desc: A class to define a lunar lander object
//
//-----------------------------------------------------------------------

#include "windows.h"
#include <vector>

#include "utils.h"
#include "defines.h"
#include "CTimer.h"
#include "SVector2D.h"
#include "C2DMatrix.h"

using namespace std;


class CLander
{
private:
	
	//position in world
	SVector2D		        m_vPos;
	
  //rotation in the world
	double			        m_dRotation;

	//scaling factor for rendering ship
  double			        m_dScale;
	
	//ships mass
  double			        m_dMass;

  //and velocity
  SVector2D		        m_vVelocity;
        
  //need to know where landing pad is for collision detection
  SVector2D           m_vPadPos;
	
	//buffer to store the ships vertices
  vector<SPoint>      m_vecShipVB;

  //buffer to hold our transformed vertices
  vector<SPoint>      m_vecShipVBTrans;

  //and the jets vertices
  vector<SPoint>      m_vecJetVB;
  vector<SPoint>      m_vecJetVBTrans;

  //we use this to determine whether to render the ships jet or not
  //(if the user is pressing thrust then the jet is rendered)
  bool                m_bJetOn;

  //local copy of client window size
	int				          m_cxClient;
	int				          m_cyClient;

  //used to flag whether or not we have already tested for success
  //or failure
  bool                m_bCheckedIfLanded;


	//returns true if the user has satisfied all the conditions for landing
  bool    LandedOK();

	//tests if any vertex of the ship is below the level of the landing
  //platform
  bool	  TestForImpact(vector<SPoint> &ship);

  //this function transforms the ships vertices so we can display them
  void WorldTransform(vector<SPoint> &ship);



public:

	CLander(int       cxClient, //so we can keep a local record 
          int       cyClient, //of the window dimensions
          double    rot,      //starting rotation of lander
          SVector2D pos,      //starting position of lander
          SVector2D pad);     //landing pad position
  
	void Render(HDC &surface);

  //resets all relevant variables for the start of a new attempt
  void Reset(SVector2D &NewPadPos);

  //updates the ship from a keypress
  void  UpdateShip(double TimeElapsed);

};
	
	


#endif