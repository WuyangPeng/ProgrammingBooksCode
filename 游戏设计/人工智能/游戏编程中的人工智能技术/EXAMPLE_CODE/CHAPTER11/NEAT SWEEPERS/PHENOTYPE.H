#ifndef PHENOTYPE_H
#define PHENOTYPE_H

//-----------------------------------------------------------------------
//
//  Name: phenotype.h
//
//  Author: Mat Buckland 2002
//
//	Desc: definitions required for the creation of a neural network. To be
//        used in the implementation of Kenneth Owen Stanley's NEAT idea.
//        
//-----------------------------------------------------------------------

#include <vector>
#include <math.h>
#include <windows.h>
#include <algorithm>

#include "utils.h"
#include "CParams.h"
#include "genes.h"


using namespace std;



struct SNeuron;

//------------------------------------------------------------------------
//
//  SLink structure 
//------------------------------------------------------------------------
struct SLink
{
  //pointers to the neurons this link connects
  SNeuron*  pIn;
  SNeuron*  pOut;

  //the connection weight
  double  dWeight;

  //is this link a recurrent link?
  bool    bRecurrent;

  SLink(double dW, SNeuron* pIn, SNeuron* pOut, bool bRec):dWeight(dW),
                                                           pIn(pIn),
                                                           pOut(pOut),
                                                           bRecurrent(bRec)
  {}
};


//------------------------------------------------------------------------
//
//  SNeuron
//------------------------------------------------------------------------
struct SNeuron
{
   //all the links coming into this neuron
  vector<SLink> vecLinksIn;

  //and out
  vector<SLink> vecLinksOut;

  //sum of weights x inputs
  double        dSumActivation;

  //the output from this neuron
  double        dOutput;

  //what type of neuron is this?
  neuron_type   NeuronType;

  //its identification number
  int           iNeuronID;

  //sets the curvature of the sigmoid function
  double        dActivationResponse;

  //used in visualization of the phenotype
  int           iPosX,   iPosY;
  double        dSplitY, dSplitX;

  //--- ctors
  SNeuron(neuron_type type,
          int         id,
          double      y,
          double      x,
          double      ActResponse):NeuronType(type),
                                   iNeuronID(id),
                                   dSumActivation(0),
                                   dOutput(0),
                                   iPosX(0),
                                   iPosY(0),
                                   dSplitY(y),
                                   dSplitX(x),
                                   dActivationResponse(ActResponse)
	{}
};

//------------------------------------------------------------------------
//
// CNeuralNet
//------------------------------------------------------------------------
class CNeuralNet
{

private:
  
  vector<SNeuron*>  m_vecpNeurons;

  //the depth of the network
  int               m_iDepth;


public:
	
  
  CNeuralNet(vector<SNeuron*> neurons,
             int              depth);
								

  ~CNeuralNet();

   //you have to select one of these types when updating the network
  //If snapshot is chosen the network depth is used to completely
  //flush the inputs through the network. active just updates the
  //network each timestep
  enum run_type{snapshot, active};

  //update network for this clock cycle
  vector<double>  Update(const vector<double> &inputs, const run_type type);

  //draws a graphical representation of the network to a user speciefied window
  void            DrawNet(HDC &surface,
                          int cxLeft,
                          int cxRight,
                          int cyTop,
                          int cyBot);

};


#endif