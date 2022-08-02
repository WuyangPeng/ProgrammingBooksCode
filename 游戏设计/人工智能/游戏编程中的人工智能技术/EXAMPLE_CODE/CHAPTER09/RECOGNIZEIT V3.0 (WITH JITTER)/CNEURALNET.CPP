#include "CNeuralNet.h"


//*************************** methods for Neuron **********************
//
//---------------------------------------------------------------------
SNeuron::SNeuron(int NumInputs): m_iNumInputs(NumInputs+1),
                                 m_dActivation(0),
                                 m_dError(0)
											
{
	//we need an additional weight for the bias hence the +1
	for (int i=0; i<NumInputs+1; ++i)
	{
		//set up the weights with an initial random value
		m_vecWeight.push_back(RandomClamped());

    m_vecPrevUpdate.push_back(0);
	}
}




//************************ methods for NeuronLayer **********************

//-----------------------------------------------------------------------
//	ctor creates a layer of neurons of the required size by calling the 
//	SNeuron ctor the rqd number of times
//-----------------------------------------------------------------------
SNeuronLayer::SNeuronLayer(int NumNeurons, 
                           int NumInputsPerNeuron):	m_iNumNeurons(NumNeurons)
{
	for (int i=0; i<NumNeurons; ++i)

		m_vecNeurons.push_back(SNeuron(NumInputsPerNeuron));
}




//************************ methods forCNeuralNet ************************



//------------------------------- ctor -----------------------------------
//
//------------------------------------------------------------------------
CNeuralNet::CNeuralNet(int NumInputs,
                       int NumOutputs,
                       int HiddenNeurons,
                       double LearningRate):m_iNumInputs(NumInputs),
                                            m_iNumOutputs(NumOutputs),
                                            m_iNumHiddenLayers(1),
                                            m_iNeuronsPerHiddenLyr(HiddenNeurons),
                                            m_dLearningRate(LearningRate),
                                            m_dErrorSum(9999),
                                            m_bTrained(false),
                                            m_iNumEpochs(0)
{
	CreateNet();
}

//------------------------------createNet()------------------------------
//
//	this method builds the ANN. The weights are all initially set to 
//	random values -1 < w < 1
//------------------------------------------------------------------------
void CNeuralNet::CreateNet()
{
	//create the layers of the network
	if (m_iNumHiddenLayers > 0)
	{
		//create first hidden layer
	  m_vecLayers.push_back(SNeuronLayer(m_iNeuronsPerHiddenLyr, m_iNumInputs));
    
    for (int i=0; i<m_iNumHiddenLayers-1; ++i)
    {

			m_vecLayers.push_back(SNeuronLayer(m_iNeuronsPerHiddenLyr,
                                         m_iNeuronsPerHiddenLyr));
    }

    //create output layer
	  m_vecLayers.push_back(SNeuronLayer(m_iNumOutputs, m_iNeuronsPerHiddenLyr));
	}

  else
  {
	  //create output layer
	  m_vecLayers.push_back(SNeuronLayer(m_iNumOutputs, m_iNumInputs));
  }
}


//--------------------------- Initialize ---------------------------------
//
//  randomizes all the weights to values btween 0 and 1
//------------------------------------------------------------------------
void CNeuralNet::InitializeNetwork()
{
	//for each layer
	for (int i=0; i<m_iNumHiddenLayers + 1; ++i)
	{
		//for each neuron
		for (int n=0; n<m_vecLayers[i].m_iNumNeurons; ++n)
		{
			//for each weight
			for (int k=0; k<m_vecLayers[i].m_vecNeurons[n].m_iNumInputs; ++k)
			{
				m_vecLayers[i].m_vecNeurons[n].m_vecWeight[k] = RandomClamped();
			}
		}
	}

  m_dErrorSum  = 9999;
  m_iNumEpochs = 0;

	return;
}

