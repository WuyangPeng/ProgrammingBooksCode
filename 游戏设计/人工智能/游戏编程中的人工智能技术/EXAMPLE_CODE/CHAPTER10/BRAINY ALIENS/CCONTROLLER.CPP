#include "CController.h"

                                      

//-----------------------------ctor---------------------------------------
//
//------------------------------------------------------------------------
CController::CController(int cxClient,
                         int cyClient):m_iNumSpawnedFromTheMultiset(0),
                                       m_cxClient(cxClient),
                                       m_cyClient(cyClient),
                                       m_iAliensCreatedSoFar(0),
                                       m_bFastRender(true)
                                     
                                       
{
  //create a gun
  m_pGunTurret = new CGun();

  //create the first few aliens
  for (int a=0; a<CParams::iNumOnScreen; ++a)
  {
    m_vecActiveAliens.push_back(CAlien());

    ++m_iAliensCreatedSoFar;
  }

  //setup the stars
  for (int star=0; star<NUM_STARS; ++star)
  {
    m_vecStarVB.push_back(SPoint(RandInt(0, cxClient), RandInt(0, cyClient)));
  }

  //create the custom pens 
  m_GreenPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
  m_RedPen   = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
  m_GunPen   = CreatePen(PS_SOLID, 1, RGB(200, 200, 100));
  m_BarPen   = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));
}

//----------------------------------- dtor -------------------------------
//
//------------------------------------------------------------------------
CController::~CController()
{
  //clean up the pens
  DeleteObject(m_GreenPen);
  DeleteObject(m_RedPen);
  DeleteObject(m_GunPen);
  DeleteObject(m_BarPen);


  //delete the gun turret
  delete m_pGunTurret;
}

//---------------------------- Reset -------------------------------------
//
//  Resets ready for another go
//------------------------------------------------------------------------
void CController::Reset()
{
  //clear all current aliens
  m_vecActiveAliens.clear();
  m_setAliens.clear();

  //reset all variables
  m_iAliensCreatedSoFar        = 0;
  m_iNumSpawnedFromTheMultiset = 0;
  m_bFastRender                = true;
  
  m_pGunTurret->AutoGunOn();

  //create the first few aliens
  for (int a=0; a<CParams::iNumOnScreen; ++a)
  {
    m_vecActiveAliens.push_back(CAlien());

    ++m_iAliensCreatedSoFar;
  }
}


//-----------------------Render--------------------------------------
//
//-------------------------------------------------------------------
void CController::Render(HDC &surface)
{
  if (!m_bFastRender)
  {
    //change the mapping mode so that the origin is at the bottom left
    //of our window and so that the y axis increases as it goes from
    //bottom to top     
    SetMapMode( surface, MM_ANISOTROPIC );
    SetViewportExtEx( surface, 1, -1, NULL );
    SetWindowExtEx( surface, 1, 1, NULL );
    SetViewportOrgEx( surface, 0, m_cyClient, NULL );


    //-------------------first render the stars

    for (int i=0; i<m_vecStarVB.size(); ++i)
    {
      //make them twinkle
      if (RandFloat() > 0.1)
      {
        SetPixel(surface, m_vecStarVB[i].x, m_vecStarVB[i].y, RGB(255, 255, 255));
      }
    }


    //-------------------render the aliens

    for (i=0; i<m_vecActiveAliens.size(); ++i)
    {
      m_vecActiveAliens[i].Render(surface, m_GreenPen, m_RedPen);
    }

    //-------------------render the gun and any bullets

    m_pGunTurret->Render(surface, m_GunPen);


    //-------------------render additional information

    SetBkMode(surface, TRANSPARENT);
    SetTextColor(surface, RGB(0,0,255));
  
    string s = "Num Spawned " + itos(m_iNumSpawnedFromTheMultiset);
	  TextOut(surface, 5, m_cyClient-5, s.c_str(), s.size());
    
 
    //return the mapping mode to its default state so text is rendered
    //correctly
    SetMapMode( surface, MM_ANISOTROPIC );
    SetViewportExtEx( surface, 1, 1, NULL );
    SetWindowExtEx( surface, 1, 1, NULL );
    SetViewportOrgEx( surface, 0, 0, NULL );
    
  }

  else
  {
    SetBkMode(surface, TRANSPARENT);
    SetTextColor(surface, RGB(0,0,255));
  
	  string s = "PreSpawning";
	  TextOut(surface, 10, m_cyClient-45, s.c_str(), s.size());

    HPEN OldPen = (HPEN)SelectObject(surface, m_BarPen);

    MoveToEx(surface, 10, m_cyClient -20, NULL);
    LineTo(surface, (m_cxClient/(double)CParams::iPreSpawns)*m_iNumSpawnedFromTheMultiset-10, m_cyClient -20);

    SelectObject(surface, OldPen);

  }
}


