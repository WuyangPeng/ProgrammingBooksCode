#include "Cga.h"


//-------------------------------------------------------------------------
//	this constructor creates a base genome from supplied values and creates 
//	a population of 'size' similar (same topology, varying weights) genomes
//-------------------------------------------------------------------------
Cga::Cga(int  size,
         int  inputs,
         int  outputs,
         HWND hwnd,
         int  cx,
         int  cy):  m_iPopSize(size),
                    m_iGeneration(0),
                    m_pInnovation(NULL),
                    m_iNextGenomeID(0),
                    m_iNextSpeciesID(0),
                    m_iFittestGenome(0),
                    m_dBestEverFitness(0),
                    m_dTotFitAdj(0),
                    m_dAvFitAdj(0),
                    m_hwnd(hwnd),
                    cxClient(cx),
                    cyClient(cy)
{
	//create the population of genomes
	for (int i=0; i<m_iPopSize; ++i)
	{
			m_vecGenomes.push_back(CGenome(m_iNextGenomeID++, inputs, outputs));
	}

	//create the innovation list. First create a minimal genome
	CGenome genome(1, inputs, outputs);

	//create the innovations
  m_pInnovation = new CInnovation(genome.Genes(), genome.Neurons());

  //create the network depth lookup table
  vecSplits = Split(0, 1, 0);
}

//------------------------------------- dtor -----------------------------
//
//------------------------------------------------------------------------
Cga::~Cga()
{
  if (m_pInnovation)
  {
    delete m_pInnovation;
      
    m_pInnovation = NULL;
  } 
}

//-------------------------------CreatePhenotypes-------------------------
//
//	cycles through all the members of the population and creates their
//  phenotypes. Returns a vector containing pointers to the new phenotypes
//-------------------------------------------------------------------------
vector<CNeuralNet*> Cga::CreatePhenotypes()
{
	vector<CNeuralNet*> networks;

  for (int i=0; i<m_iPopSize; i++)
	{
    //calculate max network depth
    int depth = CalculateNetDepth(m_vecGenomes[i]);

		//create new phenotype
		CNeuralNet* net = m_vecGenomes[i].CreatePhenotype(depth);

    networks.push_back(net);
	}

	return networks;
}

//-------------------------- CalculateNetDepth ---------------------------
//
//  searches the lookup table for the dSplitY value of each node in the 
//  genome and returns the depth of the network based on this figure
//------------------------------------------------------------------------
int Cga::CalculateNetDepth(const CGenome &gen)
{
  int MaxSoFar = 0;

  for (int nd=0; nd<gen.NumNeurons(); ++nd)
  {
    for (int i=0; i<vecSplits.size(); ++i)
    {
     
      if ((gen.SplitY(nd) == vecSplits[i].val) &&
          (vecSplits[i].depth > MaxSoFar))
      {
        MaxSoFar = vecSplits[i].depth;
      }
    }
  }
  return MaxSoFar + 2;
}


//-----------------------------------AddNeuronID----------------------------
//
//	just checks to see if a node ID has already been added to a vector of
//  nodes. If not 	then the new ID  gets added. Used in Crossover.
//------------------------------------------------------------------------
void Cga::AddNeuronID(const int nodeID, vector<int> &vec)
{
	for (int i=0; i<vec.size(); i++)
	{
		if (vec[i] == nodeID)
		{
			//already added
			return;
		}
	}

	vec.push_back(nodeID);

	return;
}

