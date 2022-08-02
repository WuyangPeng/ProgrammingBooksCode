#include "CSpecies.h"


//------------------------------------------------------------------------
//
//  this ctor creates an instance of a new species. A local copy of 
//  the initializing genome is kept in m_Leader and the first element
//  of m_vecMembers is a pointer to that genome.
//------------------------------------------------------------------------
CSpecies::CSpecies(CGenome  &FirstOrg,
                   int      SpeciesID):m_iSpeciesID(SpeciesID),
                                       m_dBestFitness(FirstOrg.Fitness()),
                                       m_iGensNoImprovement(0),
                                       m_iAge(0),
                                       m_Leader(FirstOrg),
                                       m_dSpawnsRqd(0)
                                     
{
  m_vecMembers.push_back(&FirstOrg);
  
  m_Leader = FirstOrg;
}

//------------------------ AddMember -------------------------------------
//
//  this function adds a new member to this species and updates the member
//  variables accordingly
//------------------------------------------------------------------------
void CSpecies::AddMember(CGenome &NewMember)
{
 
   //is the new member's fitness better than the best fitness?
  if (NewMember.Fitness() > m_dBestFitness)
  {
    m_dBestFitness = NewMember.Fitness();

    m_iGensNoImprovement = 0;

    m_Leader = NewMember;
  }


  m_vecMembers.push_back(&NewMember);

}

//-------------------------- Purge ---------------------------------------
//
//  this functions clears out all the members from the last generation,
//  updates the age and gens no improvement.
//------------------------------------------------------------------------
void CSpecies::Purge()
{
  m_vecMembers.clear();

  //update age etc
  ++m_iAge;

  ++m_iGensNoImprovement;

  m_dSpawnsRqd = 0;
}

//--------------------------- AdjustFitness ------------------------------
//
//  This function adjusts the fitness of each individual by first
//  examining the species age and penalising if old, boosting if young.
//  Then we perform fitness sharing by dividing the fitness by the number
//  of individuals in the species. This ensures a species does not grow 
//  too large
//------------------------------------------------------------------------
void CSpecies::AdjustFitnesses()
{
  double total = 0;

  for (int gen=0; gen<m_vecMembers.size(); ++gen)
  {
    double fitness = m_vecMembers[gen]->Fitness();

    //boost the fitness scores if the species is young
    if (m_iAge < CParams::iYoungBonusAgeThreshhold)
    {
      fitness *= CParams::dYoungFitnessBonus;
    }

    //punish older species
    if (m_iAge > CParams::iOldAgeThreshold)
    {
      fitness *= CParams::dOldAgePenalty;
    }

    total += fitness;

    //apply fitness sharing to adjusted fitnesses
    double AdjustedFitness = fitness/m_vecMembers.size();

    m_vecMembers[gen]->SetAdjFitness(AdjustedFitness);

  }
}

//------------------------ CalculateSpawnAmount --------------------------
//
//  Simply adds up the expected spawn amount for each individual in the 
//  species to calculate the amount of offspring this species should
//  spawn
//------------------------------------------------------------------------
void CSpecies::CalculateSpawnAmount()
{
  for (int gen=0; gen<m_vecMembers.size(); ++gen)
  {
    m_dSpawnsRqd += m_vecMembers[gen]->AmountToSpawn();

  }
}


//------------------------ Spawn -----------------------------------------
//
//  Returns a random genome selected from the best individuals
//------------------------------------------------------------------------
CGenome CSpecies::Spawn()
{
  CGenome baby;
  
  if (m_vecMembers.size() == 1)
  {
    baby = *m_vecMembers[0];    
  }
  
  else
  {
    int MaxIndexSize = (int) (CParams::dSurvivalRate * m_vecMembers.size())+1;

    int TheOne = RandInt(0, MaxIndexSize);

    baby = *m_vecMembers[TheOne];
  }

  return baby;
}


