#include "gaTSP.h"




//---------------------TestNumber-----------------------------
//
//	checks if a given integer is already contained in a vector
//	of integers.
//------------------------------------------------------------
bool TestNumber(const vector<int> &vec, const int &number)
{
	for (int i=0; i<vec.size(); ++i)
	{
		if (vec[i] == number)
		{
			return true;
		}
	}

	return false;
}




////////////////////////////////////////////////////////////////////////////////

//---------------------GrabPermutation----------------------
//
//	given an int, this function returns a vector containing
//	a random permutation of all the integers up to the supplied
//	parameter.
//------------------------------------------------------------
vector<int> SGenome::GrabPermutation(int &limit)
{
	vector<int> vecPerm;
	
	for (int i=0; i<limit; i++)
	{
		//we use limit-1 because we want ints numbered from zero
		int NextPossibleNumber = RandInt(0, limit-1);

		while(TestNumber(vecPerm, NextPossibleNumber))
		{
			NextPossibleNumber = RandInt(0, limit-1);
		}

		vecPerm.push_back(NextPossibleNumber);
	}

	return vecPerm;
}




/////////////////////////////////////////////////////////////////////////////


//-----------------------CalculatePopulationsFitness--------------------------
//
//	calculates the fitness of each member of the population, updates the
//	fittest, the worst, keeps a sum of the total fittness scores and the
//	average fitness score of the population (most of these stats are required
//	when we apply pre-selection fitness scaling.
//-----------------------------------------------------------------------------
void CgaTSP::CalculatePopulationsFitness()
{

	for (int i=0; i<m_iPopSize; ++i)
	{

		double TourLength = m_pMap->GetTourLength(m_vecPopulation[i].vecCities);

		m_vecPopulation[i].dFitness = TourLength;
		
		//keep a track of the shortest route found each generation
		if (TourLength < m_dShortestRoute)
		{
			m_dShortestRoute = TourLength;
		}
		
		//keep a track of the worst tour each generation
		if (TourLength > m_dLongestRoute)
		{
			m_dLongestRoute = TourLength;
		}

	}//next chromo

	//Now we have calculated all the tour lengths we can assign
	//the fitness scores
	for (i=0; i<m_iPopSize; ++i)
	{
		m_vecPopulation[i].dFitness = m_dLongestRoute - m_vecPopulation[i].dFitness;
	}

	//calculate values used in selection
	CalculateBestWorstAvTot();

}

//-----------------------CalculateBestWorstAvTot-----------------------	
//
//	calculates the fittest and weakest genome and the average/total 
//	fitness scores
//---------------------------------------------------------------------
void CgaTSP::CalculateBestWorstAvTot()
{
	m_dTotalFitness = 0;
	
	double HighestSoFar = -9999999;
	double LowestSoFar  = 9999999;
	
	for (int i=0; i<m_iPopSize; ++i)
	{
		//update fittest if necessary
		if (m_vecPopulation[i].dFitness > HighestSoFar)
		{
			HighestSoFar	 = m_vecPopulation[i].dFitness;
			
			m_iFittestGenome = i;

			m_dBestFitness	 = HighestSoFar;
		}
		
		//update worst if necessary
		if (m_vecPopulation[i].dFitness < LowestSoFar)
		{
			LowestSoFar = m_vecPopulation[i].dFitness;
			
			m_dWorstFitness = LowestSoFar;
		}
		
		m_dTotalFitness	+= m_vecPopulation[i].dFitness;
		
		
	}//next chromo
	
	m_dAverageFitness = m_dTotalFitness / m_iPopSize;

  //if all the fitnesses are zero the population has converged
  //to a grpoup of identical genomes so we should stop the run
  if (m_dAverageFitness == 0)
  {
    m_dSigma = 0;
  }

}

