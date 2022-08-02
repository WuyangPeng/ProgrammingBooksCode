#ifndef CCONTROLLER_H
#define CCONTROLLER_H

//------------------------------------------------------------------------
//
//	Name: CController.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Controller class for 'Smart Sweeper' example from the book 
//        Game AI Programming with Neural Nets and Genetic Algorithms. 
//
//------------------------------------------------------------------------
#include <vector>
#include <sstream>
#include <string>
#include <windows.h>

#include "CMinesweeper.h"
#include "CGenAlg.h"
#include "utils.h"
#include "C2DMatrix.h"
#include "SVector2D.h"
#include "CParams.h"


using namespace std;



class CController
{

private:

	vector<SGenome>	     m_vecThePopulation;

	vector<CMinesweeper> m_vecSweepers;

	//vector of mines
	vector<SVector2D>	   m_vecMines;

	//pointer to the GA
	CGenAlg*		         m_pGA;

	int					         m_NumSweepers;

	int					         m_NumMines;

	//number of weights required for the neural net
  int					         m_NumWeightsInNN;

	//vertex buffer for the sweeper shape's vertices
	vector<SPoint>		   m_SweeperVB;

	//vertex buffer for the mine shape's vertices
	vector<SPoint>		   m_MineVB;

	//stores the average fitness per generation for use 
	//in graphing.
	vector<double>		   m_vecAvFitness;

	//stores the best fitness per generation
	vector<double>		   m_vecBestFitness;

	//pens we use for the stats
	HPEN				m_RedPen;
	HPEN				m_BluePen;
	HPEN				m_GreenPen;
	HPEN				m_OldPen;
	
	//handle to the application window
	HWND				m_hwndMain;

	//toggles the speed at which the simulation runs
	bool				m_bFastRender;
	
	//cycles per generation
	int					m_iTicks;

	//generation counter
	int					m_iGenerations;

  //window dimensions
  int         cxClient, cyClient;

  void   PlotStats(HDC surface);


public:

	CController(HWND hwndMain);

	~CController();


	void		Render(HDC surface);

	void		WorldTransform(vector<SPoint> &VBuffer,
                         SVector2D      vPos);
	
	bool		Update();


	//accessor methods
	bool		FastRender()			  {return m_bFastRender;}
	void		FastRender(bool arg){m_bFastRender = arg;}
	void		FastRenderToggle()  {m_bFastRender = !m_bFastRender;}

};


#endif
	
