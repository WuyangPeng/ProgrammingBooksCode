#ifndef CCONTROLLER_H
#define CCONTROLLER_H

//------------------------------------------------------------------------
//
//	Name: CController.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Controller class for NEAT Sweepers  
//
//------------------------------------------------------------------------
#include <vector>
#include <sstream>
#include <string>
#include <windows.h>

#include "CMinesweeper.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"
#include "Cga.h"

using namespace std;



class CController
{

private:

	//storage for the entire population of chromosomes
	Cga*                 m_pPop;

	//array of sweepers
	vector<CMinesweeper> m_vecSweepers;

  //array of best sweepers from last generation (used for
  //display purposes when 'B' is pressed by the user)
  vector<CMinesweeper> m_vecBestSweepers;

	int					         m_NumSweepers;

	//vertex buffer for the sweeper shapes vertices
	vector<SPoint>		   m_SweeperVB;

  //vertex buffer for objects
  vector<SPoint>       m_ObjectsVB;

	//stores the average fitness per generation 
	vector<double>		   m_vecAvFitness;

	//stores the best fitness per generation
	vector<double>		   m_vecBestFitness;

  //best fitness ever
  double               m_dBestFitness;

	//pens we use for the stats
	HPEN				m_RedPen;
	HPEN				m_BluePen;
	HPEN				m_GreenPen;
  HPEN        m_GreyPenDotted;
  HPEN        m_RedPenDotted;
	HPEN				m_OldPen;

  HBRUSH      m_RedBrush;
  HBRUSH      m_BlueBrush;
	
	//local copy of the handle to the application window
	HWND				m_hwndMain;

  //local copy of the  handle to the info window
  HWND        m_hwndInfo;

	//toggles the speed at which the simulation runs
	bool				m_bFastRender;

  //when set, renders the best performers from the 
  //previous generaion.
  bool        m_bRenderBest;
	
	//cycles per generation
	int					m_iTicks;

	//generation counter
	int					m_iGenerations;

  //local copy of the client window dimensions
  int         m_cxClient, m_cyClient;

  //this is the sweeper who's memory cells are displayed
  int         m_iViewThisSweeper;

  void   PlotStats(HDC surface)const;
  
  void   RenderSweepers(HDC &surface, vector<CMinesweeper> &sweepers);
  
  void   RenderSensors (HDC &surface, vector<CMinesweeper> &sweepers);

public:

	CController(HWND hwndMain, int cxClient, int cyClient);

	~CController();

	void		Render(HDC &surface);

  //renders the phenotypes of the four best performers from
  //the previous generation
  void    RenderNetworks(HDC &surface);
	
	bool		Update();


	//-------------------------------------accessor methods
	bool		        FastRender()const{return m_bFastRender;}
	void		        FastRender(bool arg){m_bFastRender = arg;}
	void		        FastRenderToggle(){m_bFastRender = !m_bFastRender;}

  bool            RenderBest()const{return m_bRenderBest;}
  void            RenderBestToggle(){m_bRenderBest = !m_bRenderBest;}

  void            PassInfoHandle(HWND hnd){m_hwndInfo = hnd;}
  
  vector<double>  GetFitnessScores()const;

  void            ViewBest(int val)
  {
    if ( (val>4) || (val< 1) )
    {
      return;
    }

    m_iViewThisSweeper = val-1;
  }
};


#endif
	
