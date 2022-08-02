#ifndef CGENALG_H
#define CGENALG_H
//------------------------------------------------------------------------
//
//	Name: CGenAlg.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Genetic algorithm class.This is based on manipulating std::vectors 
//  of *real* numbers. Used to adjust the weights in a feedforward neural
//  network.
//
//------------------------------------------------------------------------

#include <vector>
#include <algorithm>
#include <iostream>

#include "utils.h"
#include "CParams.h"

using namespace std;

//-----------------------------------------------------------------------
//
//	create a structure to hold each genome
//-----------------------------------------------------------------------
struct SGenome
{
	vector <double>	vecWeights;

	double          dFitness;

	SGenome():dFitness(0){}

	SGenome( vector <double> w, double f): vecWeights(w), dFitness(f){}

	//overload '<' used for sorting
	friend bool operator<(const SGenome& lhs, const SGenome& rhs)
	{
		return (lhs.dFitness < rhs.dFitness);
	}
};

//-----------------------------------------------------------------------
//
//	the genetic algorithm class
//-----------------------------------------------------------------------
class CGenAlg
{
private:
	
	//this holds the entire population of chromosomes
	vector <SGenome>	 m_vecPop;

  //this holds the positions of the split points in the genome for use
  //in our modified crossover operator
  vector<int> m_vecSplitPoints;

	//size of population
	int         m_iPopSize;
	
	//amount of weights per chromo
	int         m_iChromoLength;

	//best, average, worst and total fitnesses this population
	double      m_dBestFitness,
              m_dAverageFitness,
              m_dWorstFitness,
              m_dTotalFitness;

	//keeps track of the best genome
	int		      m_iFittestGenome;

	//probability that a chromosones bits will mutate.
	//Try figures around 0.05 to 0.3 ish
	double      m_dMutationRate;

	//probability of chromosones crossing over bits
	//0.7 is pretty good
	double      m_dCrossoverRate;

	//generation counter
	int	        m_cGeneration;


  //this crossover operator only performs crossover at
  //the points which represent the start and end points 
  //of the weights of each neuron in the net.
  void     CrossoverAtSplits(const vector<double> &mum,
                             const vector<double> &dad,
                             vector<double>       &baby1,
                             vector<double>       &baby2);
	
	void    Mutate(vector<double> &chromo);

	void	  GrabNBest(int	            NBest,
	                  const int       NumCopies,
	                  vector<SGenome>	&vecPop);

  SGenome TournamentSelection(int N);

	void	  CalculateBestWorstAvTot();

	void	  Reset();



public:
		
	CGenAlg(int 		    popsize,
			    double	    MutRat,
			    double	    CrossRat,
			    int	  	    numweights,
          vector<int> splits);

	//this runs the GA for one generation.
	vector<SGenome>	  Epoch(vector<SGenome> &old_pop);


	//accessor methods
	vector<SGenome>&	GetChromos(){return m_vecPop;}
	double			      AverageRawFitness()const{return m_dAverageFitness;}
	double		    	  BestRawFitness()const{return m_dBestFitness;}
	
};



#endif