//------------------------------------- Epoch ----------------------------
//
//  This function performs one epoch of the genetic algorithm and returns 
//  a vector of pointers to the new phenotypes
//------------------------------------------------------------------------
vector<CNeuralNet*> Cga::Epoch(const vector<double> &FitnessScores)
{
  //first check to make sure we have the correct amount of fitness scores
  if (FitnessScores.size() != m_vecGenomes.size())
  {
    MessageBox(NULL,"Cga::Epoch(scores/ genomes mismatch)!","Error", MB_OK);
  }

  //reset appropriate values and kill off the existing phenotypes and
  //any poorly performing species
  ResetAndKill();

  //update the genomes with the fitnesses scored in the last run
  for (int gen=0; gen<m_vecGenomes.size(); ++gen)
  {
    m_vecGenomes[gen].SetFitness(FitnessScores[gen]);
  }

  //sort genomes and keep a record of the best performers
  SortAndRecord();

  //separate the population into species of similar topology, adjust
  //fitnesses and calculate spawn levels
  SpeciateAndCalculateSpawnLevels();

  //this will hold the new population of genomes
  vector<CGenome> NewPop;

  //request the offspring from each species. The number of children to 
  //spawn is a double which we need to convert to an int. 
  int NumSpawnedSoFar = 0;

  CGenome baby;

  //now to iterate through each species selecting offspring to be mated and 
  //mutated	
  for (int spc=0; spc<m_vecSpecies.size(); ++spc)
  {
    //because of the number to spawn from each species is a double
    //rounded up or down to an integer it is possible to get an overflow
    //of genomes spawned. This statement just makes sure that doesn't
    //happen
    if (NumSpawnedSoFar < CParams::iNumSweepers)
    {
      //this is the amount of offspring this species is required to
      // spawn. Rounded simply rounds the double up or down.
      int NumToSpawn = Rounded(m_vecSpecies[spc].NumToSpawn());

      bool bChosenBestYet = false;

      while (NumToSpawn--)
      {
        //first grab the best performing genome from this species and transfer
        //to the new population without mutation. This provides per species
        //elitism
        if (!bChosenBestYet)
        {         
          baby = m_vecSpecies[spc].Leader();

          bChosenBestYet = true;
        }

        else
        {
          //if the number of individuals in this species is only one
          //then we can only perform mutation
          if (m_vecSpecies[spc].NumMembers() == 1)
          {         
            //spawn a child
            baby = m_vecSpecies[spc].Spawn();
          }

          //if greater than one we can use the crossover operator
          else
          {
            //spawn1
            CGenome g1 = m_vecSpecies[spc].Spawn();

            if (RandFloat() < CParams::dCrossoverRate)
            {

              //spawn2, make sure it's not the same as g1
              CGenome g2 = m_vecSpecies[spc].Spawn();

              //number of attempts at finding a different genome
              int NumAttempts = 5;

              while ( (g1.ID() == g2.ID()) && (NumAttempts--) )
              {  
                g2 = m_vecSpecies[spc].Spawn();
              }

              if (g1.ID() != g2.ID())
              {
                baby = Crossover(g1, g2);
              }
            }

            else
            {
              baby = g1;
            }
          }

          
          ++m_iNextGenomeID;

          baby.SetID(m_iNextGenomeID);

          //now we have a spawned child lets mutate it! First there is the
          //chance a neuron may be added
          if (baby.NumNeurons() < CParams::iMaxPermittedNeurons)
          {      
            baby.AddNeuron(CParams::dChanceAddNode,
                           *m_pInnovation,
                           CParams::iNumTrysToFindOldLink);
          }

          //now there's the chance a link may be added
          baby.AddLink(CParams::dChanceAddLink,
                       CParams::dChanceAddRecurrentLink,
                       *m_pInnovation,
                       CParams::iNumTrysToFindLoopedLink,
                       CParams::iNumAddLinkAttempts);

          //mutate the weights
          baby.MutateWeights(CParams::dMutationRate,
                             CParams::dProbabilityWeightReplaced,
                             CParams::dMaxWeightPerturbation);

          baby.MutateActivationResponse(CParams::dActivationMutationRate,
                                        CParams::dMaxActivationPerturbation);
        }

        //sort the babies genes by their innovation numbers
        baby.SortGenes();

        //add to new pop
        NewPop.push_back(baby);

        ++NumSpawnedSoFar;

        if (NumSpawnedSoFar == CParams::iNumSweepers)
        {        
          NumToSpawn = 0;
        }

      }//end while
       
    }//end if
     
  }//next species


  //if there is an underflow due to the rounding error and the amount
  //of offspring falls short of the population size additional children
  //need to be created and added to the new population. This is achieved
  //simply, by using tournament selection over the entire population.
  if (NumSpawnedSoFar < CParams::iNumSweepers)
  {

    //calculate amount of additional children required
    int Rqd = CParams::iNumSweepers - NumSpawnedSoFar;

    //grab them
    while (Rqd--)
    {
      NewPop.push_back(TournamentSelection(m_iPopSize/5));
    }
  }

  //replace the current population with the new one
  m_vecGenomes = NewPop;

  //create the new phenotypes
  vector<CNeuralNet*> new_phenotypes;

  for (gen=0; gen<m_vecGenomes.size(); ++gen)
  {
    //calculate max network depth
    int depth = CalculateNetDepth(m_vecGenomes[gen]);
    
    CNeuralNet* phenotype = m_vecGenomes[gen].CreatePhenotype(depth);

    new_phenotypes.push_back(phenotype);
  }

  //increase generation counter
  ++m_iGeneration;

  return new_phenotypes;
}

