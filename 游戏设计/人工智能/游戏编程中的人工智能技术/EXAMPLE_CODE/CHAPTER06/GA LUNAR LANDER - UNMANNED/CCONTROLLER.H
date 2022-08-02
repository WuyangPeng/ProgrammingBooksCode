#ifndef CCONTROLLER_H
#define CCONTROLLER_H

//-----------------------------------------------------------------------
//  
//  Name: CController.h
//  
//  Author: Mat Buckland 2002
//
//  Desc: controller class for the Lunar Lander example project
//
//------------------------------------------------------------------------

#include <windows.h>
#include <vector>
#include <mmsystem.h>

#include "utils.h"
#include "CLander.h"
#include "CGALander.h"

using namespace std;


class CController 
{
private:

  //pointer to the genetic algorithm
  CgaLander*      m_pGA;

  vector<CLander> m_vecLanders;

  //stores all out genomes
  vector<SGenome> m_vecPop;

  //toggles the speed at which the simulation runs
	bool				    m_bFastRender;

  //if switched on shows best attempt each generation
  bool            m_bShowFittest;

  //true if we have successfully landed
  bool            m_bSuccess;

  //buffer for the stars
  vector<SPoint>  m_vecStarVB;

  //buffer to store the landing pads vertices
  vector<SPoint>  m_vecPadVB;

  //position of the landing pad
  SVector2D        m_vPadPos;

  //generation counter
  int             m_iGeneration;

  //keeps a track of the fittest lander each generation
  int             m_iFittest;

  //keeps track of the window size
  int             m_cxClient, m_cyClient;
 

  void WorldTransform(vector<SPoint> &pad);

  void RenderLandingPad(HDC &surface);

  void Success();

public:
  
  CController(int cxClient, int cyClient);
  ~CController()
  {
    if (m_pGA) delete m_pGA;;
  }

  //this is where most of our calculations are performed
  bool  Update();

  //initialize a new run
  void  NewRun();

  void  Render(HDC &surface);

  void  ToggleFastRender(){m_bFastRender = !m_bFastRender;}  

  void  ToggleShowFittest();  

  //accessor methods
  bool  FastRender()const{return m_bFastRender;}
  bool  ShowFittest()const{return m_bShowFittest;}
  
};





#endif