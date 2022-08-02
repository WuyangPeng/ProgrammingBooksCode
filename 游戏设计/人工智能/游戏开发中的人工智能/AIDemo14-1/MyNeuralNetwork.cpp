#include "MyNeuralNetwork.h"
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>


//---------------------------------------------------------------------------
/*
Book:           AI for Game Developers
Authors:        David M. Bourg & Glenn Seemann
Example:        Neural Networks, Chapter 14
*/
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////////////////////////
// NeuralNetworkLayer Class
/////////////////////////////////////////////////////////////////////////////////////////////////
NeuralNetworkLayer::NeuralNetworkLayer()
{
	ParentLayer = NULL;
	ChildLayer = NULL;
	LinearOutput = false;
	UseMomentum = false;
	MomentumFactor = 0.9;
}

void NeuralNetworkLayer::Initialize(int NumNodes, NeuralNetworkLayer* parent, NeuralNetworkLayer* child)
{
	int	i, j;

	// Allocate memory
	NeuronValues = (double*) malloc(sizeof(double) * NumberOfNodes);
	DesiredValues = (double*) malloc(sizeof(double) * NumberOfNodes);
	Errors = (double*) malloc(sizeof(double) * NumberOfNodes);

	if(parent != NULL)
	{		
		ParentLayer = parent;
	}

	if(child != NULL)
	{
		ChildLayer = child;

	
		Weights = (double**) malloc(sizeof(double*) * NumberOfNodes);
		WeightChanges = (double**) malloc(sizeof(double*) * NumberOfNodes);
		for(i = 0; i<NumberOfNodes; i++)
		{
			Weights[i] = (double*) malloc(sizeof(double) * NumberOfChildNodes);
			WeightChanges[i] = (double*) malloc(sizeof(double) * NumberOfChildNodes);
		}

		BiasValues = (double*) malloc(sizeof(double) * NumberOfChildNodes);
		BiasWeights = (double*) malloc(sizeof(double) * NumberOfChildNodes);
	} else {
		Weights = NULL;
		BiasValues = NULL;
		BiasWeights = NULL;
	}

	// Make sure everything contains zeros
	for(i=0; i<NumberOfNodes; i++)
	{
		NeuronValues[i] = 0;
		DesiredValues[i] = 0;
		Errors[i] = 0;
		
		if(ChildLayer != NULL)
			for(j=0; j<NumberOfChildNodes; j++)
			{
				Weights[i][j] = 0;
				WeightChanges[i][j] = 0;
			}
	}

	if(ChildLayer != NULL)
		for(j=0; j<NumberOfChildNodes; j++)
		{
			BiasValues[j] = -1;
			BiasWeights[j] = 0;
		}

}

void NeuralNetworkLayer::CleanUp(void)
{
	int	i;

	free(NeuronValues);
	free(DesiredValues);
	free(Errors);
	
	if(Weights != NULL)
	{
		for(i = 0; i<NumberOfNodes; i++)
		{
			free(Weights[i]);
			free(WeightChanges[i]);
		}

		free(Weights);
		free(WeightChanges);
	}

	if(BiasValues != NULL) free(BiasValues);
	if(BiasWeights != NULL) free(BiasWeights);
}

void NeuralNetworkLayer::RandomizeWeights(void)
{
	int	i,j;
	int	min = 0;
	int	max = 200;
	int	number;

	srand( (unsigned)time( NULL ) );

	for(i=0; i<NumberOfNodes; i++)
	{
		for(j=0; j<NumberOfChildNodes; j++)
		{	
			number = (((abs(rand())%(max-min+1))+min));    
    
			if(number>max)
				number = max;

			if(number<min)
    			number = min;		
			
			Weights[i][j] = number / 100.0f - 1;
		}
	}
	
	for(j=0; j<NumberOfChildNodes; j++)
	{
			number = (((abs(rand())%(max-min+1))+min));    
    
			if(number>max)
				number = max;

			if(number<min)
    			number = min;		
			
			BiasWeights[j] = number / 100.0f - 1;		
	}
}