//-----------------------------FitnessScaleRank----------------------
//
//	This type of fitness scaling sorts the population into ascending
//	order of fitness and then simply assigns a fitness score based 
//	on its position in the ladder. (so if a genome ends up last it
//	gets score of zero, if best then it gets a score equal to the size
//	of the population. 
//---------------------------------------------------------------------
void CgaTSP::FitnessScaleRank(vector<SGenome> &pop)
{
	//sort population into ascending order
	if (!m_bSorted)
	{
		sort(pop.begin(), pop.end());

		m_bSorted = true;
	}

	//now assign fitness according to the genome's position on
	//this new fitness 'ladder'
	for (int i=0; i<pop.size(); i++)
	{
		pop[i].dFitness = i;
	}

	//recalculate values used in selection
	CalculateBestWorstAvTot();
}


//----------------------------- FitnessScaleSigma ------------------------
//
//  Scales the fitness using sigma scaling based on the equations given
//  in Chapter 5 of the book.
//------------------------------------------------------------------------
void CgaTSP::FitnessScaleSigma(vector<SGenome> &pop)
{
  double RunningTotal = 0;

  //first iterate through the population to calculate the standard
  //deviation
  for (int gen=0; gen<pop.size(); ++gen)
  {
    RunningTotal += (pop[gen].dFitness - m_dAverageFitness) *
                    (pop[gen].dFitness - m_dAverageFitness);
  }

  double variance = RunningTotal/(double)m_iPopSize;

  //standard deviation is the square root of the variance
  m_dSigma = sqrt(variance);

  //now iterate through the population to reassign the fitness scores
  for (gen=0; gen<pop.size(); ++gen)
  {
    double OldFitness = pop[gen].dFitness;

    pop[gen].dFitness = (OldFitness - m_dAverageFitness) /
                                    (2 * m_dSigma);
  }

  //recalculate values used in selection
	CalculateBestWorstAvTot();

}   

//------------------------- FitnessScaleBoltzmann ------------------------
//
//  This function applies Boltzmann scaling to a populations fitness
//  scores as described in Chapter 5.
//  The static value Temp is the boltzmann temperature which is reduced
//  each generation by a small amount. As Temp decreases the difference 
//  spread between the high and low fitnesses increases.
//------------------------------------------------------------------------
void CgaTSP::FitnessScaleBoltzmann(vector<SGenome> &pop)
{

  //reduce the temp a little each generation
  m_dBoltzmannTemp -= BOLTZMANN_DT;

  //make sure it doesn't fall below minimum value
  if (m_dBoltzmannTemp< BOLTZMANN_MIN_TEMP)
  {
    m_dBoltzmannTemp = BOLTZMANN_MIN_TEMP;
  }

  //first calculate the average fitness/Temp
  double divider = m_dAverageFitness/m_dBoltzmannTemp;

  //now iterate through the population and calculate the new expected
  //values
  for (int gen=0; gen<pop.size(); ++gen)
  {
    double OldFitness = pop[gen].dFitness;

    pop[gen].dFitness = (OldFitness/m_dBoltzmannTemp)/divider;
  }

  //recalculate values used in selection
	CalculateBestWorstAvTot();
}

//--------------------------FitnessScale----------------------------------
//
//  This is simply a switch statement to choose a selection method
//  based on the user preference
//------------------------------------------------------------------------
void CgaTSP::FitnessScaleSwitch()
{
  switch(m_ScaleType)
  {
  case NONE:

    break;

  case SIGMA:
    
    FitnessScaleSigma(m_vecPopulation);

    break;

  case BOLTZMANN:
    
    FitnessScaleBoltzmann(m_vecPopulation);

    break;

  case RANK:
    
    FitnessScaleRank(m_vecPopulation);

    break;
  }
}
//-------------------------GrabNBest----------------------------------
//
//	This works like an advanced form of elitism by inserting NumCopies
//  copies of the NBest most fittest genomes into a population vector
//--------------------------------------------------------------------
void CgaTSP::GrabNBest(int				      NBest,
					             const int        NumCopies,
					             vector<SGenome>	&vecNewPop)
{
	//first we need to sort our genomes
	if (!m_bSorted)
	{
		sort(m_vecPopulation.begin(), m_vecPopulation.end());

		m_bSorted = true;
	}

	//now add the required amount of copies of the n most fittest 
	//to the supplied vector
	while(NBest--)
	{
		for (int i=0; i<NumCopies; ++i)
		{
			vecNewPop.push_back(m_vecPopulation[(m_iPopSize - 1) - NBest]);
		}
	}
}

