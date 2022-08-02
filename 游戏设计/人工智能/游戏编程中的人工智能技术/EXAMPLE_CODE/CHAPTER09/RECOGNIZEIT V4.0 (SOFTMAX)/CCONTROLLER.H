#ifndef CController_H
#define CController_H

//turn off the warnings for the STL
#pragma warning (disable : 4786)

//------------------------------------------------------------------------
//
//	Name: CController.h
//
//  Author: Mat Buckland 2002
//
//  Desc: controller class for the RecognizeIt mouse gesture recognition
//        code project
//-------------------------------------------------------------------------

#include <vector>
#include <windows.h>
#include <iomanip>
#include <math.h>

#include "SVector2D.h"
#include "defines.h"
#include "CNeuralNet.h"
#include "CData.h"


using namespace std;

//the program can be in one of three states.
enum mode{LEARNING, ACTIVE, UNREADY, TRAINING};

class CController 
{

private:

  //the neural network
  CNeuralNet*     m_pNet;

  //this class holds all the training data
  CData*          m_pData;
  
  //the user mouse paths
  vector<POINTS> m_vecPath;
  vector<POINTS> m_vecSmoothPath;

  //the smoothed path transformed into vectors
  vector<double> m_vecVectors;

  //true if user is gesturing
  bool    m_bDrawing;

  //the probability the networks guess is correct
  double  m_dMatchProbability;

  //the best match based on the probability above
  int     m_iBestMatch;

  //if the network has found a pattern this is the match
  int     m_iMatch;

  //the raw mouse data is smoothed to this number of points
  int     m_iNumSmoothPoints;

  //the number of patterns in the database;
  int     m_iNumValidPatterns;

  //the current state of the program
  mode    m_Mode;

  //local copy of the application handle
  HWND    m_hwnd;

  void    Clear();
  
  //given a series of points whis method creates a path of 
  //normalized vectors
  void    CreateVectors();

  //preprocesses the mouse data into a fixed number of points
  bool    Smooth();

  //tests for a match with a prelearnt gesture
  bool    TestForMatch();
  
  //dialog box procedure 
  static BOOL CALLBACK DialogProc(HWND   hwnd,
                                  UINT   msg,
                                  WPARAM wParam,
                                  LPARAM lParam);

  
  //this temporarily holds any newly created pattern names
  static string m_sPatternName;



public:

  CController(HWND hwnd);
  
  ~CController();


  bool TrainNetwork();

  void Render(HDC &surface, int cxClient, int cyClient);
  
  void AddPoint(POINTS p)
  {
    m_vecPath.push_back(p);
  }

  bool Drawing(){return m_bDrawing;}
  bool Drawing(bool val, HINSTANCE hInstance);

  void LearningMode();

  
};




#endif