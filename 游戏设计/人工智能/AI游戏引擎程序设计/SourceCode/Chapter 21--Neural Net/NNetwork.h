#pragma once

#include <vector>

using namespace std;

enum
{
    NLT_INPUT,
    NLT_HIDDEN,
    NLT_OUTPUT
};

enum
{
    ACT_LOGISTIC,
    ACT_BIPOLAR,
    ACT_STEP,
    ACT_TANH,
    ACT_SOFTMAX,
    ACT_LINEAR
};

struct Neuron
{
    vector<float> m_weights;   //connection strengths
    vector<float> m_lastDelta;//used for inertia in updating the weights while learning
    float m_output;           //the fired potential of the neuron
    float m_error;            //the error gradient of the potential from the expected 
                              //potential; used when learning
};



class NLayer
{
public:
    NLayer(int nNeurons, int nInputs, int type = NLT_INPUT);
    void Propagate(int type, NLayer& nextLayer);
    void BackPropagate(int type, NLayer& nextLayer);
    void AdjustWeights(NLayer& inputs,float lrate = 0.1f, float momentum = 0.9f);
    
    //activation functions
    float ActLogistic(float value);
    float ActStep(float value);
    float ActTanh(float value);
    float ActBipolarSigmoid(float value);
    void  ActSoftmax(NLayer& outputs);

    //inverse functions for backprop
    float DerLogistic(float value);
    float DerTanh(float value);
    float DerBipolarSigmoid(float value);
    
    //data
    vector<Neuron*> m_neurons;
    int             m_type;
    float           m_threshold;
};


class NeuralNet
{
    
public:
    
    NeuralNet(int nIns,int nOuts,int nHiddenLays,int nNodesinHiddenLays);
    void Init();
    
    //access methods    
    void Use(vector<float> &inputs,vector<float> &outputs);
    void Train(vector<float> &inputs,vector<float> &outputs);
    float GetError()    {return m_error;}
    void WriteWeights();
    void ReadWeights();

protected:
    //internal methods
    void AddLayer(int nNeurons,int nInputs,int type);
    void SetInputs(vector<float>& inputs);
    void FindError(vector<float>& outputs);
    void Propagate();
    void BackPropagate();

    //data
    vector<NLayer>  m_layers;
    NLayer*         m_inputLayer;
    NLayer*         m_outputLayer;

    float           m_learningRate;
    float           m_momentum;
    float           m_error;

    int             m_nInputs;
    int             m_nOutputs;
    int             m_nLayers;
    int             m_nHiddenNodesperLayer;
    int             m_actType;
    int             m_outputActType;
};