//--------------------------- SortAndRecord-------------------------------
//
//  sorts the population into descending fitness, keeps a record of the
//  best n genomes and updates any fitness statistics accordingly
//------------------------------------------------------------------------
void Cga::SortAndRecord()
{
  //sort the genomes according to their unadjusted (no fitness sharing)
  //fitnesses
  sort(m_vecGenomes.begin(), m_vecGenomes.end());

  //is the best genome this generation the best ever?
  if (m_vecGenomes[0].Fitness() > m_dBestEverFitness)
  {
    m_dBestEverFitness = m_vecGenomes[0].Fitness();
  }

  //keep a record of the n best genomes
  StoreBestGenomes();
}

//----------------------------- StoreBestGenomes -------------------------
//
//  used to keep a record of the previous populations best genomes so that 
//  they can be displayed if required.
//------------------------------------------------------------------------
void Cga::StoreBestGenomes()
{
  //clear old record
  m_vecBestGenomes.clear();

  for (int gen=0; gen<CParams::iNumBestSweepers; ++gen)
  {
    m_vecBestGenomes.push_back(m_vecGenomes[gen]);
  }
}

//----------------- GetBestPhenotypesFromLastGeneration ------------------
//
//  returns a std::vector of the n best phenotypes from the previous
//  generation
//------------------------------------------------------------------------
vector<CNeuralNet*> Cga::GetBestPhenotypesFromLastGeneration()
{
  vector<CNeuralNet*> brains;

  for (int gen=0; gen<m_vecBestGenomes.size(); ++gen)
  {
    //calculate max network depth
    int depth = CalculateNetDepth(m_vecBestGenomes[gen]);

    brains.push_back(m_vecBestGenomes[gen].CreatePhenotype(depth));
  }

  return brains;
}

//--------------------------- AdjustSpecies ------------------------------
//
//  this functions simply iterates through each species and calls 
//  AdjustFitness for each species
//------------------------------------------------------------------------
void Cga::AdjustSpeciesFitnesses()
{
  for (int sp=0; sp<m_vecSpecies.size(); ++sp)
  {
    m_vecSpecies[sp].AdjustFitnesses();
  }
}

//------------------ SpeciateAndCalculateSpawnLevels ---------------------
//
//  separates each individual into its respective species by calculating
//  a compatibility score with every other member of the population and 
//  niching accordingly. The function then adjusts the fitness scores of
//  each individual by species age and by sharing and also determines
//  how many offspring each individual should spawn.
//------------------------------------------------------------------------
void Cga::SpeciateAndCalculateSpawnLevels()
{
  bool bAdded = false;

  //iterate through each genome and speciate
  for (int gen=0; gen<m_vecGenomes.size(); ++gen)
  {
    //calculate its compatibility score with each species leader. If
    //compatible add to species. If not, create a new species
    for (int spc=0; spc<m_vecSpecies.size(); ++spc)
    {
      double compatibility = m_vecGenomes[gen].GetCompatibilityScore(m_vecSpecies[spc].Leader());

      //if this individual is similar to this species add to species
      if (compatibility <= CParams::dCompatibilityThreshold)
      {
        m_vecSpecies[spc].AddMember(m_vecGenomes[gen]);

        //let the genome know which species it's in
        m_vecGenomes[gen].SetSpecies(m_vecSpecies[spc].ID());

        bAdded = true;

        break;
      }
    }
    
    if (!bAdded)
    {
      //we have not found a compatible species so let's create a new one
      m_vecSpecies.push_back(CSpecies(m_vecGenomes[gen], m_iNextSpeciesID++));
    }

    bAdded = false;
  }

  //now all the genomes have been assigned a species the fitness scores 
  //need to be adjusted to take into account sharing and species age.
  AdjustSpeciesFitnesses();
  
  //calculate new adjusted total & average fitness for the population
  for (gen=0; gen<m_vecGenomes.size(); ++gen)
  {   
     m_dTotFitAdj += m_vecGenomes[gen].GetAdjFitness();
  }

  m_dAvFitAdj = m_dTotFitAdj/m_vecGenomes.size();

  //calculate how many offspring each member of the population
  //should spawn
  for (gen=0; gen<m_vecGenomes.size(); ++gen)
  {   
     double ToSpawn = m_vecGenomes[gen].GetAdjFitness() / m_dAvFitAdj;

     m_vecGenomes[gen].SetAmountToSpawn(ToSpawn);
  }

  //iterate through all the species and calculate how many offspring
  //each species should spawn
  for (int spc=0; spc<m_vecSpecies.size(); ++spc)
  {
    m_vecSpecies[spc].CalculateSpawnAmount();
  }
}


