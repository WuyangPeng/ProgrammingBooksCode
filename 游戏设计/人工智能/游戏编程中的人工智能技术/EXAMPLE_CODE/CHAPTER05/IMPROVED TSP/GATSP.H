#ifndef GATSP_H
#define GATSP_H

/////////////////////////////////////////////////////////////////////////
//
//		File: gaTSP.h
//
//		Author: Mat Buckland
//
//		Desc: The genetic algorithm class definition to solve the traveling
//          salesman problem.
//
/////////////////////////////////////////////////////////////////////////

#include <vector>
#include <windows.h>
#include <algorithm>

#include "defines.h"
#include "CmapTSP.h"
#include "utils.h"

using namespace std;

//used in GrabPermutation and in PBX crossover. Tests if an 
//integer is already contained in a vector of integers
bool TestNumber(const vector<int> &vec, const int &number);

//---------------------------------------------------------
// define a genome type for the travelling salesman
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
	vector<int>	GrabPermutation( int &limit);

	//overload '<' used for sorting
	friend bool operator<(const SGenome& lhs, const SGenome& rhs)
	{
		return (lhs.dFitness < rhs.dFitness);
	}	
};


//-----------------------------------------------------------------------
// enumerations for the operator, scaling and selection types 
//-----------------------------------------------------------------------

enum			MutationType{EM, DM, SM, IM};

enum			CrossoverType{PMX, OBX, PBX};

enum      ScaleType{NONE, RANK, SIGMA, BOLTZMANN};

enum      SelectionType{ROULETTE, TOURNAMENT, ALT_TOURNAMENT, SUS};

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

	//The best fitness score of the most recent generation
	double				m_dBestFitness;

	//The worst fitness score of the most recent generation
	double				m_dWorstFitness;

	//The average fitness of the most recent generation
	double				m_dAverageFitness;

	//number of genomes in the population
	int					  m_iPopSize;

	//length of chromosome
	int					  m_iChromoLength;

	//the fittest member of the most recent generation
	int					  m_iFittestGenome;

	//keeps track of which generation we are in
	int					  m_iGeneration;
	
	//lets us know if the current run is in progress
	//used in our rendering function
	bool				  m_bStarted;

	//lets us know if the genomes have been sorted
	//in order of fitness (just a time saver really
	//to prevent unnecessary sorting)
	bool			  	m_bSorted;

  //toggles elitism on/off
  bool          m_bElitism;

  //current boltzmann temperature
  double        m_dBoltzmannTemp;

  //if we are using sigma scaling this holds the current
  //value of sigma. If sigma reaches 0 then all the
  //population are identical so the run is halted
  double        m_dSigma;

  //local copy of the application handle
  HWND        m_hWnd;


	//Mutation Operators

					//Exchange Mutation
	void			MutateEM(vector<int> &chromo);
					//Dispacement Mutation
	void			MutateDM(vector<int> &chromo);
					//Scramble Mutation
	void			MutateSM(vector<int> &chromo);
					//Insertion Mutation
	void			MutateIM(vector<int> &chromo);


	//mutate function controller
	void			Mutate(vector<int> &chromo, MutationType &type);

	MutationType			m_MutationType;

	//Crossover Operators

					//Partially Matched Crossover
	void			CrossoverPMX(const vector<int> &mum, 
								         const vector<int> &dad, 
								         vector<int>	     &baby1, 
			 		 	 		         vector<int>	     &baby2);
						
					//Order Based Crossover
	void			CrossoverOBX(const vector<int> &mum, 
								         const vector<int> &dad, 
								         vector<int>	     &baby1, 
								         vector<int>	     &baby2);

					//Position Based Crossover
	void			CrossoverPBX(const vector<int> &mum, 
								         const vector<int> &dad, 
								         vector<int>	     &baby1, 
								         vector<int>	     &baby2);

  //this calls one of the above based on the CrossoverType 
  void CgaTSP::Crossover(const vector<int>	&mum, 
							           const vector<int>	&dad, 
							           vector<int>        &baby1, 
							           vector<int>        &baby2,
                         CrossoverType      type);

	CrossoverType			m_CrossoverType;


	//Selection and scaling Operators
	 
	SGenome&		RouletteWheelSelection();
  void        SUSSelection(vector<SGenome> &NewPop); //**CHECK
  SGenome&    TournamentSelection(int NumToTry);
  SGenome&    AlternativeTournamentSelection();

  SelectionType m_SelectionType;

	void			  GrabNBest(const int				 NBest,
							          const int		     NumCopies,
							          vector<SGenome>  &vecNewPop);

	void			  FitnessScaleRank(vector<SGenome> &pop);
  void        FitnessScaleSigma(vector<SGenome> &pop);
  void        FitnessScaleBoltzmann(vector<SGenome> &pop);
  void        FitnessScaleSwitch();

  ScaleType     m_ScaleType;


	//methods used in the fitness functions

	void			CalculatePopulationsFitness();

	void			CalculateBestWorstAvTot();
	

  //other methods
	void			Reset();

	void			CreateStartingPopulation();



public:

	CgaTSP(double	       mut_rat,
		     double	       cross_rat,
		     int		       pop_size,
		     int		       NumCities,
		     MutationType	 mo,
		     CrossoverType co,
         ScaleType     st,
         SelectionType select,
		     int		       map_width,
		     int		       map_height,
         HWND          hwnd): m_dMutationRate(mut_rat),
							                m_dCrossoverRate(cross_rat),
							                m_iPopSize(pop_size),
							                m_iFittestGenome(0),
							                m_dBestFitness(-999999),
							                m_dWorstFitness(99999999),
							                m_dAverageFitness(0),
							                m_iGeneration(0),
							                m_dShortestRoute(999999999),
							                m_dLongestRoute(0),
							                m_iChromoLength(NumCities),
							                m_bStarted(false),
							                m_bSorted(false),
							                m_MutationType(mo),
							                m_CrossoverType(co),
                              m_ScaleType(st),
                              m_SelectionType(select),
                              m_bElitism(true),
                              m_dBoltzmannTemp(NUM_CITIES * 2),
                              m_dSigma(1),
                              m_hWnd(hwnd)
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

  void      Render(HDC surface, int cx, int cy)const;

  //called if user resizes the client area
  void      Resize(int cxClient, int cyClient)
  {
    m_pMap->Resize(cxClient, cyClient);
  }

	//accessor methods
	void			Stop(){m_bStarted = false;}
  bool      Started()const{return m_bStarted;}
  void      SetSelectionMethod(SelectionType s){m_SelectionType = s;}
  void      SetScalingMethod(ScaleType s){m_ScaleType = s;}
  void      SetMutation(MutationType m){m_MutationType = m;}
  void      SetCrossover(CrossoverType c){m_CrossoverType = c;}
  void      SetElitism(bool arg){m_bElitism = arg;}

};


#endif
