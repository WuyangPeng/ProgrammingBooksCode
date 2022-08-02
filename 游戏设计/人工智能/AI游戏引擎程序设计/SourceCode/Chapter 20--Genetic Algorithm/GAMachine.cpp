#include "GAMachine.h"
#include "GAAIControl.h"
#include "GameSession.h"
#include "utility.h"
#include <algorithm>

//---------------------------------------------------------
void GAMachine::Init()
{
    m_mutationRate    = 0.001f;
    m_crossoverRate   = 0.70f;
    m_offsetSize      = 1.0f;
    m_generation      = 0;
    m_bestFitness     = 0.0f;
    m_totalFitness    = 0.0f;
    
}

//---------------------------------------------------------
void GAMachine::ApplyBehaviorRule(int index)
{
    if(index < 0 || index > POPULATION_SIZE)
        return;
    
    Ship* ship = (Ship*)Game.m_ships[index];
    
    //not going to collide, just idle...
    if(m_parent->m_currentEvasionSituation == -1)
    {
        ship->ThrustOff();
        ship->StopTurn();
        return;
    }
    
    //thrust
    int thrustTp = m_genomes[index].m_genes[m_parent->m_currentEvasionSituation].m_thrust;
    ship->StopTurn();
    if(thrustTp == Gene::THRUST_FORWARD)
        ship->ThrustOn();
    else if(thrustTp == Gene::THRUST_REVERSE)
        ship->ThrustReverse();
    else
        ship->ThrustOff();
    
    //turn
    //-10 puts you in the middle of the sector
    float newDir = m_genomes[index].m_genes[m_parent->m_currentEvasionSituation].m_sector*20 -10;
    float angDelta = CLAMPDIR180(ship->m_angle - newDir);
    if(fabsf(angDelta)<=90)
    {
        if(angDelta >0)
            ship->TurnRight();
        else
            ship->TurnLeft();
    }
    else
    {
        if(angDelta<0)
            ship->TurnRight();
        else
            ship->TurnLeft();
    }
}

//---------------------------------------------------------
void GAMachine::UpdateFitness(int index)
{
    Ship* ship = (Ship*)Game.m_ships[index];
    if(ship && ship->m_active)
    {
        //if I'm currently surviving a collision situation, incr fitness
        if(m_parent->m_currentEvasionSituation != -1)
            m_genomes[index].m_fitness++;
    }
}

//---------------------------------------------------------
void GAMachine::Update(float dt)
{
    //find best out of 5000 tries, then start over
    if(m_generation > NUM_MAX_GENERATIONS)
    {
        WriteSolution();
        //reset
        CreateStartPopulation();
        Reset();
    }
    
    m_liveCount = 0;
    for (int shpNum=0; shpNum<POPULATION_SIZE; ++shpNum)
    {
        if(!Game.m_ships[shpNum]->m_active)
            continue;
        m_liveCount++;
        m_parent->UpdatePerceptions(dt,shpNum);
        ApplyBehaviorRule(shpNum);
        UpdateFitness(shpNum);
    }
    
    //if the generation is over...
    if(!m_liveCount)
        SetupNextGeneration();
    
    static char buffer[30];
    sprintf(buffer,"G: %d    Best Fitness %3.2f",m_generation,m_bestFitness);
    m_parent->m_debugTxt = buffer;
}

