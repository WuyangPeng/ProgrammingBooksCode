#pragma once

#pragma warning(disable: 4786)
#include "Genome.h"

class GAAIControl;

#define POPULATION_SIZE      50
#define TIME_PER_GENERATION  60.0f
#define GENOME_SIZE         520
#define NUM_MAX_GENERATIONS 5000


class GAMachine
{
public:
    GAMachine(GAAIControl* parent):m_parent(parent){}
    void SetupNextGeneration();
    void CreateStartPopulation();
    void Update(float dt);
    void UpdateFitness(int index);
    void Init();
    void Reset();
    void ApplyBehaviorRule(int index);
    bool WriteSolution();
    bool ReadSolution();
    
    //selection operators    
    Genome& SelectRouletteWheel();
    Genome& SelectTournament();
    Genome& SelectRank();
    
    //crossover operators
    void CrossUniform( const vector<Gene> &parent1,const vector<Gene> &parent2,
        vector<Gene>&offspring1,vector<Gene>&offspring2);
    void CrossSinglePoint(const vector<Gene> &parent1,const vector<Gene> &parent2,
        vector<Gene>&offspring1,vector<Gene>&offspring2);
    void CrossMultiPoint(const vector<Gene> &parent1,const vector<Gene> &parent2,
        vector<Gene>&offspring1,vector<Gene>&offspring2);
    //crossover operators -- order based genes
    void CrossPMX(const vector<Gene> &parent1,const vector<Gene> &parent2,
        vector<Gene>&offspring1,vector<Gene>&offspring2);
    void CrossOrderBased(const vector<Gene> &parent1,const vector<Gene> &parent2,
        vector<Gene>&offspring1,vector<Gene>&offspring2);;
    void CrossPositionBased(const vector<Gene> &parent1,const vector<Gene> &parent2,
        vector<Gene>&offspring1,vector<Gene>&offspring2);
    
    //mutation operators
    void MutateOffset(vector<Gene> &genes);
    //mutation operators -- order based genes
    void MutateExchange(vector<Gene> &genes);
    void MutateDisplacement(vector<Gene> &genes);
    void MutateInsertion(vector<Gene> &genes);
    
    //elitism
    void CopyEliteInto(vector<Genome>&destination);
    
protected:
    GAAIControl*    m_parent;
    //genetic data
    vector<Genome>  m_genomes;
    int             m_rankIndexLast;
    Genome          m_bestGenome;
    int             m_generation;
    float           m_crossoverRate;
    float           m_mutationRate;
    float           m_offsetSize;
    float           m_bestFitness;
    float           m_totalFitness;
    int             m_liveCount;
};
