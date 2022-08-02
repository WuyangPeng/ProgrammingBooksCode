#ifndef DATA_H
#define DATA_H

//turn off the warnings for the STL
#pragma warning (disable : 4786)

//------------------------------------------------------------------------
//
//	Name: CData.h
//
//  Author: Mat Buckland 2002
//
//  Desc: class to manipulate the gesture data for the RecognizeIt mouse
//        gesture recognition code project
//-------------------------------------------------------------------------

#include <vector>
#include <iomanip>
#include <windows.h>

#include "defines.h"
#include "utils.h"

using namespace std;



//------------------------------------------------------------------------
//
//  class to handle the training data
//------------------------------------------------------------------------
class CData
{
private:

  //these will contain the training set when created.
  vector<vector<double> > m_SetIn;
  vector<vector<double> > m_SetOut;

  //the names of the gestures
  vector<string>          m_vecNames;

  //the vectors which make up the gestures
  vector<vector<double> > m_vecPatterns;

  //number of patterns loaded into database
  int            m_iNumPatterns;

  //size of the pattern vector
  int            m_iVectorSize;

  //adds the predefined patterns and names to m_vecNames
  //and m_vecPatterns
  void           Init();


public:
  
  CData(int NumStartPatterns,
        int VectorSize)    :m_iNumPatterns(NumStartPatterns),
                            m_iVectorSize(VectorSize)
                            
  {
    Init();
    
    CreateTrainingSetFromData();
  }

  //returns the name of the pattern at val
  string  PatternName(int val);

  //this adds a new pattern and pattern name to the training data.
  //In addition, the function automatically adds the correct amount
  // of dirty versions of the pattern
  bool    AddData(vector<double> &data, string NewName);

  //this function creates a training set from the data defined as
  //constants in CData.h. From each pattern several additional patterns
  //are formed by adding random noise
  void CreateTrainingSetFromData();

  vector<vector<double> > GetInputSet() {return m_SetIn;}
  vector<vector<double> > GetOutputSet(){return m_SetOut;}

};

#endif
