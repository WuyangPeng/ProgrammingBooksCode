#ifndef CMINESWEEPER_H
#define CMINESWEEPER_H

//------------------------------------------------------------------------
//
//	Name: CMineSweeper.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Class to create a minesweeper object used in the 'Smart Sweeper'
//        example from the book Game AI Programming with Neural Nets and 
//        Genetic Algorithms.
//
//------------------------------------------------------------------------
#include <vector>
#include <math.h>

#include "CNeuralNet.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"
#include "collision.h"


using namespace std;


class CMinesweeper
{

private:

	CNeuralNet  m_ItsBrain;

  //its position in the world
	SVector2D		m_vPosition;

	//direction sweeper is facing
	SVector2D		m_vLookAt;

	double			m_dRotation;

	double			m_dSpeed;

	//to store output from the ANN
	double			m_lTrack, m_rTrack;

	//the sweepers energy level. 
	double			m_dFitness;

	//the scale of the sweeper when drawn
	double			m_dScale;

  //these members keep track of the individual penalties
  double      m_dSpinBonus;
  double      m_dCollisionBonus;
  
  //to store end vertices of sensor segments
  vector<SPoint>  m_Sensors;
  vector<SPoint>  m_tranSensors;

  //this keeps a record of how far down the sensor segment
  //a 'hit' has occurred.
  vector<double>  m_vecdSensors;

  //if a collision has been detected this flag is set
  bool            m_bCollided;


  //this function returns a vector of points which make up 
  //the line segments of the sweepers sensors.
  void      CreateSensors(vector<SPoint> &sensors,
                          int            NumSensors,
                          double         range);

  int       CheckForHit(vector<SVector2D> &objects, double size);

  //this function checks for any intersections between the
  //sweeper's sensors and the objects in its environment
  void      TestSensors(vector<SPoint> &objects);
  

public:
	
  
	CMinesweeper();
	
	//updates the ANN with information from the sweepers enviroment
	bool			Update(vector<SPoint> &objects);

	//used to transform the sweepers vertices prior to rendering
  void			WorldTransform(vector<SPoint> &sweeper, double scale);

	void			Reset();

  void      EndOfRunCalculations();

  void      RenderStats(HDC surface);
  
  void      RenderPenalties(HDC surface);




	//-------------------accessor functions
	SVector2D	        Position()const{return m_vPosition;}

  double            Rotation()const{return m_dRotation;}

	float			        Fitness()const{return m_dFitness;}

  void              ZeroEnergy(){m_dFitness = 0;}

  double            Scale()const{return m_dScale;}

  vector<SPoint>&   Sensors(){return m_tranSensors;}

  vector<double>&   SensorReadings(){return m_vecdSensors;}

  bool              Collided()const{return m_bCollided;}

  void              PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}

  int               GetNumberOfWeights(){return m_ItsBrain.GetNumberOfWeights();}

  vector<int>       CalculateSplitPoints(){return m_ItsBrain.CalculateSplitPoints();}

  
};


#endif

	
	