//---------------------------------------------------------
void GAMachine::SetupNextGeneration()
{
    //next Generation 
    vector<Genome> offspring;
    
    //sort the population (for scaling and elitism)
    sort(m_genomes.begin(), m_genomes.end());
    m_rankIndexLast = POPULATION_SIZE-1;

    //statistics
    m_totalFitness = 0.0f;
    for (int i=0; i<POPULATION_SIZE; ++i)
        m_totalFitness  += m_genomes[i].m_fitness;      
    m_bestFitness   = m_genomes[POPULATION_SIZE - 1].m_fitness;

    CopyEliteInto(offspring);
    
    while (offspring.size() < POPULATION_SIZE)
    {
        //selection operator
        Genome parent1 = SelectRouletteWheel();
        Genome parent2 = SelectRouletteWheel();
        
        //crossover operator
        Genome offspring1, offspring2;
        CrossSinglePoint(parent1.m_genes,
            parent2.m_genes,
            offspring1.m_genes,
            offspring2.m_genes);
        
        //mutation operator
        MutateOffset(offspring1.m_genes);
        MutateOffset(offspring2.m_genes);
        
        //add to new population
        offspring.push_back(offspring1);
        offspring.push_back(offspring2);
    }
    
    //replace old generation with new
    m_genomes = offspring;

    for(i = 0;i<POPULATION_SIZE;i++)
        m_genomes[i].m_fitness = 0.0f;
    
    ++m_generation;
    
    //reactivate the ships
    for (int shpNum=0; shpNum<POPULATION_SIZE; ++shpNum)
    {
        //reset test ships to startup state
        Ship* ship = (Ship*)Game.m_ships[shpNum];
        ship->m_active = true;
        ship->m_velocity.x() = 0;
        ship->m_velocity.y() = 0;
        ship->m_velocity.z() = 0;
        ship->MakeInvincible(3.0f);
    }
}

//-----------------------------------------------------------------------
void GAMachine::CreateStartPopulation()
{
    m_genomes.clear();
    
    //create random initial generation
    for (int i=0; i<POPULATION_SIZE; i++)
        m_genomes.push_back(Genome(GENOME_SIZE));
    
    //reset all variables
    Init();
}

//--------------------------------------------------------------------
#define NUM_ELITE             4
#define NUM_COPIES_ELITE      2
void GAMachine::CopyEliteInto(vector<Genome>&destination)
{
    int numberOfElite = NUM_ELITE;
    //copy the elite over to the supplied destination
    for (int i=numberOfElite; i>0; --i)
    {
        for(int j=0;j<NUM_COPIES_ELITE;++j)
            destination.push_back(m_genomes[(POPULATION_SIZE - 1) - numberOfElite]);
    }
}

//------------------------------------------------------------------
Genome& GAMachine::SelectRouletteWheel()
{
    float wedge = randflt() * m_totalFitness;
    float total = 0.0f;
    
    for (int i=0; i<POPULATION_SIZE; ++i)
    {
        total += m_genomes[i].m_fitness;
        if (total > wedge)
            return m_genomes[i];
    }
    return m_genomes[0];
}

//------------------------------------------------------------------
#define NUM_TO_TOURNEY   8
Genome& GAMachine::SelectTournament()
{
    int bestGenome    = 0;
    float bestFitness = 0.0f;
    
    for (int i=0; i<NUM_TO_TOURNEY; ++i)
    {
        int tourneyMember = randint(0,POPULATION_SIZE-1);
        if (m_genomes[i].m_fitness > bestFitness)
        {
            bestFitness = m_genomes[i].m_fitness;
            bestGenome  = i;
        }
    }
    return m_genomes[bestGenome];
}

//------------------------------------------------------------------
Genome& GAMachine::SelectRank()
{
    //list is already sorted, and m_rankIndexLast is set to the 
    //best guy after the sort, note that this function doesn't bounds check
    return m_genomes[m_rankIndexLast--];
}

//-------------------------------------------------------------------------
void GAMachine::CrossUniform( const vector<Gene> &parent1,const vector<Gene> &parent2,
                                vector<Gene>&offspring1,vector<Gene>&offspring2)
{
    if ( (randflt() > m_crossoverRate) || (parent1 == parent2)) 
    {
        offspring1 = parent1;
        offspring2 = parent2;
        return;
    }
    
    for (int gene=0; gene<GENOME_SIZE; ++gene)
    {
        if (randflt() < m_crossoverRate)
        {
            //switch the genes at this point
            offspring1.push_back(parent2[gene]);
            offspring2.push_back(parent1[gene]);
            
        }
        else
        {
            //just copy into offspring 
            offspring1.push_back(parent1[gene]);
            offspring2.push_back(parent2[gene]);
        }
    }
}