//--------------------------RouletteWheelSelection----------------------
//
//	selects a member of the population by using roulette wheel selection
//	as described in the text.
//-----------------------------------------------------------------------
SGenome& CgaTSP::RouletteWheelSelection()
{
	double fSlice	= RandFloat() * m_dTotalFitness;
	
	double cfTotal	= 0.0;
	
	int	SelectedGenome = 0;
	
	for (int i=0; i<m_iPopSize; ++i)
	{
		
		cfTotal += m_vecPopulation[i].dFitness;
		
		if (cfTotal > fSlice) 
		{
			SelectedGenome = i;
			
			break;
		}
	}
	
	return m_vecPopulation[SelectedGenome];
}

//----------------------- SUSSelection -----------------------------------
//
//  This function performs Stochasitic Universal Sampling.
//
//  SUS uses N evenly spaced hands which are spun once to choose the 
//  new population. As described in chapter 5.
//------------------------------------------------------------------------
void CgaTSP::SUSSelection(vector<SGenome> &NewPop)
{
  //this algorithm relies on all the fitnesses to be positive so
  //these few lines check and adjust accordingly (in this example
  //Sigma scaling can give negative fitnesses
  if (m_dWorstFitness < 0)
  {
    //recalculate
    for (int gen=0; gen<m_vecPopulation.size(); ++gen)
    {
      m_vecPopulation[gen].dFitness += fabs(m_dWorstFitness);
    }

    CalculateBestWorstAvTot();
  }

  int curGen = 0;
  double sum = 0;

  //NumToAdd is the amount of individuals we need to select using SUS.
  //Remember, some may have already been selected through elitism
  int NumToAdd = m_iPopSize - NewPop.size();

  //calculate the hand spacing
  double PointerGap = m_dTotalFitness/(double)NumToAdd;

  //choose a random start point for the wheel
  float ptr = RandFloat() * PointerGap;

	while (NewPop.size() < NumToAdd)
  {
	  for(sum+=m_vecPopulation[curGen].dFitness; sum > ptr; ptr+=PointerGap)
    {
	     NewPop.push_back(m_vecPopulation[curGen]);

       if( NewPop.size() == NumToAdd)
       {
         return;
       }
    }

    ++curGen;
  }
}


//---------------------------- TournamentSelection -----------------
//
//  performs standard tournament selection given a number of genomes to
//  sample from each try.
//------------------------------------------------------------------------
SGenome& CgaTSP::TournamentSelection(int N)
{
  double BestFitnessSoFar = 0;
  
  int ChosenOne = 0;

  //Select N members from the population at random testing against 
  //the best found so far
  for (int i=0; i<N; ++i)
  {
    int ThisTry = RandInt(0, m_iPopSize-1);

    if (m_vecPopulation[ThisTry].dFitness > BestFitnessSoFar)
    {
      ChosenOne = ThisTry;

      BestFitnessSoFar = m_vecPopulation[ThisTry].dFitness;
    }
  }

  //return the champion
  return m_vecPopulation[ChosenOne];
}

//-------------------------- AlternativeTournamentSelection---------------
//
//  variation of tournament selection described in chapter 5 of the book
//------------------------------------------------------------------------
SGenome& CgaTSP::AlternativeTournamentSelection()
{
  //allocate two indexes into the population
  int g1 = RandInt(0, m_vecPopulation.size()-1);
  int g2 = RandInt(0, m_vecPopulation.size()-1);

  //make sure they are different
  while(g1 == g2)
  {
    g2 = RandInt(0, m_vecPopulation.size()-1);
  }

  //grab a random number between 0 and 1
  float Rand = RandFloat();

  //now return the chosen individual based on CTOURNAMENT
  if(Rand < CTOURNAMENT)
  {
    //return the fitter of the two
    if (m_vecPopulation[g1].dFitness > m_vecPopulation[g2].dFitness)
    {
      return m_vecPopulation[g1];
    }
    else
    {
      return m_vecPopulation[g2];
    }
  }

  else
  {
    //return the weaker
    if (m_vecPopulation[g1].dFitness < m_vecPopulation[g2].dFitness)
    {
      return m_vecPopulation[g1];
    }
    else
    {
      return m_vecPopulation[g2];
    }
  }
}