//--------------------------- TournamentSelection ------------------------
//
//------------------------------------------------------------------------
CGenome Cga::TournamentSelection(const int NumComparisons)
{
   double BestFitnessSoFar = 0;
  
   int ChosenOne = 0;

   //Select NumComparisons members from the population at random testing  
   //against the best found so far
   for (int i=0; i<NumComparisons; ++i)
   {
     int ThisTry = RandInt(0, m_vecGenomes.size()-1);

     if (m_vecGenomes[ThisTry].Fitness() > BestFitnessSoFar)
     {
       ChosenOne = ThisTry;

       BestFitnessSoFar = m_vecGenomes[ThisTry].Fitness();
     }
   }

   //return the champion
   return m_vecGenomes[ChosenOne];
}
                                 
//-----------------------------------Crossover----------------------------
//	
//------------------------------------------------------------------------
CGenome Cga::Crossover(CGenome& mum, CGenome& dad)
{

  //helps make the code clearer
  enum parent_type{MUM, DAD,};
  
  //first, calculate the genome we will using the disjoint/excess
  //genes from. This is the fittest genome.
  parent_type best;

  //if they are of equal fitness use the shorter (because we want to keep
  //the networks as small as possible)
  if (mum.Fitness() == dad.Fitness())
  {
    //if they are of equal fitness and length just choose one at
    //random
    if (mum.NumGenes() == dad.NumGenes())
    {
      best = (parent_type)RandInt(0, 1);
    }

    else
    {
      if (mum.NumGenes() < dad.NumGenes())
      {
        best = MUM;
      }
		  
      else
      {
        best = DAD;
      }
    }
  }

  else 
  {
    if (mum.Fitness() > dad.Fitness())
    {
      best = MUM;
    }

    else
    {
      best = DAD;
    }
  }

  //these vectors will hold the offspring's nodes and genes
  vector<SNeuronGene>  BabyNeurons;
  vector<SLinkGene>    BabyGenes;

  //temporary vector to store all added node IDs
  vector<int> vecNeurons;

  //create iterators so we can step through each parents genes and set
  //them to the first gene of each parent
  vector<SLinkGene>::iterator curMum = mum.StartOfGenes();
  vector<SLinkGene>::iterator curDad = dad.StartOfGenes();

  //this will hold a copy of the gene we wish to add at each step
  SLinkGene SelectedGene;

  //step through each parents genes until we reach the end of both
  while (!((curMum == mum.EndOfGenes()) && (curDad == dad.EndOfGenes())))
  {
	
    //the end of mum's genes have been reached
    if ((curMum == mum.EndOfGenes())&&(curDad != dad.EndOfGenes()))
    {
      //if dad is fittest
      if (best == DAD)
      {
        //add dads genes
        SelectedGene = *curDad;
      }

      //move onto dad's next gene
      ++curDad;
    }

    //the end of dads's genes have been reached
    else if ( (curDad == dad.EndOfGenes()) && (curMum != mum.EndOfGenes()))
    {
      //if mum is fittest
      if (best == MUM)
      {
        //add mums genes
        SelectedGene = *curMum;
      }
			
      //move onto mum's next gene
      ++curMum;
    }

    //if mums innovation number is less than dads
    else if (curMum->InnovationID < curDad->InnovationID)
    {
      //if mum is fittest add gene
      if (best == MUM)
      {
        SelectedGene = *curMum;
      }

      //move onto mum's next gene
      ++curMum;
    }

    //if dads innovation number is less than mums
    else if (curDad->InnovationID < curMum->InnovationID)
    {
      //if dad is fittest add gene
      if (best = DAD)
      {
        SelectedGene = *curDad;
      }

      //move onto dad's next gene
      ++curDad;
    }

    //if innovation numbers are the same
    else if (curDad->InnovationID == curMum->InnovationID)
    {
      //grab a gene from either parent
      if (RandFloat() < 0.5f)
      {
        SelectedGene = *curMum;
      }

      else
      {
        SelectedGene = *curDad;
      }

      //move onto next gene of each parent
      ++curMum;
      ++curDad;
    }
	
    //add the selected gene if not already added
    if (BabyGenes.size() == 0)
    {
      BabyGenes.push_back(SelectedGene);
    }

    else
    {
      if (BabyGenes[BabyGenes.size()-1].InnovationID !=
          SelectedGene.InnovationID)
      {
        BabyGenes.push_back(SelectedGene);
      }
    }   

    //Check if we already have the nodes referred to in SelectedGene.
    //If not, they need to be added.		
    AddNeuronID(SelectedGene.FromNeuron, vecNeurons);
    AddNeuronID(SelectedGene.ToNeuron, vecNeurons);
		
  }//end while

  //now create the required nodes. First sort them into order
  sort(vecNeurons.begin(), vecNeurons.end());
  
  for (int i=0; i<vecNeurons.size(); i++)
  {
    BabyNeurons.push_back(m_pInnovation->CreateNeuronFromID(vecNeurons[i]));
  }

  //finally, create the genome
  CGenome babyGenome(m_iNextGenomeID++,
                     BabyNeurons,
                     BabyGenes,
                     mum.NumInputs(),
                     mum.NumOutputs());

  return babyGenome;
}


