#ifndef CPARAMS_H
#define CPARAMS_H
//------------------------------------------------------------------------
//
//	Name: CParams.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Class to hold all the parameters used in this project. The values
//        are loaded in from an ini file when an instance of the class is
//        created.
//       
//
//------------------------------------------------------------------------
#include <fstream>
#include <windows.h>

using namespace std;	

#define NUM_STARS 20

//macros for the user input
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

class CParams
{

public:

  //------------------------------------general parameters
  static double dPi;
  static double dHalfPi;
  static double dTwoPi;

  static int    WindowWidth;
  static int    WindowHeight;

  static int    iFramesPerSecond;

  
  //-------------------------------------used for the neural network
  static int    iNumInputs;
  static int    iNumHidden;
  static int    iNeuronsPerHiddenLayer;
  static int    iNumOutputs;

  //for tweeking the sigmoid function
  static double dActivationResponse;

  //bias value
  static double dBias;


  //--------------------------------------controller parameters
  static int    iPopSize;
  static int    iNumOnScreen;

  //tournament selection choses from this amount of best
  //performers
  static double dPercentageBestToSelectFrom;
 
  //the tourney is held using this amount of competitors
  static int    iNumTourneyCompetitors;

  //number of offspring spawned when program first starts
  static int    iPreSpawns;


  //---------------------------------------GA parameters
  static double dMutationRate;

  //the maximum amount the ga may mutate each weight by
  static double dMaxPerturbation;


  //---------------------------------------CBullet settings
  static double dBulletScale;

  static double dBulletSpeed;


  //---------------------------------------CGun settings
  static double dGunScale;
  static int    iMaxBullets;
  static  int   iFiringRate;
  static double dMaxTranslationPerTick;

  //---------------------------------------Alien settings
  static double dAlienScale;
  static double dMaxThrustVertical;
  static double dMaxThrustLateral;
  static double dMaxVelocity;
  static double dAlienMass;
  static double dGravityPerTick;



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

    #define GRAVITY  -1.63 

    dGravityPerTick = GRAVITY/CParams::iFramesPerSecond;

    iNumInputs = 2 + iMaxBullets*2;

    return true;
  }


  bool LoadInParameters(char* szFileName);


};






#endif