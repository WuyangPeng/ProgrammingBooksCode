#ifndef CLANDER_H
#define CLANDER_H

//-----------------------------------------------------------------------
//  
//  Name: CLander.h
//  
//  Author: Mat Buckland 2002
//
//  Desc: The Lander Class for the Lunar Lander example program
//
//------------------------------------------------------------------------


#include "windows.h"
#include <vector>

#include "utils.h"
#include "defines.h"
#include "CTimer.h"
#include "S2DVector.h"
#include "C2DMatrix.h"

using namespace std;

//enumerate a type for each different action the Lander can perform
enum action_type{rotate_left,
                 rotate_right,
                 thrust,
                 non};

//-------------------------------------------------------------------

struct SGene 
{
	
	action_type action;

	//duration the action is applied measured in ticks
  int       	duration;
	
	SGene()
	{
		//create a random move
		action = (action_type)RandInt(0,3);

		duration = RandInt(1, MAX_ACTION_DURATION);
	}

	SGene(action_type a, int d):action(a), duration(d){}

	//need to overload the == operator so we can test if actions are 
	//equal (used in the crossover process of the GA)
	bool operator==(const SGene &rhs) const
	{
		return (action == rhs.action) && (duration == rhs.duration);
	}

};

//-------------------------------------------------------------------

class CLander
{
private:
	
	//position in world
	SVector2D		m_vPos;

	//keep a record of the start position
	SVector2D		m_vStartPos;

  //need to know where landing pad is for collision detection
  SVector2D   m_vPadPos;
	
	SVector2D		m_vVelocity;
	
	double			m_dRotation;

	//keep a record of the start rotation
	double			m_dStartRotation;	
	
	double			m_dMass;

  //this will hold the horizontal position of the landing pad
  int         m_iPadX;
	
	//buffer to store the ships vertices
  vector<SPoint>  m_vecShipVB;

  //buffer to hold our transformed vertices
  vector<SPoint>  m_vecShipVBTrans;

  //and the jets vertices
  vector<SPoint>  m_vecJetVB;
  vector<SPoint>  m_vecJetVBTrans;

  //we use this to determine whether to render the ships
  //jet or not
  bool            m_bJetOn;

  //this will hold a series of actions decoded from
  //the ships chromosomes
  vector<action_type> m_vecActions;

  //the action counter. Tells us which is the current
  //action.
  int         m_cTick;

	//scaling factor for rendering ship
  double			m_dScale;


  //local copy of client window size
	int				  m_cxClient;
	int				  m_cyClient;

	//its fitness score
  double			m_dFitness;

  //used to flag whether or not we have already tested for success
  //or failure
  bool        m_bCheckedIfLanded;



	void    CalculateFitness();

	bool	  TestForImpact(vector<SPoint> &ship);

  void    WorldTransform(vector<SPoint> &ship);



public:

	CLander(int       cxClient, //so we can keep a local record 
          int       cyClient, //of the window dimensions
          double    rot,      //starting rotation of lander
          SVector2D pos,      //starting position of lander
          SVector2D pad);     //landing pad position

  
	void Render(HDC surface);

  bool UpdateShip();

  void Reset(SVector2D &NewPadPos);

  void Decode(const vector<SGene> &actions);
  

  //accessor methods
  SVector2D           Pos()const{return m_vPos;}
  vector<action_type> GetActionVector()const{return m_vecActions;}
  double              Fitness()const{return m_dFitness;}

};
	
	


#endif