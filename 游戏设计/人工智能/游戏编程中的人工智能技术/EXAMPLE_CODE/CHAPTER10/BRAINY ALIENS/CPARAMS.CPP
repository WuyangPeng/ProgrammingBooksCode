#include "CParams.h"


//because we will always be loading in the settings from an ini file
//we can just initialize everything to zero
double CParams::dPi                 = 0;
double CParams::dHalfPi             = 0;
double CParams::dTwoPi              = 0;
int CParams::WindowWidth            = 400;
int CParams::WindowHeight           = 400;
int CParams::iFramesPerSecond       = 0;
int CParams::iNumInputs             = 0;
int CParams::iNumHidden             = 0;
int CParams::iNeuronsPerHiddenLayer = 0;
int CParams::iNumOutputs            = 3;
double CParams::dActivationResponse = 0;
double CParams::dBias               = -1;
double CParams::dMutationRate       = 0;
double CParams::dMaxPerturbation    = 0;

int CParams::iPopSize                       = 0;
int CParams::iNumOnScreen                   = 0;
double CParams::dPercentageBestToSelectFrom = 0;
int CParams::iNumTourneyCompetitors         = 0;
int CParams::iPreSpawns                     = 0;

double CParams::dBulletSpeed        = 0;
double CParams::dBulletScale        = 0;

double CParams::dMaxTranslationPerTick = 2.5;
double CParams::dGunScale              = 6;
int CParams::iMaxBullets               = 0;
int CParams::iFiringRate               = 15;

double CParams::dMaxThrustLateral      = 30;
double CParams::dMaxThrustVertical     = 20;
double CParams::dMaxVelocity           = 2;
double CParams::dAlienMass             = 100;
double CParams::dAlienScale            = 3;
double CParams::dGravityPerTick        = 0;







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
  grab >> iNumHidden;
  grab >> ParamDescription;
  grab >> iNeuronsPerHiddenLayer;
  grab >> ParamDescription;
  grab >> dActivationResponse;
  grab >> ParamDescription;
  grab >> dMutationRate;
  grab >> ParamDescription;
  grab >> dMaxPerturbation;
  grab >> ParamDescription;
  grab >> iPopSize;
  grab >> ParamDescription;
  grab >> dPercentageBestToSelectFrom;
  grab >> ParamDescription;
  grab >> iNumOnScreen;
  grab >> ParamDescription;
  grab >> dBulletSpeed;
  grab >> ParamDescription;
  grab >> dBulletScale;
  grab >> ParamDescription;
  grab >> iMaxBullets;
  grab >> ParamDescription;
  grab >> iNumTourneyCompetitors;
  grab >> ParamDescription;
  grab >> iPreSpawns;


  return true;
}
 




  
  
