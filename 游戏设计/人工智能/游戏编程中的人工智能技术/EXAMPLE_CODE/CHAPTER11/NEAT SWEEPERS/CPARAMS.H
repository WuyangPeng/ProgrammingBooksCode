#ifndef CPARAMS_H
#define CPARAMS_H
//------------------------------------------------------------------------
//
//	Name: CParams.h
//
//  Author: Mat Buckland 2002
//
//  Desc: class to hold all the parameters used in this project. The values
//        are loaded in from an ini file when an instance of the class is
//        created.
//       
//
//------------------------------------------------------------------------
#include <windows.h>
#include <fstream>

using namespace std;	



class CParams
{

public:

  //-------------------------------------------------------------------
  //  general parameters
  //-------------------------------------------------------------------

  static double dPi;
  static double dHalfPi;
  static double dTwoPi;

  static int    WindowWidth;
  static int    WindowHeight;

  static int    InfoWindowWidth;
  static int    InfoWindowHeight;

  static int    iFramesPerSecond;


  //-------------------------------------------------------------------
  //  used to define the sweepers
  //-------------------------------------------------------------------

  static int    iNumSweepers;
  
  //limits how fast the sweepers can turn
  static double dMaxTurnRate;

  //for controlling the size
  static int   iSweeperScale;

  //amount of sensors
  static int    iNumSensors;

  //range of sensors
  static double dSensorRange;

  //distance 0 < d < 1 for collision detection. The smaller the 
  //value is the closer the sweeper has to be to an object.
  static double dCollisionDist;


  //--------------------------------------controller parameters

  //number of time steps we allow for each generation to live
  static int    iNumTicks;

  //---------------------------------------------------------------------
  //  used in CMapper.h/cpp
  //---------------------------------------------------------------------

  static double dCellSize; 


  //----------------------------------------------------------------------
  // used in phenotype.h/cpp
  //----------------------------------------------------------------------

  static int    iNumInputs;
  static int    iNumOutputs;

  //bias value
  static double dBias;
  
  //starting value for the sigmoid response
  static double dSigmoidResponse;

  //----------------------------------------------------------------------
  // used in genotype.h/cpp
  //----------------------------------------------------------------------
  
  //number of times we try to find 2 unlinked nodes when adding a link.
  //see CGenome::AddLink()
  static int    iNumAddLinkAttempts;

  //number of attempts made to choose a node that is not an input 
  //node and that does not already have a recurrently looped connection 
  //to itself. See CGenome::AddLink()
  static int    iNumTrysToFindLoopedLink;

  //the number of attempts made to find an old link to prevent chaining
  //in CGenome::AddNeuron
  static int    iNumTrysToFindOldLink;

  //the chance, each epoch, that a neuron or link will be added to the
  //genome
  static double dChanceAddLink;
  static double dChanceAddNode;
  static double dChanceAddRecurrentLink;

  //mutation probabilities for mutating the weights in CGenome::Mutate()
  static double dMutationRate;
  static double dMaxWeightPerturbation;
  static double dProbabilityWeightReplaced;

  //probabilities for mutating the activation response
  static double dActivationMutationRate;
  static double dMaxActivationPerturbation;

  //the smaller the number the more species will be created
  static double dCompatibilityThreshold;



  //----------------------------------------------------------------------
  // used in CSpecies.h/cpp
  //----------------------------------------------------------------------

  //during fitness adjustment this is how much the fitnesses of 
  //young species are boosted (eg 1.2 is a 20% boost)
  static double dYoungFitnessBonus;

  //if the species are below this age their fitnesses are boosted
  static int    iYoungBonusAgeThreshhold;

  //number of population to survive each epoch. (0.2 = 20%)
  static double dSurvivalRate;

  //if the species is above this age their fitness gets penalized
  static int    iOldAgeThreshold;

  //by this much
  static double dOldAgePenalty;


  
  //----------------------------------------------------------------------
  // used in Cga.h/cpp
  //----------------------------------------------------------------------

  //how long we allow a species to exist without any improvement
  static int    iNumGensAllowedNoImprovement;

  //maximum number of neurons permitted in the network
  static int    iMaxPermittedNeurons;

  //the number of best performing sweepers shown when 'B' is 
  //selected. (you will see copies from the previous generation
  static int    iNumBestSweepers;

  static double dCrossoverRate;


  //---------------------------------------------

  //ctor
  CParams(){}

  bool Initialize()
  {
    if(!LoadInParameters("params.ini"))
    {
      MessageBox(NULL, "Cannot find 'params.ini'", "Error", 0);

      return false;
    }

    dPi     = 3.14159265358979;
    dHalfPi = dPi / 2;
    dTwoPi  = dPi * 2;

    dCollisionDist = (double)(iSweeperScale+1)/dSensorRange;

    iNumInputs  = (iNumSensors * 2) + 1;
    iNumOutputs = 2;

    return true;

  }

  bool LoadInParameters(char* szFileName);
};






#endif