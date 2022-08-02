#include "CgaBob.h"



//--------------------------RouletteWheelSelection-----------------
//
//	selects a member of the population by using roulette wheel 
//	selection as described in the text.
//------------------------------------------------------------------
SGenome& CgaBob::RouletteWheelSelection()
{
	double fSlice	= RandFloat() * m_dTotalFitnessScore;
	
	double cfTotal	= 0.0;
	
	int	SelectedGenome = 0;
	
	for (int i=0; i<m_iPopSize; ++i)
	{
		
		cfTotal += m_vecGenomes[i].dFitness;
		
		if (cfTotal > fSlice) 
		{
			SelectedGenome = i;
			break;
		}
	}
	
	return m_vecGenomes[SelectedGenome];
}

//----------------------------Mutate---------------------------------
//	iterates through each genome flipping the bits acording to the
//	mutation rate
//--------------------------------------------------------------------
void CgaBob::Mutate(vector<int> &vecBits)
{
	for (int curBit=0; curBit<vecBits.size(); curBit++)
	{
		//do we flip this bit?
		if (RandFloat() < m_dMutationRate)
		{
			//flip the bit
			vecBits[curBit] = !vecBits[curBit];
		}
	}//next bit
}

//----------------------------Crossover--------------------------------
//	Takes 2 parent vectors, selects a midpoint and then swaps the ends
//	of each genome creating 2 new genomes which are stored in baby1 and
//	baby2.
//---------------------------------------------------------------------
void CgaBob::Crossover( const vector<int> &mum,
						const vector<int> &dad,
						vector<int>		  &baby1,
						vector<int>		  &baby2)
{
	//just return parents as offspring dependent on the rate
	//or if parents are the same
	if ( (RandFloat() > m_dCrossoverRate) || (mum == dad)) 
	{
		baby1 = mum;
		baby2 = dad;

		return;
	}
	
	//determine a crossover point
	int cp = RandInt(0, m_iChromoLength - 1);

	//swap the bits
	for (int i=0; i<cp; ++i)
	{
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}

	for (i=cp; i<mum.size(); ++i)
	{
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}
}
//-----------------------------------Run----------------------------------
//
//	This is the function that starts everything. It is mainly another 
//	windows message pump using PeekMessage instead of GetMessage so we
//	can easily and dynamically make updates to the window while the GA is 
//	running. Basically, if there is no msg to be processed another Epoch
//	is performed.
//------------------------------------------------------------------------
void CgaBob::Run(HWND hwnd)
{
	//The first thing we have to do is create a random population
	//of genomes
	CreateStartPopulation();
	
	m_bBusy = true;
		
}
//----------------------CreateStartPopulation---------------------------
//
//-----------------------------------------------------------------------
void CgaBob::CreateStartPopulation()
{
	//clear existing population
	m_vecGenomes.clear();
	
	for (int i=0; i<m_iPopSize; i++)
	{
		m_vecGenomes.push_back(SGenome(m_iChromoLength));
	}

	//reset all variables
	m_iGeneration		 = 0;
	m_iFittestGenome	 = 0;
	m_dBestFitnessScore  = 0;
	m_dTotalFitnessScore = 0;
}
//--------------------------------Epoch---------------------------------
//
//	This is the workhorse of the GA. It first updates the fitness
//	scores of the population then creates a new population of
//	genomes using the Selection, Croosover and Mutation operators
//	we have discussed
//----------------------------------------------------------------------
void CgaBob::Epoch()
{
	
	UpdateFitnessScores();

	//Now to create a new population
	int NewBabies = 0;

	//create some storage for the baby genomes 
	vector<SGenome> vecBabyGenomes;

	while (NewBabies < m_iPopSize)
	{
		//select 2 parents
		SGenome mum = RouletteWheelSelection();
		SGenome dad = RouletteWheelSelection();

		//operator - crossover
		SGenome baby1, baby2;
		Crossover(mum.vecBits, dad.vecBits, baby1.vecBits, baby2.vecBits);

		//operator - mutate
		Mutate(baby1.vecBits);
		Mutate(baby2.vecBits);

		//add to new population
		vecBabyGenomes.push_back(baby1);
		vecBabyGenomes.push_back(baby2);

		NewBabies += 2;
	}

	//copy babies back into starter population
	m_vecGenomes = vecBabyGenomes;

	//increment the generation counter
	++m_iGeneration;
}