//-------------------------------Update-----------------------------------
//
//	given an input vector this function calculates the output vector
//
//------------------------------------------------------------------------
vector<double> CNeuralNet::Update(vector<double> inputs)
{
	//add in some noise to the data
  for (int k=0; k<inputs.size(); ++k)
  {
    inputs[k]+=RandFloat() * MAX_NOISE_TO_ADD;
  }
  
  //stores the resultant outputs from each layer
	vector<double> outputs;
  
	int cWeight = 0;
	
	//first check that we have the correct amount of inputs
	if (inputs.size() != m_iNumInputs)
  {
		//just return an empty vector if incorrect.
		return outputs;
  }
	
	//For each layer...
	for (int i=0; i<m_iNumHiddenLayers + 1; ++i)
	{
		
		if ( i > 0 )
    {
			inputs = outputs;
    }

		outputs.clear();
		
		cWeight = 0;

		//for each neuron sum the (inputs * corresponding weights).Throw 
		//the total at our sigmoid function to get the output.
		for (int n=0; n<m_vecLayers[i].m_iNumNeurons; ++n)
		{
			double netinput = 0.0f;

			int	NumInputs = m_vecLayers[i].m_vecNeurons[n].m_iNumInputs;
			
			//for each weight
			for (int k=0; k<NumInputs - 1; ++k)
			{
				//sum the weights x inputs
				netinput += m_vecLayers[i].m_vecNeurons[n].m_vecWeight[k] * 
                    inputs[cWeight++];
			}

			//add in the bias
			netinput += m_vecLayers[i].m_vecNeurons[n].m_vecWeight[NumInputs-1] * 
                  BIAS;

			 
      //The combined activation is first filtered through the sigmoid 
      //function and a record is kept for each neuron 
      m_vecLayers[i].m_vecNeurons[n].m_dActivation = 
        Sigmoid(netinput, ACTIVATION_RESPONSE);

			//store the outputs from each layer as we generate them.
      outputs.push_back(m_vecLayers[i].m_vecNeurons[n].m_dActivation);

			cWeight = 0;
		}
	}

	return outputs;
}