//-----------------------------ChooseSection----------------------------
//
//	given a max span size and a min span size, this will calculate a 
//  random beginning and end point within the span. Used mainly in 
//  mutation and crossover operators
//----------------------------------------------------------------------
void ChooseSection(int       &beg,
                   int       &end,
                   const int max_span,
                   const int min_span)
{
	
	beg = RandInt(0, max_span-min_span);
	
	end = beg;
	
	//find an end
	while (end <= beg)
	{
		end = RandInt(0, max_span);
	}
}
//---------------------------MutateEM-----------------------------
//
//	Mutates the chromosome by choosing two random genes and swapping
//	their position.
//-----------------------------------------------------------------
void CgaTSP::MutateEM(vector<int> &chromo)
{
	//return dependent upon mutation rate
	if (RandFloat() > m_dMutationRate) return;

	//choose first gene
	int pos1 = RandInt(0, chromo.size()-1);

	//choose second
	int pos2 = pos1;

	while (pos1 == pos2)
	{
		pos2 = RandInt(0, chromo.size()-1);
	}

	//swap their positions
	swap(chromo[pos1], chromo[pos2]);
}

//--------------------------MutateIM------------------------------
//
//	Chooses a random gene and inserts displaced back into the
//	chromosome
//-----------------------------------------------------------------
void CgaTSP::MutateIM(vector<int> &chromo)
{
	//return dependent upon mutation rate
	if (RandFloat() > m_dMutationRate) return;

	//create an iterator for us to work with
	vector<int>::iterator curPos;

	//choose a gene to move
	curPos = chromo.begin() + RandInt(0, chromo.size()-1);

	//keep a note of the genes value
	int CityNumber = *curPos;

	//remove from the chromosome
	chromo.erase(curPos);

	//move the iterator to the insertion location
	curPos = chromo.begin() + RandInt(0, chromo.size()-1);

	chromo.insert(curPos, CityNumber);
}
//------------------------MutateSM--------------------------------
//
//	chooses a random start and point then scrambles the genes 
//	between them
//----------------------------------------------------------------
void CgaTSP::MutateSM(vector<int> &chromo)
{
	//return dependent upon mutation rate
	if (RandFloat() > m_dMutationRate) return;

	//first we choose a section of the chromosome
	const int MinSpanSize = 3;

	//these will hold the beginning and end points of the span
  int beg, end;

	ChooseSection(beg, end, chromo.size()-1, MinSpanSize);

	int span = end - beg;

	//now we just swap randomly chosen genes with the beg/end
	//range a few times to scramble them
	int NumberOfSwapsRqd = span;

	while(--NumberOfSwapsRqd)
	{
		vector<int>::iterator gene1 = chromo.begin();
		vector<int>::iterator gene2 = chromo.begin();

		//choose two loci within the range
		advance(gene1, beg + RandInt(0, span));
		advance(gene2, beg + RandInt(0, span));

		//exchange them
		swap(*gene1, *gene2);
		
	}//repeat
}

//-------------------------MutateDM-------------------------------------
//
//	Select two random points, grab the chunk of chromosome between them 
//	and then insert it back into the chromosome in a random position 
//	displaced from the original.
//----------------------------------------------------------------------
void CgaTSP::MutateDM(vector<int> &chromo)
{
	//return dependent upon mutation rate
	if (RandFloat() > m_dMutationRate) return;

	//first we choose a section of the chromosome
	const int MinSpanSize = 3;
	
	//these will hold the beginning and end points of the span
  int beg, end;
	
	ChooseSection(beg, end, chromo.size()-1, MinSpanSize);

	//setup iterators for our beg/end points
	vector<int>::iterator SectionStart = chromo.begin() + beg;
	vector<int>::iterator SectionEnd   = chromo.begin() + end;

	//hold on to the section we are moving
	vector<int> TheSection;
	TheSection.assign(SectionStart, SectionEnd);

	//erase from current position
	chromo.erase(SectionStart, SectionEnd);

	//move an iterator to a random insertion location
	vector<int>::iterator curPos;
	curPos = chromo.begin() + RandInt(0, chromo.size()-1);

	//re-insert the section
	chromo.insert(curPos, TheSection.begin(), TheSection.end());
	
}

