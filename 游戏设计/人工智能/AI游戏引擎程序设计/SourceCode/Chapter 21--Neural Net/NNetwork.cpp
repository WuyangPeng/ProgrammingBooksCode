#include "NNetwork.h"
#include "utility.h"
#include <math.h>



//---------------------------------------------------------
NLayer::NLayer(int nNeurons,int nInputs,int type):
m_type(type),
m_threshold(1.0f)
{
    for (int i=0; i<nNeurons; ++i)
    {
        Neuron* newNeuron = new Neuron;

        //each neuron has nInputs+1 weights, extra one is the bias value
        for (int j=0; j<nInputs+1; ++j)
        {
            newNeuron->m_weights.push_back(randflt() - randflt());//rnd between -1 & 1
            newNeuron->m_lastDelta.push_back(0.0f);
        }
        //initial values
        newNeuron->m_output = 0.0f;
        newNeuron->m_error  = 999999.9f;

        m_neurons.push_back(newNeuron);
    }
}

//---------------------------------------------------------
void NLayer::Propagate(int type, NLayer& nextLayer)
{
    int weightIndex;
    int numNeurons = nextLayer.m_neurons.size();
    for (int i=0; i<numNeurons; ++i)
    {
        weightIndex = 0;
        float value = 0.0f;
        
        int	numWeights = m_neurons.size();
        for (int j=0; j<numWeights; ++j)
        {
            //sum the (weights * inputs), the inputs are the outputs of the prop layer
            value += nextLayer.m_neurons[i]->m_weights[j] * m_neurons[j]->m_output;
        }
        
        //add in the bias (always has an input of -1)
        value += nextLayer.m_neurons[i]->m_weights[numWeights]*-1.0f;
        
        //store the outputs, but run activation first
        switch(type)
        {
            case ACT_STEP:
                nextLayer.m_neurons[i]->m_output = ActStep(value);
                break;
            case ACT_TANH:
                nextLayer.m_neurons[i]->m_output = ActTanh(value);
                break;
            case ACT_LOGISTIC:
                nextLayer.m_neurons[i]->m_output = ActLogistic(value);
                break;
            case ACT_BIPOLAR:
                nextLayer.m_neurons[i]->m_output = ActBipolarSigmoid(value);
                break;
            case ACT_LINEAR:
            default:
                nextLayer.m_neurons[i]->m_output = value;
                break;
        }
    }
    //if you wanted to run the Softmax activation function, you
    //would do it here, since it needs all the output values
    //if you pushed all the outputs into a vector, you could...
    //outputs = ActSoftmax(outputs);
    //and then put the outputs back into the correct slots
    
    return;
}

//---------------------------------------------------------
void NLayer::BackPropagate(int type, NLayer &nextLayer)
{
    float outputVal, error;
    int numNeurons = nextLayer.m_neurons.size();
    for (int i=0; i<numNeurons; ++i)
    {
        outputVal = nextLayer.m_neurons[i]->m_output;
        error = 0;
        for (int j=0; j<m_neurons.size(); ++j)
            error += m_neurons[j]->m_weights[i] * m_neurons[j]->m_error;
        switch(type)
        {
            case ACT_TANH:
                nextLayer.m_neurons[i]->m_error = DerTanh(outputVal)*error;
                break;
            case ACT_LOGISTIC:
                nextLayer.m_neurons[i]->m_error = DerLogistic(outputVal)*error;
                break;
            case ACT_BIPOLAR:
                nextLayer.m_neurons[i]->m_error = DerBipolarSigmoid(outputVal)*error;
                break;
            case ACT_LINEAR:
            default:
                nextLayer.m_neurons[i]->m_error = outputVal*error;
                    break;
        }
    }
}

