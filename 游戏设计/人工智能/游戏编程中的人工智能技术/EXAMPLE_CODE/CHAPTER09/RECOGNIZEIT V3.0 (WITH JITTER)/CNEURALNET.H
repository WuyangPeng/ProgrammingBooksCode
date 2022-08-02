#ifndef CNEURALNET_H
#define CNEURALNET_H

//turn off the warnings for the STL
#pragma warning (disable : 4786)

//------------------------------------------------------------------------
//
//	Name: CNeuralNet.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Class for creating a feedforward neural net.From the book Game AI 
//  Programming with Neural Nets and Genetic Algorithms.
//-------------------------------------------------------------------------
#include <vector>
#include <fstream>
#include <math.h>
#include <windows.h>

#include "utils.h"
#include "defines.h"
#include "CData.h"


using namespace std;

//define a type for an input or output vector (used in
//the training method)
typedef vector<double> iovector;




//-------------------------------------------------------------------
//	define neuron struct
//-------------------------------------------------------------------
struct SNeuron
{
	//the number of inputs into the neuron
	int				      m_iNumInputs;

	//the weights for each input
	vector<double>	m_vecWeight;

  //the previous timesteps weight update used 
  //to add momentum
  vector<double>  m_vecPrevUpdate;

  //the activation of this neuron
  double          m_dActivation;

  //the error value
  double          m_dError;

	//ctor
	SNeuron(int NumInputs);
};


//---------------------------------------------------------------------
//	struct to hold a layer of neurons.
//---------------------------------------------------------------------

struct SNeuronLayer
{
	//the number of neurons in this layer
	int					      m_iNumNeurons;

	//the layer of neurons
	vector<SNeuron>		m_vecNeurons;

	SNeuronLayer(int NumNeurons, 
				       int NumInputsPerNeuron);
};


//----------------------------------------------------------------------
//	neural net class
//----------------------------------------------------------------------

class CNeuralNet
{
	
private:
	
	int					m_iNumInputs;

	int					m_iNumOutputs;

	int					m_iNumHiddenLayers;

	int					m_iNeuronsPerHiddenLyr;

  //we must specify a learning rate for backprop
  double      m_dLearningRate;

  //cumulative error for the network (sum (outputs - expected))
  double      m_dErrorSum;

  //true if the network has been trained
  bool        m_bTrained;

  //epoch counter
  int         m_iNumEpochs;

	//storage for each layer of neurons including the output layer
	vector<SNeuronLayer>	m_vecLayers;

  //given a training set this method performs one iteration of the
  //backpropagation algorithm. The training sets comprise of series
  //of vector inputs and a series of expected vector outputs. Returns
  //false if there is a problem.
  bool            NetworkTrainingEpoch(vector<iovector> &SetIn,
                                       vector<iovector> &SetOut);

  void            CreateNet();

  //sets all the weights to small random values
  void            InitializeNetwork();
  
	//sigmoid response curve
	inline double	  Sigmoid(double activation, double response);


public:


  CNeuralNet::CNeuralNet(int    NumInputs,
                         int    NumOutputs,
                         int    HiddenNeurons,
                         double LearningRate);


	//calculates the outputs from a set of inputs
	vector<double>	Update(vector<double> inputs);

  //trains the network given a training set. Returns false if
  //there is an error with the data sets
  bool            Train(CData* data, HWND hwnd);

  //accessor methods
  bool            Trained()const{return m_bTrained;}
  double          Error()const  {return m_dErrorSum;}
  int             Epoch()const  {return m_iNumEpochs;}

};
				



#endif