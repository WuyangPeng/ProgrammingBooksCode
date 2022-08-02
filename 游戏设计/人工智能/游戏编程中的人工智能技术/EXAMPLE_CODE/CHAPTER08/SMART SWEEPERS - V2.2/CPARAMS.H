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
#include <fstream>
#include <windows.h>

using namespace std;	



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

  //--------------------------------------used to define the sweepers

  //limits how fast the sweepers can turn
  static double dMaxTurnRate;

  static double dMaxSpeed;

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
  static int    iNumSweepers;

  //number of time steps we allow for each generation to live
  static int    iNumTicks;

  //scaling factor for mines
  static double dMineScale;

  //---------------------------------------GA parameters
  static double dCrossoverRate;
  static double dMutationRate;

  //the maximum amount the GA may mutate each weight by
  static double dMaxPerturbation;

  //used for elitism
  static int    iNumElite;
  static int    iNumCopiesElite;

  static int    iTournamentCompetitors;

  //-------------------------------------used for the memory mapping
  static double dCellSize; 


  //ctor
  CParams()
  {
    if(!LoadInParameters("params.ini"))
    {
      MessageBox(NULL, "Cannot find ini file!", "Error", 0);
    }

    dPi     = 3.14159265358979;
    dHalfPi = dPi / 2;
    dTwoPi  = dPi * 2;

    dCollisionDist = (double)(iSweeperScale+1)/dSensorRange;

    iNumInputs = 2*iNumSensors + 1;
  }

  bool LoadInParameters(char* szFileName);


};






#endif