//------------------------------- Update ---------------------------------
//
//  The workhorse of the program. Updates all the game objects and
//  spawns new aliens into the population.
//------------------------------------------------------------------------
bool CController::Update()
{
  
  //switch the autogun off if enough offspring have been
  //spawned
  if (m_iNumSpawnedFromTheMultiset > CParams::iPreSpawns)
  {
    m_pGunTurret->AutoGunOff();

    m_bFastRender = false;
  }
  
  //get update from player for the turret movement
  //and update any bullets that may have been fired
  m_pGunTurret->Update();
    
  //move the stars
  for (int str=0; str<m_vecStarVB.size(); ++str)
  {
    m_vecStarVB[str].y -= 0.2f;

    if (m_vecStarVB[str].y < 0)
    {
      //create a new star
      m_vecStarVB[str].x = RandInt(0, CParams::WindowWidth);
      m_vecStarVB[str].y = CParams::WindowHeight;
    }
  }


  //update the aliens
  for (int i=0; i<m_vecActiveAliens.size(); ++i)
  {

    //if alien has 'died' replace with a new one
    if (!m_vecActiveAliens[i].Update(m_pGunTurret->m_vecBullets,
                               m_pGunTurret->m_vPos))
    { 

      //first we need to re-insert into the breeding population so
      //that its fitness score and genes are recorded.
      m_setAliens.insert(m_vecActiveAliens[i]);

      //if the required population size has been reached, delete the 
      //worst performer from the multiset
      if (m_setAliens.size() >= CParams::iPopSize)
      {      
        m_setAliens.erase(--m_setAliens.end());        
      }

      ++m_iNumSpawnedFromTheMultiset;
                  
      //if early in the run then we are still trying out new aliens
      if (m_iAliensCreatedSoFar <= CParams::iPopSize)
      {
        m_vecActiveAliens[i] = CAlien();

        ++m_iAliensCreatedSoFar;          
      }

      //otherwise select from the multiset and apply mutation
      else
      {         
        m_vecActiveAliens[i] = TournamentSelection();

        m_vecActiveAliens[i].Reset();

        if (RandFloat() < 0.8)
        {
          m_vecActiveAliens[i].Mutate();
        }
      }
    }
  }//next alien

  return true;
}


//---------------------------- TournamentSelection -----------------------
//
//  performs standard tournament selection given a number of genomes to
//  sample from each try.
//------------------------------------------------------------------------
CAlien CController::TournamentSelection()
{
  double BestFitnessSoFar = 0;

  //this will hold the winner of the tournament
  AlienIterator ChosenAlien = NULL;  

  //Select N members from the population at random testing against 
  //the best found so far
  for (int i=0; i<CParams::iNumTourneyCompetitors; ++i)
  {
    //select an alien from the population at random
    AlienIterator curAlien = m_setAliens.begin();

    advance(curAlien, RandInt(0, (int)(m_setAliens.size()-1) * CParams::dPercentageBestToSelectFrom));

    //test it to see if it's fitter than any selected so far and that its not already active
    if ( curAlien->Fitness() > BestFitnessSoFar)
    {
      ChosenAlien = curAlien;

      BestFitnessSoFar = curAlien->Fitness();
    }
  }

  //return our champion
  return *ChosenAlien;
}
	