//---------------------------Mutate-----------------------------
//
//	feeds the chromo into the correct mutation function according
//	to its type
//--------------------------------------------------------------
void CgaTSP::Mutate(vector<int> &chromo, MutationType &type)
{
	switch (type)
	{
	case EM:

		MutateEM(chromo);
		
		break;

	case SM:

		MutateSM(chromo);

		break;

	case IM:

		MutateIM(chromo);
		
		break;

  case DM:

		MutateDM(chromo);
		
		break;

	default: break;
	}//end switch
}

//-------------------------CrossoverPMX---------------------------------
//
// crossover operator based on 'partially matched crossover' as 
// defined in the text
//-------------------------------------------------------------------
void CgaTSP::CrossoverPMX(	const vector<int>	&mum, 
							              const vector<int>	&dad, 
							              vector<int>			&baby1, 
							              vector<int>			&baby2)
{
	baby1 = mum;
	baby2 = dad;
	
	//just return dependent on the crossover rate or if the
	//chromosomes are the same.
	if ( (RandFloat() > m_dCrossoverRate) || (mum == dad)) 
	{
		return;
	}

	//first we choose a section of the chromosome
	int beg = RandInt(0, mum.size()-2);
	
	int end = beg;
	
	//find an end
	while (end <= beg)
	{
		end = RandInt(0, mum.size()-1);
	}

	//now we iterate through the matched pairs of genes from beg
	//to end swapping the places in each child
	vector<int>::iterator posGene1, posGene2;

	for (int pos = beg; pos < end+1; ++pos)
	{
		//these are the genes we want to swap
		int gene1 = mum[pos];
		int gene2 = dad[pos];

		if (gene1 != gene2)
		{
			//find and swap them in baby1
			posGene1 = find(baby1.begin(), baby1.end(), gene1);
			posGene2 = find(baby1.begin(), baby1.end(), gene2);

			swap(*posGene1, *posGene2);

			//and in baby2
			posGene1 = find(baby2.begin(), baby2.end(), gene1);
			posGene2 = find(baby2.begin(), baby2.end(), gene2);
			
			swap(*posGene1, *posGene2);
		}
		
	}//next pair
}	

//-------------------------CrossoverOBX---------------------------------
//
// Order Based operator as described in Chapter 5
//-------------------------------------------------------------------
void CgaTSP::CrossoverOBX(	const vector<int>	&mum, 
							              const vector<int>	&dad, 
							              vector<int>			&baby1, 
							              vector<int>			&baby2)
{
  baby1 = mum;
	baby2 = dad;
	
	//just return dependent on the crossover rate or if the
	//chromosomes are the same.
	if ( (RandFloat() > m_dCrossoverRate) || (mum == dad)) 
	{
		return;
	}
 
  //holds the chosen cities
  vector<int> tempCities;

  //holds the positions of the chosen cities
  vector<int> positions;

  //first city position
  int Pos = RandInt(0, mum.size()-2);

  //keep adding random cities until we can add no more
  //record the positions as we go
  while (Pos < mum.size())
  {
    positions.push_back(Pos);

    tempCities.push_back(mum[Pos]);

    //next city
    Pos += RandInt(1, mum.size()-Pos);
  }

  //so now we have n amount of cities from mum in the tempCities
  //vector we can impose their order in dad.
  int cPos = 0;

  for (int cit=0; cit<baby2.size(); ++cit)
  {
    for (int i=0; i<tempCities.size(); ++i)
    {
      if (baby2[cit]==tempCities[i])
      {
         baby2[cit] = tempCities[cPos];

         ++cPos;

         break;
      }
    }
  }

   //now vice versa
  tempCities.clear();
  cPos = 0;

  //first grab the cities from the same positions in dad
  for(int i=0; i<positions.size(); ++i)
  {
    tempCities.push_back(dad[positions[i]]);
  }

  //and impose their order in mum
  for (cit=0; cit<baby1.size(); ++cit)
  {
    for (int i=0; i<tempCities.size(); ++i)
    {
      if (baby1[cit]==tempCities[i])
      {
         baby1[cit] = tempCities[cPos];

         ++cPos;

         break;
      }
    }
  }    
}

