#include "CgaLander.h"

//----------------------CreateStartPopulation---------------------------
//
//-----------------------------------------------------------------------
void CgaLander::CreateStartPopulation()
{
	//clear existing population
	m_vecPop.clear();
	
	for (int i=0; i<m_iPopSize; i++)
	{
		m_vecPop.push_back(SGenome(CHROMO_LENGTH));
	}

	//reset all variables
	m_iGeneration		 = 0;
	m_iFittestGenome	 = 0;
	m_dBestFitness  = 0;
	m_dTotalFitness = 0;
}

//-------------------------GrabNBest----------------------------------
//
//	This works like an advanced form of elitism by inserting NumCopies
//  copies of the NBest most fittest genomes into a population vector
//--------------------------------------------------------------------
void CgaLander::GrabNBest(int	            NBest,
					                const int	      NumCopies,
					                vector<SGenome>	&vecPop)
{
	//add the required amount of copies of the n most fittest 
	//to the supplied vector
	while(NBest--)
	{
		for (int i=0; i<NumCopies; ++i)
		{
			vecPop.push_back(m_vecPop[(m_iPopSize - 1) - NBest]);
		}
	}
}

//--------------------------RouletteWheelSelection-----------------
//
//	selects a member of the population by using roulette wheel 
//	selection as described in the text.
//------------------------------------------------------------------
SGenome& CgaLander::RouletteWheelSelection()
{
	double fSlice	= RandFloat() * m_dTotalFitness;
	
	double cfTotal	= 0.0;
	
	int	SelectedGenome = 0;
	
	for (int i=0; i<m_iPopSize; ++i)
	{
		
		cfTotal += m_vecPop[i].dFitness;
		
		if (cfTotal > fSlice) 
		{
			SelectedGenome = i;

			break;
		}
	}
	
	return m_vecPop[SelectedGenome];
}


//----------------------------Mutate---------------------------------
//
//--------------------------------------------------------------------
void CgaLander::Mutate(vector<SGene> &vecActions)
{

	for (int gene=0; gene<vecActions.size(); ++gene)
  {
    //do we mutate the action?
	  if (RandFloat() < m_dMutationRate)
	  {
      vecActions[gene].action = (action_type)RandInt(0,3);

	  }

	  //do we mutate the duration?
	  if (RandFloat() < m_dMutationRate/2)
	  {
      vecActions[gene].duration += RandomClamped()*MAX_MUTATION_DURATION;

      //clamp the duration
      Clamp(vecActions[gene].duration, 0, MAX_ACTION_DURATION);
	  }

  }//next gene
}


//--------------------------- CrossoverMulti -----------------------------
//
//  This function performs multipoint crossover on the genes. That is to
//  say for each chromosome where crossover is to be performed we determine
//  a swap rate and iterate through each chromosome swap over individual
//  genes where appropriate. 
//-------------------------------------------------------------------------
void CgaLander::CrossoverMulti( const vector<SGene> &mum,
						                    const vector<SGene> &dad,
						                    vector<SGene>       &baby1,
						                    vector<SGene>	     &baby2)
{
  //just return parents as offspring dependent on the rate
	//or if parents are the same
	if ( (RandFloat() > m_dCrossoverRate) || (mum == dad)) 
	{
		baby1 = mum;
		baby2 = dad;

		return;
	}
    
  //first determine a swapping rate for this chromosome
  float SwapRate = RandFloat()*CHROMO_LENGTH;

  for (int gene=0; gene<mum.size(); ++gene)
  {
    if (RandFloat() < SwapRate)
    {
      //switch the genes at this point
      baby1.push_back(dad[gene]);
      baby2.push_back(mum[gene]);
    
    }

    else
    {
      //just copy into offspring 
      baby1.push_back(mum[gene]);
      baby2.push_back(dad[gene]);
    }
  }//next gene
}

//------------------------------ UpdatePop -----------------------------
//
//----------------------------------------------------------------------
void CgaLander::UpdatePop(vector<SGenome> &vOldPop)
{
  m_vecPop = vOldPop;

  vOldPop = Epoch();

}

//--------------------------------Epoch---------------------------------
//
//	This is the workhorse of the GA. It first updates the fitness
//	scores of the population then creates a new population of
//	genomes using the Selection, Crossover and Mutation operators
//	we have discussed
//----------------------------------------------------------------------
vector<SGenome> CgaLander::Epoch()
{
	
	//create some storage for the baby genomes 
	vector<SGenome> vecBabyGenomes;

  //sort the population (for scaling and elitism)
  sort(m_vecPop.begin(), m_vecPop.end());

  CalculateBestWorstAvTot();

	//Now to add a little elitism we shall add in some copies of the
	//fittest genomes. Make sure we add an EVEN number or the roulette wheel
	//sampling will crash
	if (!(NUM_COPIES_ELITE * NUM_ELITE % 2))
	{
		GrabNBest(NUM_ELITE, NUM_COPIES_ELITE, vecBabyGenomes);
	}


	while (vecBabyGenomes.size() < m_iPopSize)
	{
		//select 2 parents
	  SGenome mum = RouletteWheelSelection();
		SGenome dad = RouletteWheelSelection();
   
		//operator - crossover
		SGenome baby1, baby2;
    
		CrossoverMulti(mum.vecActions,
                   dad.vecActions,
                   baby1.vecActions,
                   baby2.vecActions);

		//operator - mutate
		Mutate(baby1.vecActions);
		Mutate(baby2.vecActions);

		//add to new population
		vecBabyGenomes.push_back(baby1);
		vecBabyGenomes.push_back(baby2);
	}

	//copy babies back into starter population
	m_vecPop = vecBabyGenomes;

	//increment the generation counter
	++m_iGeneration;

  return m_vecPop;
}

//-----------------------CalculateBestWorstAvTot-----------------------	
//
//	calculates the fittest and weakest genome and the average/total 
//	fitness scores. Assumes the genomes have been sorted
//---------------------------------------------------------------------
void CgaLander::CalculateBestWorstAvTot()
{
	m_dTotalFitness = 0;
		
	for (int i=0; i<m_iPopSize; ++i)
	{
		m_dTotalFitness	+= m_vecPop[i].dFitness;		
	}//next chromo
	
	m_dAverageFitness = m_dTotalFitness / m_iPopSize;

  m_iFittestGenome = 0;
  m_dBestFitness   = m_vecPop[m_iPopSize - 1].dFitness;
  m_dWorstFitness  = m_vecPop[0].dFitness;

}