//----------------------------NetworkTrainingEpoch -----------------------
//
//  given a training set this method trains the network using backprop.
//  The training sets comprise of series of input vectors and a series
//  of output vectors.
//  Returns false if there is a problem
//------------------------------------------------------------------------
bool CNeuralNet::NetworkTrainingEpoch(vector<iovector> &SetIn,
                                      vector<iovector> &SetOut)
{
  //create some iterators
  vector<double>::iterator  curWeight;
  vector<SNeuron>::iterator curNrnOut, curNrnHid;

  double WeightUpdate = 0;

  //this will hold the cumulative error value for the training set
  m_dErrorSum = 0;

  //run each input pattern through the network, calculate the errors and update
  //the weights accordingly
  for (int vec=0; vec<SetIn.size(); ++vec)
  {
    //first run this input vector through the network and retrieve the outputs
    vector<double> outputs = Update(SetIn[vec]);

    //return if error has occurred
    if (outputs.size() == 0)
    {
      return false;
    }

    //for each output neuron calculate the error and adjust weights
    //accordingly
    for (int op=0; op<m_iNumOutputs; ++op)
    {
      //first calculate the error value
      double err = (SetOut[vec][op] - outputs[op]) * outputs[op]
                   * (1 - outputs[op]);

      //update the error total. (when this value becomes lower than a
      //preset threshold we know the training is successful)
      m_dErrorSum += (SetOut[vec][op] - outputs[op]) *
                     (SetOut[vec][op] - outputs[op]);      

      //keep a record of the error value
      m_vecLayers[1].m_vecNeurons[op].m_dError = err;

      curWeight = m_vecLayers[1].m_vecNeurons[op].m_vecWeight.begin();
      curNrnHid = m_vecLayers[0].m_vecNeurons.begin();

      int w = 0;

      //for each weight up to but not including the bias
      while(curWeight != m_vecLayers[1].m_vecNeurons[op].m_vecWeight.end()-1)
      {
        //calculate weight update
        WeightUpdate = err * m_dLearningRate * curNrnHid->m_dActivation;
        
        //calculate the new weight based on the backprop rules and adding in momentum
        *curWeight += WeightUpdate + m_vecLayers[1].m_vecNeurons[op].m_vecPrevUpdate[w] * MOMENTUM;

        //keep a record of this weight update
        m_vecLayers[1].m_vecNeurons[op].m_vecPrevUpdate[w] = WeightUpdate;

        ++curWeight; ++curNrnHid; ++w;
      }

      //and the bias for this neuron
      WeightUpdate = err * m_dLearningRate * BIAS;

      *curWeight += WeightUpdate + m_vecLayers[1].m_vecNeurons[op].m_vecPrevUpdate[w] * MOMENTUM;  

      //keep a record of this weight update
      m_vecLayers[1].m_vecNeurons[op].m_vecPrevUpdate[w] = WeightUpdate;
      
      
    }

   //**moving backwards to the hidden layer**
    curNrnHid = m_vecLayers[0].m_vecNeurons.begin();

    int n = 0;
    
    //for each neuron in the hidden layer calculate the error signal
    //and then adjust the weights accordingly
    while(curNrnHid != m_vecLayers[0].m_vecNeurons.end())
    {
      double err = 0;

      curNrnOut = m_vecLayers[1].m_vecNeurons.begin();

      //to calculate the error for this neuron we need to iterate through
      //all the neurons in the output layer it is connected to and sum
      //the error * weights
      while(curNrnOut != m_vecLayers[1].m_vecNeurons.end())
      {
        err += curNrnOut->m_dError * curNrnOut->m_vecWeight[n];

        ++curNrnOut;
      }

      //now we can calculate the error
      err *= curNrnHid->m_dActivation * (1 - curNrnHid->m_dActivation);     
      
      //for each weight in this neuron calculate the new weight based
      //on the error signal and the learning rate
      for (int w=0; w<m_iNumInputs; ++w)
      {
        WeightUpdate = err * m_dLearningRate * SetIn[vec][w];

        //calculate the new weight based on the backprop rules and adding in momentum
        curNrnHid->m_vecWeight[w] += WeightUpdate + curNrnHid->m_vecPrevUpdate[w] * MOMENTUM;
        
        //keep a record of this weight update
        curNrnHid->m_vecPrevUpdate[w] = WeightUpdate;

      }

      //and the bias
      WeightUpdate = err * m_dLearningRate * BIAS;

      curNrnHid->m_vecWeight[m_iNumInputs] += WeightUpdate + curNrnHid->m_vecPrevUpdate[w] * MOMENTUM;

      //keep a record of this weight update
       curNrnHid->m_vecPrevUpdate[w] = WeightUpdate;

      ++curNrnHid;
      ++n;
    }

  }//next input vector
  return true;
}

//----------------------------- Train ------------------------------------
//
//  Given some training data in the form of a CData object this function
//  trains the network until the error is within acceptable limits.
// 
//  the HWND is required to give some graphical feedback
//------------------------------------------------------------------------
bool CNeuralNet::Train(CData* data, HWND hwnd)
{
  vector<vector<double> > SetIn  = data->GetInputSet();
  vector<vector<double> > SetOut = data->GetOutputSet();

   //first make sure the training set is valid
   if ((SetIn.size()     != SetOut.size())  || 
       (SetIn[0].size()  != m_iNumInputs)   ||
       (SetOut[0].size() != m_iNumOutputs))
   {
     MessageBox(NULL, "Inputs != Outputs", "Error", NULL);
    
     return false;
   }
  
   //initialize all the weights to small random values
   InitializeNetwork();

   //train using backprop until the SSE is below the user defined
   //threshold
   while( m_dErrorSum > ERROR_THRESHOLD )
   {
     //return false if there are any problems
     if (!NetworkTrainingEpoch(SetIn, SetOut))
     {
       return false;
     }

     ++m_iNumEpochs;
     
     //call the render routine to display the error sum
     InvalidateRect(hwnd, NULL, TRUE);
		 UpdateWindow(hwnd);
   }

   m_bTrained = true;
   
   return true;
}


//-------------------------------Sigmoid function-------------------------
//
//------------------------------------------------------------------------
double CNeuralNet::Sigmoid(double netinput, double response)
{
	return ( 1 / ( 1 + exp(-netinput / response)));
}