//---------------------------UpdateFitnessScores------------------------
//	updates the genomes fitness with the new fitness scores and calculates
//	the highest fitness and the fittest member of the population.
//	Also sets m_pFittestGenome to point to the fittest. If a solution
//	has been found (fitness == 1 in this example) then the run is halted
//	by setting m_bBusy to false
//-----------------------------------------------------------------------
void CgaBob::UpdateFitnessScores()
{
	m_iFittestGenome		= 0;
	m_dBestFitnessScore		= 0;
	m_dTotalFitnessScore	= 0;

	CBobsMap TempMemory;
	 
	//update the fitness scores and keep a check on fittest so far
	for (int i=0; i<m_iPopSize; ++i)
	{
		//decode each genomes chromosome into a vector of directions
		vector<int> vecDirections = Decode(m_vecGenomes[i].vecBits);

		//get it's fitness score
		m_vecGenomes[i].dFitness = m_BobsMap.TestRoute(vecDirections, TempMemory);

		//update total
		m_dTotalFitnessScore += m_vecGenomes[i].dFitness;

		//if this is the fittest genome found so far, store results
		if (m_vecGenomes[i].dFitness > m_dBestFitnessScore)
		{
			m_dBestFitnessScore = m_vecGenomes[i].dFitness;

			m_iFittestGenome = i;

			m_BobsBrain = TempMemory;

			//Has Bob found the exit?
			if (m_vecGenomes[i].dFitness == 1)
			{
				//is so, stop the run
				m_bBusy = false;
			}
		}

		TempMemory.ResetMemory();
	
	}//next genome
}

//---------------------------Decode-------------------------------------
//
//	decodes a vector of bits into a vector of directions (ints)
//
//	0=North, 1=South, 2=East, 3=West
//-----------------------------------------------------------------------
vector<int> CgaBob::Decode(const vector<int> &bits)
{
	vector<int>	directions;

	//step through the chromosome a gene at a time
	for (int gene=0; gene < bits.size(); gene += m_iGeneLength)
	{
		//get the gene at this position
		vector<int> ThisGene;
		
		for (int bit = 0; bit < m_iGeneLength; ++bit)
		{
			ThisGene.push_back(bits[gene+bit]);
		}

		//convert to decimal and add to list of directions
		directions.push_back(BinToInt(ThisGene));
	}

	return directions;
}

//-------------------------------BinToInt-------------------------------
//	converts a vector of bits into an integer
//----------------------------------------------------------------------
int	CgaBob::BinToInt(const vector<int> &vec)
{
	int val = 0;
	int multiplier = 1;
	
	for (int cBit=vec.size(); cBit>0; cBit--)
	{
		val += vec[cBit-1] * multiplier;
		
		multiplier *= 2;
	}

	return val;
}



//------------------------- Render -------------------------------
//
//	given a surface to render to this function renders the map
//	and the best path if relevant. cxClient/cyClient are the 
//	dimensions of the client window.
//----------------------------------------------------------------
void CgaBob::Render(int cxClient, int cyClient, HDC surface)
{
	//render the map
	m_BobsMap.Render(cxClient, cyClient, surface);

	//render the best route
	m_BobsBrain.MemoryRender(cxClient, cyClient, surface);

	//Render additional information
	string s = "Generation: " + itos(m_iGeneration);
	TextOut(surface, 5, 0, s.c_str(), s.size());
	
	if (!m_bBusy)
	{
		string Start = "Press Return to start a new run";
		
		TextOut(surface, cxClient/2 - (Start.size() * 3), cyClient - 20, Start.c_str(), Start.size());
	}
	
	else
		
	{
		string Start = "Space to stop";
		
		TextOut(surface, cxClient/2 - (Start.size() * 3), cyClient - 20, Start.c_str(), Start.size());
	}
	
}