//---------------------------------------------------------
void NLayer::AdjustWeights(NLayer& inputs,float lrate, float momentum)
{
    for (int i=0; i<m_neurons.size(); ++i)
    {
        int numWeights = m_neurons[i]->m_weights.size();
        for (int j=0; j<numWeights; ++j)
        {
            //bias weight always uses -1 output value
            float output = (j==numWeights-1)? -1 : inputs.m_neurons[j]->m_output;
            float error  = m_neurons[i]->m_error;
            float delta  = momentum*m_neurons[i]->m_lastDelta[j] + (1-momentum)*lrate * error * output;
            m_neurons[i]->m_weights[j]   += delta;
            m_neurons[i]->m_lastDelta[j]  = delta;
        }
    }
}

//---------------------------------------------------------
float NLayer::ActLogistic(float value)
{
    return (1/(1+exp(-value*m_threshold)));
}

//---------------------------------------------------------
float NLayer::DerLogistic(float value)
{
    return (value*m_threshold*(1.0f-value));
}

//---------------------------------------------------------
float NLayer::ActBipolarSigmoid(float value)
{
    return ((2/(1+exp(-value*m_threshold)))-1);
}

//---------------------------------------------------------
float NLayer::DerBipolarSigmoid(float value)
{
    return (0.5f*m_threshold*(1+value)*(1-value));
}

//---------------------------------------------------------
float NLayer::ActStep(float value)
{
    return ((value > m_threshold)? 1.0f : 0.0f);
}

//---------------------------------------------------------
float NLayer::ActTanh(float value)
{
    return (tanh(value*m_threshold));
}
//---------------------------------------------------------
float NLayer::DerTanh(float value)
{
    return (1-value*value);
}
//---------------------------------------------------------
void NLayer::ActSoftmax(NLayer& outputs)
{
    float total = 0.0f;
    for(int i= 0;i<m_neurons.size();++i)
        total = exp(outputs.m_neurons[i]->m_output);
    for(i = 0;i<m_neurons.size();++i)
        outputs.m_neurons[i]->m_output = exp(outputs.m_neurons[i]->m_output)/total;
}

//---------------------------------------------------------
NeuralNet::NeuralNet(int nIns,int nOuts,int nHiddenLays,int nNodesPerHLays)
{
    m_nInputs      = nIns;
    m_nOutputs     = nOuts;
    m_nLayers      = nHiddenLays + 2;//plus the output layer
    m_nHiddenNodesperLayer = nNodesPerHLays;

    Init();
}

//---------------------------------------------------------
void NeuralNet::AddLayer(int nNeurons,int nInputs,int type)
{
    m_layers.push_back(NLayer(nNeurons,nInputs,type));
}

//---------------------------------------------------------
void NeuralNet::Init()
{
    m_inputLayer   = NULL;
    m_outputLayer  = NULL;
    m_actType      = ACT_BIPOLAR;
    m_outputActType= ACT_LOGISTIC;
    m_momentum     = 0.9f;
    m_learningRate = 0.1f;
    
    //error check
    if(m_nLayers<2)
        return;
    
    //clear out the layers, incase you're restarting the net
    m_layers.clear();

    //input layer
    AddLayer(m_nInputs, 1, NLT_INPUT);
    
    if(m_nLayers > 2)//multilayer network
    {
        //first hidden layer connect back to inputs
        AddLayer(m_nHiddenNodesperLayer, m_nInputs, NLT_HIDDEN);
        
        //any other hidden layers connect to other hidden outputs
        //-3 since the first layer was the inputs,
        //the second (connected to inputs) was initialized above,
        //and the last one (connect to outputs) will be initiallized below
        for (int i=0; i<m_nLayers-3; ++i)
            AddLayer(m_nHiddenNodesperLayer, m_nHiddenNodesperLayer, NLT_HIDDEN);
        
        //the output layer also connects to hidden outputs
        AddLayer(m_nOutputs, m_nHiddenNodesperLayer, NLT_OUTPUT);
    }
    else//perceptron
    {
        //output layer connects to inputs
        AddLayer(m_nOutputs, m_nInputs, NLT_OUTPUT);
    }
    m_inputLayer = &m_layers[0];
    m_outputLayer= &m_layers[m_nLayers-1];
}