//----------------------- CrossoverPBX -----------------------------------
//
//  Position Based Crossover as described in Chapter 5
//------------------------------------------------------------------------
void CgaTSP::CrossoverPBX(	const vector<int>	&mum, 
							              const vector<int>	&dad, 
							              vector<int>			&baby1, 
							              vector<int>			&baby2)
{	
	//Return dependent on the crossover rate or if the
	//chromosomes are the same.
	if ( (RandFloat() > m_dCrossoverRate) || (mum == dad)) 
	{
    //make sure baby1 and baby2 are assigned some cities first!
    baby1 = mum;
    baby2 = dad;
    
		return;
	}

  //initialize the babies with minus values so we can tell which positions
  //have been filled later in the algorithm
  baby1.assign(mum.size(), -1);
  baby2.assign(mum.size(), -1);

  int l = baby2.size();

  //holds the positions of the chosen cities
  vector<int> positions;

  //first city position
  int Pos = RandInt(0, mum.size()-2);

  //keep adding random cities until we can add no more
  //record the positions as we go
  while (Pos < mum.size())
  {
    positions.push_back(Pos);

    //next city
    Pos += RandInt(1, mum.size()-Pos);
  }
  
  //now we have chosen some cities it's time to copy the selected cities
  //over into the offspring in the same position.
  for (int pos=0; pos<positions.size(); ++pos)
  {
    //baby1 receives from mum
    baby1[positions[pos]] = mum[positions[pos]];

    //baby2 receives from dad
    baby2[positions[pos]] = dad[positions[pos]];
  }

  //fill in the blanks. First create two position markers so we know
  //whereabouts we are in baby1 and baby2
  int c1 = 0, c2 = 0;

  for (pos=0; pos<mum.size(); ++pos)
  {   
    //advance position marker until we reach a free position
    //in baby2
    while( (baby2[c2] > -1) && (c2 < mum.size()))
    {
      ++c2;
    }
    
    //baby2 gets the next city from mum which is not already
    //present
    if ( (!TestNumber(baby2, mum[pos])) )
    {
      baby2[c2] = mum[pos]; 
    }

    //now do the same for baby1
    while((baby1[c1] > -1) && (c1 < mum.size()))
    {      
      ++c1;
    }
    
    //baby1 gets the next city from dad which is not already
    //present
    if ( (!TestNumber(baby1, dad[pos])) )
    {
      baby1[c1] = dad[pos];
    }     
  }
}
//--------------------- Crossover ----------------------------------------
//
//  simple switch statement to perform crossover based on the selected
//  CrossoverType, type
//------------------------------------------------------------------------
void CgaTSP::Crossover(const vector<int>	&mum, 
							         const vector<int>	&dad, 
							         vector<int>        &baby1, 
							         vector<int>        &baby2,
                       CrossoverType      type)
{
  //perform crossover based on type
  switch(type)
  {
  case OBX:

    CrossoverOBX(mum, dad, baby1, baby2);

    break;

  case PMX:

    CrossoverPMX(mum, dad, baby1, baby2);

    break;

  case PBX:

    CrossoverPBX(mum, dad, baby1, baby2);

    break;


  default: break;

  }//end switch
}

