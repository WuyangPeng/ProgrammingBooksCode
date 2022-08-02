#include "CParams.h"


double CParams::dPi                       = 0;
double CParams::dHalfPi                   = 0;
double CParams::dTwoPi                    = 0;
int CParams::WindowWidth                  = 400;
int CParams::WindowHeight                 = 400;
int CParams::iFramesPerSecond             = 0;
int CParams::iNumInputs                   = 0;
int CParams::iNumOutputs                  = 0;
double CParams::dBias                     = -1;
double CParams::dMaxTurnRate              = 0;
int CParams::iSweeperScale                = 0;
int CParams::iNumSensors                  = 0;
double CParams::dSensorRange              = 0;
int CParams::iNumSweepers                 = 0;
int CParams::iNumTicks                    = 0;
double CParams::dCollisionDist            = 0;
double CParams::dCellSize                 = 0;
double CParams::dSigmoidResponse          = 1;
int CParams::iNumAddLinkAttempts          = 0;
int CParams::iNumTrysToFindLoopedLink     = 5;
int CParams::iNumTrysToFindOldLink        = 5;
double CParams::dYoungFitnessBonus        = 0;
int CParams::iYoungBonusAgeThreshhold     = 0;
double CParams::dSurvivalRate             = 0;
int CParams::InfoWindowWidth              = 400;
int CParams::InfoWindowHeight             = 400;
int CParams::iNumGensAllowedNoImprovement = 0;
int CParams::iMaxPermittedNeurons         = 0;
double CParams::dChanceAddLink            = 0;
double CParams::dChanceAddNode            = 0;
double CParams::dChanceAddRecurrentLink   = 0;
double CParams::dMutationRate             = 0;
double CParams::dMaxWeightPerturbation    = 0;
double CParams::dProbabilityWeightReplaced= 0;

double CParams::dActivationMutationRate   = 0;
double CParams::dMaxActivationPerturbation= 0;

double CParams::dCompatibilityThreshold   = 0;
int CParams::iNumBestSweepers             = 4;
int CParams::iOldAgeThreshold             = 0;
double CParams::dOldAgePenalty            = 0;
double CParams::dCrossoverRate            = 0;


//this function loads in the parameters from a given file name. Returns
//false if there is a problem opening the file.
bool CParams::LoadInParameters(char* szFileName)
{
  ifstream grab(szFileName);

  //check file exists
  if (!grab)
  {
    return false;
  }

  //load in from the file
  char ParamDescription[40];

  grab >> ParamDescription;
  grab >> iFramesPerSecond;
  grab >> ParamDescription;
  grab >> dMaxTurnRate;
  grab >> ParamDescription;
  grab >> iSweeperScale;
  grab >> ParamDescription;
  grab >> iNumSensors;
  grab >> ParamDescription;
  grab >> dSensorRange;
  grab >> ParamDescription;
  grab >> iNumSweepers;
  grab >> ParamDescription;
  grab >> iNumTicks;
  grab >> ParamDescription;
  grab >> dCellSize;
  grab >> ParamDescription;
  grab >> iNumAddLinkAttempts;
  grab >> ParamDescription;
  grab >> dSurvivalRate;
  grab >> ParamDescription;
  grab >> iNumGensAllowedNoImprovement;
  grab >> ParamDescription;
  grab >> iMaxPermittedNeurons;
  grab >> ParamDescription;
  grab >> dChanceAddLink;
  grab >> ParamDescription;
  grab >> dChanceAddNode;
  grab >> ParamDescription;
  grab >> dChanceAddRecurrentLink;
  grab >> ParamDescription;
  grab >> dMutationRate;
  grab >> ParamDescription;
  grab >> dMaxWeightPerturbation;
  grab >> ParamDescription;
  grab >> dProbabilityWeightReplaced;
  grab >> ParamDescription;
  grab >> dActivationMutationRate;
  grab >> ParamDescription;
  grab >> dMaxActivationPerturbation;
  grab >> ParamDescription;
  grab >> dCompatibilityThreshold;
  grab >> ParamDescription;
  grab >>iOldAgeThreshold;
  grab >> ParamDescription;
  grab >>dOldAgePenalty;
  grab >> ParamDescription;
  grab >> dYoungFitnessBonus;
  grab >> ParamDescription;
  grab >> iYoungBonusAgeThreshhold;
  grab >> ParamDescription;
  grab >>dCrossoverRate;


  return true;
}
 




  
  
