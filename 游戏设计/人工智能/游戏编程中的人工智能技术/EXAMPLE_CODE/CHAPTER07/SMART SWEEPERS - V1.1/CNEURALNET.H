#ifndef CNEURALNET_H
#define CNEURALNET_H
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
#include <math.h>

#include "utils.h"
#include "CParams.h"

using namespace std;



//-------------------------------------------------------------------
//	define neuron struct
//-------------------------------------------------------------------
struct SNeuron
{
	//the number of inputs into the neuron
	int				      m_NumInputs;

	//the weights for each input
	vector<double>	m_vecWeight;


	//ctor
	SNeuron(int NumInputs);
};


//---------------------------------------------------------------------
//	struct to hold a layer of neurons.
//---------------------------------------------------------------------

struct SNeuronLayer
{
	//the number of neurons in this layer
	int					      m_NumNeurons;

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
	
	int					m_NumInputs;

	int					m_NumOutputs;

	int					m_NumHiddenLayers;

	int					m_NeuronsPerHiddenLyr;

	//storage for each layer of neurons including the output layer
	vector<SNeuronLayer>	m_vecLayers;

public:

	CNeuralNet();

	void			      CreateNet();

	//gets the weights from the NN
	vector<double>	GetWeights()const;

	//returns total number of weights in net
	int				      GetNumberOfWeights()const;

	//replaces the weights with new ones
	void			      PutWeights(vector<double> &weights);

	//calculates the outputs from a set of inputs
	vector<double>	Update(vector<double> &inputs);

	//sigmoid response curve
	inline double	  Sigmoid(double activation, double response);

  //calculate the points which define the individual neurons
  vector<int>     CalculateSplitPoints() const;

};
				



#endif