//-------------------------------------------------------------------------
void GAMachine::CrossSinglePoint(const vector<Gene> &parent1,const vector<Gene> &parent2,
                                   vector<Gene>&offspring1,vector<Gene>&offspring2)
{
    if ( (randflt() > m_crossoverRate) || (parent1 == parent2)) 
    {
        offspring1 = parent1;
        offspring2 = parent2;
        return;
    }
    
    //determine a crossover point
    int crossPoint = (int)(randflt()*GENOME_SIZE-1);
    
    for (int gene=0; gene<GENOME_SIZE; ++gene)
    {
        if (gene > crossPoint)
        {
            //just copy into offspring 
            offspring1.push_back(parent1[gene]);
            offspring2.push_back(parent2[gene]);
            
        }
        else
        {
            //switch the genes at this point
            offspring1.push_back(parent2[gene]);
            offspring2.push_back(parent1[gene]);
        }
    }
}

//-------------------------------------------------------------------------
void GAMachine::CrossMultiPoint(const vector<Gene> &parent1,const vector<Gene> &parent2,
                                  vector<Gene>&offspring1,vector<Gene>&offspring2)
{
    if ( (randflt() > m_crossoverRate) || (parent1 == parent2)) 
    {
        offspring1 = parent1;
        offspring2 = parent2;
        return;
    }
    
    //determine crossover interval points
    int crossPoint1 = randint(0,GENOME_SIZE-2);
    int crossPoint2 = randint(crossPoint1,GENOME_SIZE-1);
    
    for (int gene=0; gene<GENOME_SIZE; ++gene)
    {
        if (gene < crossPoint1 || gene>crossPoint2)
        {
            //just copy into offspring 
            offspring1.push_back(parent1[gene]);
            offspring2.push_back(parent2[gene]);
            
        }
        else
        {
            //switch the genes at this point
            offspring1.push_back(parent2[gene]);
            offspring2.push_back(parent1[gene]);
        }
    }
}

//-------------------------------------------------------------------------
void GAMachine::CrossPMX(const vector<Gene> &parent1,const vector<Gene> &parent2,
                                  vector<Gene>&offspring1,vector<Gene>&offspring2)
{
    if ( (randflt() > m_crossoverRate) || (parent1 == parent2)) 
    {
        offspring1 = parent1;
        offspring2 = parent2;
        return;
    }
    
    //determine crossover interval points
    int crossPoint1 = randint(0,GENOME_SIZE-2);
    int crossPoint2 = randint(crossPoint1,GENOME_SIZE-1);
    
    //do a straight copy
    offspring1 = parent1;
    offspring2 = parent2;
    //then swap over the mapped interval
    for (int gene=crossPoint1; gene<crossPoint2+1; ++gene)
    {
        Gene swapGene1 = parent1[gene];
        Gene swapGene2 = parent2[gene];
        
        if (swapGene1 != swapGene2)
        {
            //swap positions in both offspring
            Gene index1 = *find(offspring1.begin(),offspring1.end(),swapGene1);
            Gene index2 = *find(offspring1.begin(),offspring1.end(),swapGene2);
            swap(index1,index2);
            
            index1 = *find(offspring2.begin(),offspring2.end(),swapGene1);
            index2 = *find(offspring2.begin(),offspring2.end(),swapGene2);
            swap(index1,index2);
        }
    }
}

