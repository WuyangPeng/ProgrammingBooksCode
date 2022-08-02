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
  
  //the user mouse gesture paths - raw and smoothed
  vector<POINTS> m_vecPath;
  vector<POINTS> m_vecSmoothPath;

  //the smoothed path transformed into vectors
  vector<double> m_vecVectors;

  //true if user is gesturing
  bool    m_bDrawing;

  //the highest output the net produces. This is the most
  //likely candidate for a matched gesture.
  double  m_dHighestOutput;

  //the best match for a gesture based on m_dHighestOutput
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

  //clears the mouse data vectors
  void    Clear();
  
  //given a series of points whis method creates a path of 
  //normalized vectors
  void    CreateVectors();

  //preprocesses the mouse data into a fixed number of points
  bool    Smooth();

  //tests for a match with a prelearnt gesture
  bool    TestForMatch();
  
  //dialog box procedure. A dialog box is spawned when the user
  //enters a new gesture.
  static BOOL CALLBACK DialogProc(HWND   hwnd,
                                  UINT   msg,
                                  WPARAM wParam,
                                  LPARAM lParam);

  //this temporarily holds any newly created pattern names
  static string m_sPatternName;


public:

  CController(HWND hwnd);
  
  ~CController();


  //call this to train the network using backprop with the current data
  //set
  bool TrainNetwork();

  //renders the mouse gestures and relevant data such as the number
  //of training epochs and training error
  void Render(HDC &surface, int cxClient, int cyClient);

  //returns whether or not the mouse is currently drawing
  bool Drawing()const{return m_bDrawing;}

  //this is called whenever the user depresses or releases the right
  //mouse button.
  //If val is true then the right mouse button has been depressed so all
  //mouse data is cleared ready for the next gesture. If val is false a
  //gesture has just been completed. The gesture is then either added to
  //the current data set or it is tested to see if it matches an existing
  //pattern.
  //The hInstance is required so a dialog box can be created as a child
  //window of the main app instance. The dialog box is used to grab the
  //name of any user defined gesture
  bool Drawing(bool val, HINSTANCE hInstance);

  //clears the screen and puts the app into learning mode, ready to accept
  //a user defined gesture
  void LearningMode();

  //call this to add a point to the mouse path
  void AddPoint(POINTS p)
  {
    m_vecPath.push_back(p);
  }  
};




#endif