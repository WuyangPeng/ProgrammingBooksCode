#ifndef CMINESWEEPER_H
#define CMINESWEEPER_H

//------------------------------------------------------------------------
//
//	Name: CMineSweeper.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Class to create a minesweeper object 
//
//------------------------------------------------------------------------
#include <vector>
#include <math.h>

#include "phenotype.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"
#include "collision.h"
#include "CMapper.h"



using namespace std;


class CMinesweeper
{

private:

  CNeuralNet*  m_pItsBrain; 
  
  //its memory
  CMapper     m_MemoryMap;

  //its position in the world
	SVector2D		m_vPosition;

	//direction sweeper is facing
	SVector2D		m_vLookAt;

	//how much it is rotated from its starting position
	double			m_dRotation;

	double			m_dSpeed;

	//to store output from the ANN
	double			m_lTrack, m_rTrack;

	//the sweepers fitness score. 
	double			m_dFitness;

	//the scale of the sweeper when drawn
	double			m_dScale;
  
  //to store end vertices of sensor segments
  vector<SPoint>  m_Sensors;
  vector<SPoint>  m_tranSensors;

  //this keeps a record of how far down the sensor segment
  //a 'hit' has occurred.
  vector<double>  m_vecdSensors;

  //the end points of the sensors check their coordinate
  //cell to see how many times the sweeper has visited it.
  vector<double>  m_vecFeelers;

  //if a collision has been detected this flag is set
  bool            m_bCollided;


  void      CreateSensors(vector<SPoint> &sensors,
                          int            NumSensors,
                          double         range);

  int       CheckForHit(vector<SVector2D> &objects, double size);

  void      TestSensors(vector<SPoint> &objects);

  void      TestRange();
  

public:
	
  
	CMinesweeper();
	
	//updates the ANN with information from the sweepers enviroment
	bool			Update(vector<SPoint> &objects);

	//used to transform the sweepers vertices prior to rendering
  void			WorldTransform(vector<SPoint> &sweeper, double scale);

	void			Reset();

  void      EndOfRunCalculations();

  void      RenderStats(HDC surface);
  
  void      Render(HDC surface);

  void      DrawNet(HDC &surface, int cxLeft, int cxRight, int cyTop, int cyBot)
  {
    m_pItsBrain->DrawNet(surface, cxLeft, cxRight, cyTop, cyBot);
  }


	//-------------------accessor functions
	SVector2D	        Position()const{return m_vPosition;}

  double            Rotation()const{return m_dRotation;}

	float			        Fitness()const{return m_dFitness;}

  double            Scale()const{return m_dScale;}

  vector<SPoint>&   Sensors(){return m_tranSensors;}

  vector<double>&   SensorReadings(){return m_vecdSensors;}

  bool              Collided()const{return m_bCollided;}

  vector<double>    MemoryReadings(){return m_vecFeelers;}

  int               NumCellsVisited(){return m_MemoryMap.NumCellsVisited();}

  void              InsertNewBrain(CNeuralNet* brain){m_pItsBrain = brain;}
 
};


#endif

	
	