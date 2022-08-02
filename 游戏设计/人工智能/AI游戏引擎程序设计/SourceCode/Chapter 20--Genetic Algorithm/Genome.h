#pragma once

#pragma warning(disable: 4786)
#include <vector>
#include "utility.h"
#define NUM_SECTORS 18
#define NUM_THRUST_STATES 2
using namespace std;

class Gene 
{
public:
    //methods    
    Gene() {m_thrust = randint(0,2);m_sector = randint(0,NUM_SECTORS-1);}
    Gene(int a, int d):m_thrust(a), m_sector(d){}
    bool operator==(const Gene &rhs) const {return (m_thrust == rhs.m_thrust) && (m_sector == rhs.m_sector);}
    bool operator!=(const Gene &rhs) const {return (m_thrust != rhs.m_thrust) || (m_sector != rhs.m_sector);}
    
    enum
    {
        THRUST_OFF,
        THRUST_FORWARD,
        THRUST_REVERSE
    };
    
    //data
    char m_thrust;
    char m_sector;
};

class Genome
{
public:
    //methods
    Genome():m_fitness(0){}
    Genome(const int num_genes):m_fitness(0){for(int i=0;i<num_genes;++i)m_genes.push_back(Gene());}
    
    bool operator<(const Genome& rhs){return (m_fitness < rhs.m_fitness);}

    //data
    vector<Gene> m_genes;
    float        m_fitness;
};