//---------------------------------------------------------
void NeuralNet::Propagate()
{
    for (int i=0; i<m_nLayers-1; ++i)
    {
        int type = (m_layers[i+1].m_type == NLT_OUTPUT)? m_outputActType : m_actType;
        m_layers[i].Propagate(type,m_layers[i+1]);
    }
}

//---------------------------------------------------------
void NeuralNet::BackPropagate()
{
    //backprop the error
    for (int i=m_nLayers-1; i>0; --i)
        m_layers[i].BackPropagate(m_actType,m_layers[i-1]);
    
    //adjust the weights
    for (i=1; i<m_nLayers; i++)
        m_layers[i].AdjustWeights(m_layers[i-1],m_learningRate,m_momentum);
}

//---------------------------------------------------------
void NeuralNet::Train(vector<float> &inputs,vector<float> &outputs)
{
    SetInputs(inputs);
    Propagate();
    FindError(outputs);
    BackPropagate();
}

//---------------------------------------------------------
void NeuralNet::Use(vector<float> &inputs,vector<float> &outputs)
{
    SetInputs(inputs);
    Propagate();
    outputs.clear();
    //return the net outputs
    for(int i =0;i< m_outputLayer->m_neurons.size();++i)
        outputs.push_back(m_outputLayer->m_neurons[i]->m_output);
}

//---------------------------------------------------------
void NeuralNet::SetInputs(vector<float>& inputs)
{
    int numNeurons = m_inputLayer->m_neurons.size();
    for (int i = 0; i<numNeurons; ++i)
        m_inputLayer->m_neurons[i]->m_output = inputs[i];
}
//---------------------------------------------------------
void NeuralNet::FindError(vector<float>& outputs)
{
    m_error = 0;
    int numNeurons = m_outputLayer->m_neurons.size();
    for (int i=0; i<numNeurons; ++i)
    {
        float outputVal = m_outputLayer->m_neurons[i]->m_output;
        float error = outputs[i]-outputVal;
        switch(m_actType)
        {
            case ACT_TANH:
                m_outputLayer->m_neurons[i]->m_error = m_outputLayer->DerTanh(outputVal)*error;
                break;
            case ACT_BIPOLAR:
                m_outputLayer->m_neurons[i]->m_error = m_outputLayer->DerBipolarSigmoid(outputVal)*error;
                break;
            case ACT_LOGISTIC:
                m_outputLayer->m_neurons[i]->m_error = m_outputLayer->DerLogistic(outputVal)*error;
                break;
            case ACT_LINEAR:
            default:
                m_outputLayer->m_neurons[i]->m_error = outputVal*error;
                break;
        }
        //error calculation for the entire net
        m_error += 0.5*error*error;
    }
}

//---------------------------------------------------------
void NeuralNet::WriteWeights()
{
    FILE* pFile;
    if ((pFile = fopen("NNWeightData.txt","w")) == NULL)
        return;
    
    for(int i = 0;i<m_nLayers;++i)
    {
        int numNeurons = m_layers[i].m_neurons.size();
        for(int j =0;j<numNeurons;++j)
        {
            int numWeights = m_layers[i].m_neurons[j]->m_weights.size();
            for(int k=0;k< numWeights;++k)
                fprintf(pFile,"%f ",m_layers[i].m_neurons[j]->m_weights[k]);
        }
    }
    fclose(pFile);
}

//---------------------------------------------------------
void NeuralNet::ReadWeights()
{
    FILE* pFile;
    if ((pFile = fopen("NNWeightData.txt","r")) == NULL)
        return;
    
    for(int i = 0;i<m_nLayers;++i)
    {
        int numNeurons = m_layers[i].m_neurons.size();
        for(int j =0;j<numNeurons;++j)
        {
            int numWeights = m_layers[i].m_neurons[j]->m_weights.size();
            for(int k=0;k< numWeights;++k)
                fscanf(pFile,"%f ",&m_layers[i].m_neurons[j]->m_weights[k]);
        }
    }
    fclose(pFile);
}