//-------------------------------------------------------------------------
void GAMachine::CrossOrderBased(const vector<Gene> &parent1,const vector<Gene> &parent2,
                                  vector<Gene>&offspring1,vector<Gene>&offspring2)
{
    if ( (randflt() > m_crossoverRate) || (parent1 == parent2)) 
    {
        offspring1 = parent1;
        offspring2 = parent2;
        return;
    }
    
    //vector to save the genes already used
    vector<Gene> usedGenes;
    vector<int>  usedGenesPositions;
    
    //do a straight copy
    offspring1 = parent1;
    offspring2 = parent2;

    //find a number of random genes within parent 1, and record
    //both the position, and the gene itself
    int position = randint(0,GENOME_SIZE-2);
    while(position< GENOME_SIZE)
    {
        usedGenesPositions.push_back(position);
        usedGenes.push_back(parent1[position]);
        position += randint(1,GENOME_SIZE-position);
    }

    int genePosition = 0;
    for(int i=0;i<GENOME_SIZE;++i)
    {
        for(int j=0;j<usedGenes.size();++j)
        {
            if(offspring2[i] == usedGenes[j])
            {
                offspring2[i] = usedGenes[genePosition++];
                break;
            }
        }
    }
    
    //and now do the same for the other offspring
    usedGenes.clear();
    genePosition = 0;
    for (i=0;i<usedGenesPositions.size();++i)
        usedGenes.push_back(parent2[i]);
    
    for(i=0;i<GENOME_SIZE;++i)
    {
        for(int j=0;j<usedGenes.size();++j)
        {
            if(offspring1[i] == usedGenes[j])
            {
                offspring1[i] = usedGenes[genePosition++];
                break;
            }
        }
    }
}

//-------------------------------------------------------------------------
void GAMachine::CrossPositionBased(const vector<Gene> &parent1,const vector<Gene> &parent2,
                                     vector<Gene>&offspring1,vector<Gene>&offspring2)
{
    if ( (randflt() > m_crossoverRate) || (parent1 == parent2)) 
    {
        offspring1 = parent1;
        offspring2 = parent2;
        return;
    }
    
    int off1PosFilled = 0;
    int off2PosFilled = 0;
    vector<int> genePositions;
    //find a number of random genes positions, these will
    //be the slots that will be position static
    int randGenePos = randint(0,GENOME_SIZE-2);
    while(randGenePos < GENOME_SIZE)
    {
        genePositions.push_back(randGenePos);
        randGenePos += randint(1,GENOME_SIZE-randGenePos);
    }
    //copy over the genes in the position static slots
    for (int i=0; i<genePositions.size(); ++i)
    {
        offspring1[genePositions[i]] = parent1[genePositions[i]];
        offspring2[genePositions[i]] = parent2[genePositions[i]];
    }
    //now, fill in the non-static slots
    int openSlot = 0;
    for(i=0;i<GENOME_SIZE;++i)
    {
        //find next open slot
        bool found = false;
        do
        {
            vector<int>::iterator iIter = find(genePositions.begin(),genePositions.end(),openSlot);
            if(iIter != genePositions.end())
                found = true;
            else
                ++openSlot;
        }while(!found);
        //put the gene into the offspring if it's not already there
        vector<Gene>::iterator gIter = find(offspring1.begin(),offspring1.end(),parent2[i]);
        if(gIter != offspring1.end())
            offspring1[openSlot] = parent2[i];
        gIter = find(offspring2.begin(),offspring2.end(),parent1[i]);
        if(gIter != offspring2.end())
            offspring2[openSlot] = parent1[i];
    }
}

//--------------------------------------------------------------------
void GAMachine::MutateOffset(vector<Gene> &genes)
{
    
    for (int gene=0; gene<genes.size(); ++gene)
    {
        //check for thrust mutation
        if (randflt() < m_mutationRate)
        {
            genes[gene].m_thrust += (randint(0,1)? -m_offsetSize: m_offsetSize);
            //bounds check
            if(genes[gene].m_thrust > NUM_THRUST_STATES)
                genes[gene].m_thrust = 0;
            if(genes[gene].m_thrust < 0)
                genes[gene].m_thrust = NUM_THRUST_STATES;
        }
        
        //check for angle mutation
        if (randflt() < m_mutationRate)
        {
            genes[gene].m_sector += (randint(0,1)? -m_offsetSize: m_offsetSize);
            //bounds check
            if(genes[gene].m_sector > NUM_SECTORS)
                genes[gene].m_sector = 0;
            if(genes[gene].m_sector < 0)
                genes[gene].m_sector = NUM_SECTORS;
        }
        
    }
}