//--------------------------- ResetAndKill -------------------------------
//
//  This function resets some values ready for the next epoch, kills off
//  all the phenotypes and any poorly performing species.
//------------------------------------------------------------------------
void Cga::ResetAndKill()
{
  m_dTotFitAdj = 0;
  m_dAvFitAdj  = 0;

  //purge the species
  vector<CSpecies>::iterator curSp = m_vecSpecies.begin();

  while (curSp != m_vecSpecies.end())
  {
    curSp->Purge();

    //kill off species if not improving and if not the species which contains 
    //the best genome found so far
    if ( (curSp->GensNoImprovement() > CParams::iNumGensAllowedNoImprovement) &&
         (curSp->BestFitness() < m_dBestEverFitness) )
    {
     curSp = m_vecSpecies.erase(curSp);
     --curSp;
    }

    ++curSp;
  }

  //we can also delete the phenotypes
  for (int gen=0; gen<m_vecGenomes.size(); ++gen)
  {
    m_vecGenomes[gen].DeletePhenotype();
  }
}

//------------------------------- Split ----------------------------------
//
//  this function is used to create a lookup table that is used to
//  calculate the depth of the network. 
//------------------------------------------------------------------------
vector<SplitDepth> Cga::Split(double low, double high, int depth)
{
  static vector<SplitDepth> vecSplits;

  double span = high-low;

  vecSplits.push_back(SplitDepth(low + span/2, depth+1));

  if (depth > 6)
  {
    return vecSplits;
  }

  else
  {
    Split(low, low+span/2, depth+1);
    Split(low+span/2, high, depth+1);

    return vecSplits;
  }
}

//--------------------------- RenderSpeciesInfo --------------------------
//
//  does what it says on the tin 
//------------------------------------------------------------------------
void Cga::RenderSpeciesInfo(HDC &surface, RECT db)
{
  if (m_vecSpecies.size() < 1) return;
  
  int numColours = 255/m_vecSpecies.size();

  double SlicePerSweeper = (double)(db.right-db.left)/(double)(CParams::iNumSweepers-1);

  double left = db.left;

  //now draw a different colored rectangle for each species
  for (int spc=0; spc<m_vecSpecies.size(); ++spc)
  {

     //choose a brush to draw with
     HBRUSH PieBrush = CreateSolidBrush(RGB(numColours*spc, 255, 255 - numColours*spc));

     HBRUSH OldBrush = (HBRUSH)SelectObject(surface, PieBrush);
     
     if (spc == m_vecSpecies.size()-1)
     {
       Rectangle(surface, 
                  left,
                  db.top,
                  db.right,
                  db.bottom);
     }

     else
     {
       Rectangle(surface, 
                  left,
                  db.top,
                  left+SlicePerSweeper*m_vecSpecies[spc].NumMembers(),
                  db.bottom);
     }

     left += SlicePerSweeper * m_vecSpecies[spc].NumMembers();

     SelectObject(surface, OldBrush);
     DeleteObject(PieBrush);

     //display best performing species stats in the same color as displayed
     //in the distribution bar
     if ( m_vecSpecies[spc].BestFitness() == m_dBestEverFitness)
     {
       string s = "Best Species ID: " + itos(m_vecSpecies[spc].ID());
       TextOut(surface, 5, db.top - 80, s.c_str(), s.size());
       
       s = "Species Age: " + itos(m_vecSpecies[spc].Age());          
       TextOut(surface, 5, db.top - 60, s.c_str(), s.size());

       s = "Gens no improvement: " + itos(m_vecSpecies[spc].GensNoImprovement());
       TextOut(surface, 5, db.top - 40, s.c_str(), s.size());
     }
  }
  
  string s = "Species Distribution Bar";
	TextOut(surface, 5, db.top - 20, s.c_str(), s.size());
}