//-----------------------CreateStartingPopulation()------------------------
//
//	clears any existing population, fills a vector with a random population
//	of genomes and resets appropriate member variables
//-------------------------------------------------------------------------
void CgaTSP::CreateStartingPopulation()
{
	//make sure the vector of genomes is empty before we
	//start
	m_vecPopulation.clear();
	
	//create a new population of random genomes
	for (int i=0; i<m_iPopSize; ++i)
	{
		m_vecPopulation.push_back(SGenome(m_iChromoLength));
	}

	//make sure variables are initialised correctly
	m_iGeneration	        = 0;
	m_dShortestRoute      = 9999999;
	m_dBestFitness	      = 0;
	m_dWorstFitness       = 9999999;
	m_dAverageFitness     = 0;
	m_iFittestGenome      = 0;
	m_bStarted			      = false;
  m_dBoltzmannTemp      = NUM_CITIES * 2;

}
//-----------------------------------Run-----------------------------------
//
//	This is the function that initializes a new population and sets the
//  ga running 
//------------------------------------------------------------------------
void CgaTSP::Run(HWND hwnd)
{
	//The first thing we have to do is create a random population
	//of genomes
	CreateStartingPopulation();

	m_bStarted = true;

}
//-------------------------Reset()------------------------------
//
//	resets all the relevant variables ready for a new generation
//--------------------------------------------------------------
void CgaTSP::Reset()
{
	//just make the shortest route some excessively large distance
	m_dShortestRoute	= 999999999;
	m_dLongestRoute		= 0;
	m_dTotalFitness		= 0;
	m_dBestFitness		= 0;
	m_dWorstFitness		= 9999999;
	m_dAverageFitness	= 0;
	m_bSorted			    = false;
  m_dSigma          = 1;
}

//------------------------Epoch-------------------------------
//
//	creates a new population of genomes using the selection,
//	mutation and crossover operators
//------------------------------------------------------------
void CgaTSP::Epoch()
{

	//first we reset variables and calculate the fitness of each genome
	Reset();
	
	CalculatePopulationsFitness();

	//if we have found a solution exit
	if ((m_dShortestRoute <= m_pMap->BestPossibleRoute()))
	{
		m_bStarted = false;
		
		return;
	}	

  //perform the appropriate fitness scaling
  FitnessScaleSwitch();

  //if sigma is zero (either set in sigma scaling or in CalculateBestWorstAv
  //then the population are identical and we should stop the run
  if (m_dSigma == 0)
  {
    m_bStarted = false;

    return;
  }
	
	//create a temporary vector for the new population
	vector<SGenome> vecNewPop;
	
  if (m_bElitism)
  {
	  //Now to add a little elitism we shall add in some copies of the
	  //fittest genomes
	  const int CopiesToAdd = 2;
	  const int NBest		  = 4;
	  
	  //make sure we add an EVEN number or the roulette wheel
	  //sampling will crash
	  if (!(CopiesToAdd * NBest % 2))
	  {
		  GrabNBest(NBest, CopiesToAdd, vecNewPop);
	  }
  }

  //SUS selection selects the entire population all at once so we have to
  //handle the epoch slightly differently if SUS is chosen
  if(m_SelectionType != SUS)
  {
	  //now create the remainder of the population
	  while (vecNewPop.size() != m_iPopSize)
	  {
	  
		  SGenome mum, dad;
    
      //switch on selection method
      switch(m_SelectionType)
      {
      case ROULETTE:
  
        //grab two parents dependent on the selection method
		    mum = RouletteWheelSelection();
		    dad = RouletteWheelSelection();

        break;

      case TOURNAMENT:

        mum = TournamentSelection(NUM_TO_COMPARE);
	      dad = TournamentSelection(NUM_TO_COMPARE);

        break;

      case ALT_TOURNAMENT:
 
        mum = AlternativeTournamentSelection();
	      dad = AlternativeTournamentSelection();

        break;
      }

		  //create 2 children
		  SGenome baby1, baby2;
		  
		  //Breed them
      Crossover(mum.vecCities,
                dad.vecCities,
                baby1.vecCities,
                baby2.vecCities,
                m_CrossoverType);

		  //and mutate them
		  Mutate(baby1.vecCities, m_MutationType);
		  Mutate(baby2.vecCities, m_MutationType);

		  //add them to new population
		  vecNewPop.push_back(baby1);
		  vecNewPop.push_back(baby2);
	  }
  }

  //SUS selection
  else
  {
    //select all the individuals
    vector<SGenome> vecSampledPop;

    SUSSelection(vecSampledPop);

    //step through the newly sampled population and apply crossover
    //and mutation operators
    for (int gen=0; gen<vecSampledPop.size(); gen+=2)
    {
      SGenome baby1, baby2;
      
      Crossover(vecSampledPop[gen].vecCities,
                vecSampledPop[gen+1].vecCities,
                baby1.vecCities,
                baby2.vecCities,
                m_CrossoverType);

      Mutate(baby1.vecCities, m_MutationType);
      Mutate(baby2.vecCities, m_MutationType);

      vecNewPop.push_back(baby1);
      vecNewPop.push_back(baby2);      

    }
   
  }

	//copy into next generation
	m_vecPopulation = vecNewPop;

	//increment generation counter
	++m_iGeneration;
}