//---------------------------------------------------------
void GAMachine::MutateExchange(vector<Gene> &genes)
{
    if (randflt() > m_mutationRate) 
        return;
    
    //choose two non-identical genes
    int pos1 = randint(0, GENOME_SIZE-1);
    int pos2;
    do
    {
        pos2 = randint(0, GENOME_SIZE-1);
    }while(pos2 == pos1);
    //swap their positions
    swap(genes[pos1], genes[pos2]);
}

//---------------------------------------------------------
void GAMachine::MutateDisplacement(vector<Gene> &genes)
{
    if (randflt() > m_mutationRate) 
        return;
    
    //determine crossover interval points
    int index = randint(0,GENOME_SIZE-2);
    vector<Gene>::iterator crossPoint1 = genes.begin() + index;
    vector<Gene>::iterator crossPoint2 = crossPoint1 + randint(0,GENOME_SIZE-1-index);
    
    //save the interval
    vector<Gene> temp;
    temp.assign(crossPoint1,crossPoint2);
    //remove interval from genes, and reinsert at random point
    genes.erase(crossPoint1,crossPoint2);
    vector<Gene>::iterator insertPoint = genes.begin() + randint(0,GENOME_SIZE-1);
    genes.insert(insertPoint,temp.begin(),temp.end());
}

//---------------------------------------------------------
void GAMachine::MutateInsertion(vector<Gene> &genes)
{
    if (randflt() > m_mutationRate) 
        return;
    
    //determine a gene to mutate
    int index = randint(0,GENOME_SIZE-1);
    vector<Gene>::iterator mutateGene = genes.begin() + index;
    //remove gene from list, and reinsert at random point
    genes.erase(mutateGene);
    vector<Gene>::iterator insertPoint = genes.begin() + randint(0,GENOME_SIZE-1);
    genes.insert(insertPoint,*mutateGene);
}

//---------------------------------------------------------
bool GAMachine::WriteSolution()
{
    FILE* pFile;
    char* fileNameStr = "solution.txt";
    if ((pFile = fopen(fileNameStr,"w")) == NULL)
    {
        return false;
    }
    
    //sort the genomes (to single out the best guy)
    sort(m_genomes.begin(), m_genomes.end());
    
    for(int i = 0;i<GENOME_SIZE;++i)
    {
        fwrite(&m_genomes[GENOME_SIZE-1].m_genes[i].m_thrust, sizeof(char), 1, pFile);
        fwrite(&m_genomes[GENOME_SIZE-1].m_genes[i].m_sector, sizeof(char), 1, pFile);
    }
    fclose(pFile);
    return true;
}

//---------------------------------------------------------
bool GAMachine::ReadSolution()
{
    FILE* pFile;
    char* fileNameStr = "solution.txt";
    if ((pFile = fopen(fileNameStr,"r")) == NULL)
    {
        return false;
    }
    
    for(int i = 0;i<GENOME_SIZE;++i)
    {
        fread(&m_bestGenome.m_genes[i].m_thrust, sizeof(char), 1, pFile);
        fread(&m_bestGenome.m_genes[i].m_sector, sizeof(char), 1, pFile);
    }
    fclose(pFile);
    return true;
}

//---------------------------------------------------------
void GAMachine::Reset()
{
    Init();
    for (int shpNum=0; shpNum<POPULATION_SIZE; ++shpNum)
    {
        //reset test ships to startup state
        Ship* ship = (Ship*)Game.m_ships[shpNum];
        ship->m_active = true;
        ship->m_velocity.x() = 0;
        ship->m_velocity.y() = 0;
        ship->m_velocity.z() = 0;
        ship->MakeInvincible(3.0f);
    }
    CreateStartPopulation();
}