void NeuralNetworkLayer::CalculateErrors(void)
{
	int		i, j;
	double	sum;
	
	if(ChildLayer == NULL) // output layer
	{
		for(i=0; i<NumberOfNodes; i++)
		{
			Errors[i] = (DesiredValues[i] - NeuronValues[i]) * NeuronValues[i] * (1.0f - NeuronValues[i]);
		}
	} else if(ParentLayer == NULL) { // input layer
		for(i=0; i<NumberOfNodes; i++)
		{
			Errors[i] = 0.0f;
		}
	} else { // hidden layer
		for(i=0; i<NumberOfNodes; i++)
		{
			sum = 0;
			for(j=0; j<NumberOfChildNodes; j++)
			{
				sum += ChildLayer->Errors[j] * Weights[i][j];	
			}
			Errors[i] = sum * NeuronValues[i] * (1.0f - NeuronValues[i]);
		}
	}
}

void NeuralNetworkLayer::AdjustWeights(void)
{
	int		i, j;	
	double	dw;

	if(ChildLayer != NULL)
	{
		for(i=0; i<NumberOfNodes; i++)
		{
			for(j=0; j<NumberOfChildNodes; j++)
			{
				dw = LearningRate * ChildLayer->Errors[j] * NeuronValues[i];
				Weights[i][j] += dw + MomentumFactor * WeightChanges[i][j];			
				WeightChanges[i][j] = dw;
			}
		}

		for(j=0; j<NumberOfChildNodes; j++)
		{
			BiasWeights[j] += LearningRate * ChildLayer->Errors[j] * BiasValues[j];
		}
	}
}

void NeuralNetworkLayer::CalculateNeuronValues(void)
{
	int		i,j;
	double	x;
	
	if(ParentLayer != NULL)
	{
		for(j=0; j<NumberOfNodes; j++)
		{
			x = 0;
			for(i=0; i<NumberOfParentNodes; i++)
			{
				x += ParentLayer->NeuronValues[i] * ParentLayer->Weights[i][j];
			}			
			x += ParentLayer->BiasValues[j] * ParentLayer->BiasWeights[j];
			
			if((ChildLayer == NULL) && LinearOutput)
				NeuronValues[j] = x;
			else
				NeuronValues[j] = 1.0f/(1+exp(-x));				
		}
	}
}



/////////////////////////////////////////////////////////////////////////////////////////////////
// NeuralNetwork Class
/////////////////////////////////////////////////////////////////////////////////////////////////

void NeuralNetwork::Initialize(int nNodesInput, int nNodesHidden, int nNodesOutput)
{
	InputLayer.NumberOfNodes = nNodesInput;
	InputLayer.NumberOfChildNodes = nNodesHidden;
	InputLayer.NumberOfParentNodes = 0;	
	InputLayer.Initialize(nNodesInput, NULL, &HiddenLayer);
	InputLayer.RandomizeWeights();
	
	HiddenLayer.NumberOfNodes = nNodesHidden;
	HiddenLayer.NumberOfChildNodes = nNodesOutput;
	HiddenLayer.NumberOfParentNodes = nNodesInput;		
	HiddenLayer.Initialize(nNodesHidden, &InputLayer, &OutputLayer);
	HiddenLayer.RandomizeWeights();
	
	OutputLayer.NumberOfNodes = nNodesOutput;
	OutputLayer.NumberOfChildNodes = 0;
	OutputLayer.NumberOfParentNodes = nNodesHidden;		
	OutputLayer.Initialize(nNodesOutput, &HiddenLayer, NULL);	
	
}

void NeuralNetwork::CleanUp()
{
	InputLayer.CleanUp();
	HiddenLayer.CleanUp();
	OutputLayer.CleanUp();
}

void	NeuralNetwork::SetInput(int i, double value)
{
	if((i>=0) && (i<InputLayer.NumberOfNodes))
	{
		InputLayer.NeuronValues[i] = value;
	}
}

double	NeuralNetwork::GetOutput(int i)
{
	if((i>=0) && (i<OutputLayer.NumberOfNodes))
	{
		return OutputLayer.NeuronValues[i];
	}

	return (double) INT_MAX; // to indicate an error
}

void NeuralNetwork::SetDesiredOutput(int i, double value)
{
	if((i>=0) && (i<OutputLayer.NumberOfNodes))
	{
		OutputLayer.DesiredValues[i] = value;
	}
}