//-------------------------------Render-------------------------------
//
//	This function does all the drawing and textual output. Called from
// the winproc when it receives a WM_PAINT msg
//--------------------------------------------------------------------
void CgaTSP::Render(HDC surface, int cx, int cy)const
{

		//draw all the cities
	for (int city_num = 0; city_num < m_pMap->m_vecCityCoOrds.size(); ++city_num)
	{
		int x = (int)m_pMap->m_vecCityCoOrds[city_num].x;
		int y = (int)m_pMap->m_vecCityCoOrds[city_num].y;
		
		Ellipse(surface, x-CITY_SIZE, y+CITY_SIZE, x+CITY_SIZE, y-CITY_SIZE);
	}
	
	//draw the fittest route so far
	vector<int> route = m_vecPopulation[m_iFittestGenome].vecCities;
	
	//only display the routes if we are in a run
	if (m_iGeneration != 0)
	{ 
		MoveToEx(surface, (int)m_pMap->m_vecCityCoOrds[route[0]].x, (int)m_pMap->m_vecCityCoOrds[route[0]].y, NULL);
		
		for (int i=1; i<route.size(); ++i)
		{
			int CityX = (int)m_pMap->m_vecCityCoOrds[route[i]].x;
			int CityY = (int)m_pMap->m_vecCityCoOrds[route[i]].y;
			
			LineTo(surface, CityX, CityY);
			
			//draw the numbers representing the order the cities are visited.
			//No point drawing them after about a 100 cities as the display
			//just becomes confused
			if (NUM_CITIES < 100)
			{
				string CityNumber = itos(i);
			
				TextOut(surface, CityX, CityY, CityNumber.c_str(), CityNumber.size());
			}
		}

		//now draw the line from the last city visited back to the starting point
		LineTo(surface, (int)m_pMap->m_vecCityCoOrds[route[0]].x, (int)m_pMap->m_vecCityCoOrds[route[0]].y);
	}	
	
	//print stats
	string sGen = itos(m_iGeneration);
	sGen = "Generation: " + sGen;
	TextOut(surface, 5, cy - 20, sGen.c_str(), sGen.size());


	if (!m_bStarted)
	{
		string Start = "Press Return to start a new run";

		TextOut(surface, cx/2 - (Start.size() * 3), cy - 20, Start.c_str(), Start.size());

    if (m_dSigma == 0)
    {
      string s = "Premature Convergence!";

      TextOut(surface, cx-40 - (Start.size() * 3), cy-20, s.c_str(), s.size());
    }
	}

	else

	{
		string Start = "Space to stop";
		
		TextOut(surface, cx/2 - (Start.size() * 3), cy - 20, Start.c_str(), Start.size());
	}	

 

  //render the current Boltzmann temperature if applicable
  if (m_ScaleType == BOLTZMANN)
  {
    string s = "Boltzmann Temp: " + ftos(m_dBoltzmannTemp);
    TextOut(surface, 400, 5, s.c_str(), s.size());
  }
    
}


