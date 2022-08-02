#ifndef CCONTROLLER_H
#define CCONTROLLER_H
//-----------------------------------------------------------------------
//
//  Name: CLander.h
//
//  Author: Mat Buckland 2002
//
//	Desc: Controller class for the lunar lander project.
//
//-----------------------------------------------------------------------

#include <windows.h>
#include <vector>
#include <mmsystem.h>

#include "utils.h"
#include "CLander.h"


using namespace std;


class CController 
{
private:

  //this is the lander the user can control
  CLander*        m_pUserLander;

  //true if we have successfully landed
  bool            m_bSuccess;

  //vertex buffer for the stars
  vector<SPoint>  m_vecStarVB;

  //vertex buffer to store the landing pads vertices
  vector<SPoint>  m_vecPadVB;

  //position of the landing pad
  SVector2D       m_vPadPos;

  //keeps a record of the window size
  int             m_cxClient,
                  m_cyClient;

  void WorldTransform(vector<SPoint> &pad);

  void RenderLandingPad(HDC &surface);


public:
  
  CController(int cxClient, int cyClient);

  ~CController();

  //this is called from the windows message loop and calls
  //CLander::CheckForKeyPress() which tests for user input 
  //and updates the lander's position accordingly
  bool  Update(double TimeElapsed);

  //initialize a new run
  void  NewRun();

  //this is called from WM_PAINT to render all the objects
  //in our scene
  void  Render(HDC &surface);
  
};


#endif