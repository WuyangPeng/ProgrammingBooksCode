#ifndef CCONTROLLER_H
#define CCONTROLLER_H

//-----------------------------------------------------------------------
//  
//  Name: CController.h
//  
//  Author: Mat Buckland 2002
//
//  Desc: controller class for the Brainy Aliens example project
//
//------------------------------------------------------------------------
#pragma warning (disable:4786) //turn off warnings for std::multiset

#include <windows.h>
#include <vector>
#include <set>

#include "utils.h"
#include "CGun.h"
#include "CNeuralNet.h"
#include "CParams.h"
#include "CAlien.h"

using namespace std;


//helps legibility
typedef multiset<CAlien>::iterator AlienIterator;

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class CController 
{
private:

  //the player's gun
  CGun*            m_pGunTurret;

  //the pool of aliens
  multiset<CAlien> m_setAliens;

  //the currently active aliens
  vector<CAlien>   m_vecActiveAliens;

  int              m_iAliensCreatedSoFar;
 
  int              m_iNumSpawnedFromTheMultiset;

  //vertex buffer for the stars
  vector<SPoint>   m_vecStarVB;

  //keeps track of the window size
  int              m_cxClient,
                   m_cyClient;

  //lets the program run as fast as possible
  bool             m_bFastRender;
 
  //custom pens used for drawing the game objects
  HPEN             m_GreenPen;
  HPEN             m_RedPen;
  HPEN             m_GunPen;
  HPEN             m_BarPen;


  void    WorldTransform(vector<SPoint> &pad);
    
  CAlien  TournamentSelection();


public:
  
  CController(int cxClient, int cyClient);

  ~CController();

  //The workhorse of the program. Updates all the game objects and
  //spawns new aliens into the population.
  bool  Update();

  void  Render(HDC &surface);

  //resets all the controller variables and creates a new starting
  //population of aliens, ready for another run
  void  Reset();

  //-----------------------------accessor functions
  bool FastRender(){return m_bFastRender;} 
};





#endif