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
#include "CMapper.h"



using namespace std;


class CMinesweeper
{

private:

    
  CNeuralNet  m_ItsBrain;

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

  void              PutWeights(vector<double> &w){m_ItsBrain.PutWeights(w);}

  int               GetNumberOfWeights()const{return m_ItsBrain.GetNumberOfWeights();}

  vector<int>       CalculateSplitPoints()const{return m_ItsBrain.CalculateSplitPoints();}
 
};


#endif

	
	