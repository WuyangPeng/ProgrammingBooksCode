#ifndef GATSP_H
#define GATSP_H

#include <vector>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include <iostream>

#include "defines.h"
#include "CmapTSP.h"
#include "utils.h"

using namespace std;



//---------------------------------------------------------
// define the genome type for the travelling salesman
// problem.
//---------------------------------------------------------
struct SGenome
{
	//the city tour
	vector<int>		vecCities;
	
	//its fitness
  double			  dFitness;


	//ctor
	SGenome():dFitness(0){}
	
	SGenome(int nc): dFitness(0)
	{
		vecCities = GrabPermutation(nc);
	}

	//creates a random tour of the cities
	vector<int>	GrabPermutation(int &limit);

	//used in GrabPermutation
	bool		TestNumber(const vector<int> &vec, const int &number);

};


//------------------------------------------------------------------------
//	The permutation GA class definition
//------------------------------------------------------------------------
class CgaTSP
{
private:

	vector<SGenome>		m_vecPopulation;

	//instance of the map class
	CmapTSP*			m_pMap;

	double				m_dMutationRate;

	double				m_dCrossoverRate;

	//total fitness of the entire population
	double				m_dTotalFitness;
	
	//the shortest tour found so far
	double				m_dShortestRoute;

	//the worst tour found so far
	double				m_dLongestRoute;

	//number of genomes in the population
	int					  m_iPopSize;

	//length of chromosome
	int					  m_iChromoLength;

	//the fittest member of the most recent generation
	int					  m_iFittestGenome;

	//keeps track of which generation we are in
	int					  m_iGeneration;
	
	//lets us know if the current run is in progress
	//used in the rendering function
	bool				  m_bStarted;


	//Exchange Mutation
	void			  MutateEM(vector<int> &chromo);


	//Partially Matched Crossover
	void			  CrossoverPMX(const vector<int> &mum, 
				                   const vector<int> &dad, 
								           vector<int>	     &baby1, 
			 		 	 		           vector<int>	     &baby2);
	 
	SGenome&		RouletteWheelSelection();


	//methods used in the fitness functions

	void			 CalculatePopulationsFitness();

	void			 CalculateBestWorstAvTot();
	
	void			 Reset();

	void			 CreateStartingPopulation();

public:

	
	CgaTSP(double	  mut_rat,
		     double	  cross_rat,
		     int		  pop_size,
		     int		  NumCities,
		     int		  map_width,
		     int		  map_height):m_dMutationRate(mut_rat),
							                m_dCrossoverRate(cross_rat),
							                m_iPopSize(pop_size),
							                m_iFittestGenome(0),
							                m_iGeneration(0),
							                m_dShortestRoute(999999999),
							                m_dLongestRoute(0),
							                m_iChromoLength(NumCities),
							                m_bStarted(false)


	{
		//set up the map
		m_pMap = new CmapTSP(map_width,
							           map_height,
							           NumCities);
		
		CreateStartingPopulation();
	}


	~CgaTSP()
	{
		delete m_pMap;
	}


  void			Epoch();

	void			Run(HWND hwnd);

  void      Render(HDC surface, int cx, int cy);

  //called if user resizes the client area
  void      Resize(int cxClient, int cyClient)
  {
    m_pMap->Resize(cxClient, cyClient);
  }

	//accessor methods
	void			Stop(){m_bStarted = false;}
  bool      Started(){return m_bStarted;}

};




#endif
