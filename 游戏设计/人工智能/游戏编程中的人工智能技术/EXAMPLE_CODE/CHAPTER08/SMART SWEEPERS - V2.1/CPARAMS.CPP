#include "CParams.h"


double CParams::dPi                 = 0;
double CParams::dHalfPi             = 0;
double CParams::dTwoPi              = 0;
int CParams::WindowWidth            = 400;
int CParams::WindowHeight           = 400;
int CParams::iFramesPerSecond       = 0;
int CParams::iNumInputs             = 0;
int CParams::iNumHidden             = 0;
int CParams::iNeuronsPerHiddenLayer = 0;
int CParams::iNumOutputs            = 0;
double CParams::dActivationResponse = 0;
double CParams::dBias               = -1;
double CParams::dMaxTurnRate        = 0;
double CParams::dMaxSpeed           = 0;
int CParams::iSweeperScale          = 0;
int CParams::iNumSensors            = 0;
double CParams::dSensorRange        = 0;
int CParams::iNumSweepers           = 0;
int CParams::iNumTicks              = 0;
double CParams::dMineScale          = 0;
double CParams::dCrossoverRate      = 0;
double CParams::dMutationRate       = 0;
double CParams::dMaxPerturbation    = 0;
int CParams::iNumElite              = 0;
int CParams::iNumCopiesElite        = 0;
double CParams::dCollisionDist      = 0;



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
  grab >> iNumInputs;
  grab >> ParamDescription;
  grab >> iNumHidden;
  grab >> ParamDescription;
  grab >> iNeuronsPerHiddenLayer;
  grab >> ParamDescription;
  grab >> iNumOutputs;
  grab >> ParamDescription;
  grab >> dActivationResponse;
  grab >> ParamDescription;
  grab >> dMaxTurnRate;
  grab >> ParamDescription;
  grab >> dMaxSpeed;
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
  grab >> dMineScale;
  grab >> ParamDescription;
  grab >> dCrossoverRate;
  grab >> ParamDescription;
  grab >> dMutationRate;
  grab >> ParamDescription;
  grab >> dMaxPerturbation;
  grab >> ParamDescription;
  grab >> iNumElite;
  grab >> ParamDescription;
  grab >> iNumCopiesElite;
 



  return true;
}
 




  
  