void NeuralNetwork::FeedForward(void)
{
	InputLayer.CalculateNeuronValues();
	HiddenLayer.CalculateNeuronValues();
	OutputLayer.CalculateNeuronValues();
}

void NeuralNetwork::BackPropagate(void)
{
	OutputLayer.CalculateErrors();
	HiddenLayer.CalculateErrors();

	HiddenLayer.AdjustWeights();
	InputLayer.AdjustWeights();
}

int	NeuralNetwork::GetMaxOutputID(void)
{
	int		i, id;
	double	maxval;

	maxval = OutputLayer.NeuronValues[0];
	id = 0;

	for(i=1; i<OutputLayer.NumberOfNodes; i++)
	{
		if(OutputLayer.NeuronValues[i] > maxval)
		{
			maxval = OutputLayer.NeuronValues[i];
			id = i;
		}
	}

	return id;
}

double NeuralNetwork::CalculateError(void)
{
	int		i;
	double	error = 0;

	for(i=0; i<OutputLayer.NumberOfNodes; i++)
	{
		error += pow(OutputLayer.NeuronValues[i] - OutputLayer.DesiredValues[i], 2);
	}

	error = error / OutputLayer.NumberOfNodes;

	return error;
}

void NeuralNetwork::SetLearningRate(double rate)
{
	InputLayer.LearningRate = rate;
	HiddenLayer.LearningRate = rate;
	OutputLayer.LearningRate = rate;
} 

void	NeuralNetwork::SetLinearOutput(bool useLinear)
{
	InputLayer.LinearOutput = useLinear;
	HiddenLayer.LinearOutput = useLinear;
	OutputLayer.LinearOutput = useLinear;
}

void	NeuralNetwork::SetMomentum(bool useMomentum, double factor)
{
	InputLayer.UseMomentum = useMomentum;
	HiddenLayer.UseMomentum = useMomentum;
	OutputLayer.UseMomentum = useMomentum;

	InputLayer.MomentumFactor = factor;
	HiddenLayer.MomentumFactor = factor;
	OutputLayer.MomentumFactor = factor;

}

void NeuralNetwork::DumpData(char* filename)
{
	FILE*	f;
	int		i, j;

	f = fopen(filename, "w");
	
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Input Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Node Values:\n");
	fprintf(f, "\n");
	for(i=0; i<InputLayer.NumberOfNodes; i++)		
		fprintf(f, "(%d) = %f\n", i, InputLayer.NeuronValues[i]);
	fprintf(f, "\n");
	fprintf(f, "Weights:\n");
	fprintf(f, "\n");
	for(i=0; i<InputLayer.NumberOfNodes; i++)
		for(j=0; j<InputLayer.NumberOfChildNodes; j++)
			fprintf(f, "(%d, %d) = %f\n", i, j, InputLayer.Weights[i][j]);
	fprintf(f, "\n");
	fprintf(f, "Bias Weights:\n");
	fprintf(f, "\n");
	for(j=0; j<InputLayer.NumberOfChildNodes; j++)
		fprintf(f, "(%d) = %f\n", j, InputLayer.BiasWeights[j]);

	fprintf(f, "\n");
	fprintf(f, "\n");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Hidden Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Weights:\n");
	fprintf(f, "\n");
	for(i=0; i<HiddenLayer.NumberOfNodes; i++)
		for(j=0; j<HiddenLayer.NumberOfChildNodes; j++)
			fprintf(f, "(%d, %d) = %f\n", i, j, HiddenLayer.Weights[i][j]);
	fprintf(f, "\n");
	fprintf(f, "Bias Weights:\n");
	fprintf(f, "\n");
	for(j=0; j<HiddenLayer.NumberOfChildNodes; j++)
		fprintf(f, "(%d) = %f\n", j, HiddenLayer.BiasWeights[j]);

	fprintf(f, "\n");
	fprintf(f, "\n");

	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "Output Layer\n");
	fprintf(f, "--------------------------------------------------------\n");
	fprintf(f, "\n");
	fprintf(f, "Node Values:\n");
	fprintf(f, "\n");
	for(i=0; i<OutputLayer.NumberOfNodes; i++)		
		fprintf(f, "(%d) = %f\n", i, OutputLayer.NeuronValues[i]);
	fprintf(f, "\n");


	fclose(f);
}