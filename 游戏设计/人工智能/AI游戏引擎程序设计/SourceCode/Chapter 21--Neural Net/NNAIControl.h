#pragma once

#include "FSMAIControl.h"
#include "utility.h"

class Ship;
class GameObj;
class NeuralNet;
class FSMMachine;

#define NUM_TRAINING_SETS_TO_AQUIRE  1000
#define BOOL_THRESHOLD 0.5f

enum
{
    NM_USE,
    NM_TRAIN,
    NM_RETRAIN
};

//main class declaration
class NNAIControl: public FSMAIControl
{
public:
    //constructor/functions
    NNAIControl(Ship* ship = NULL);
    ~NNAIControl();
    void Update(float dt);
    void UpdatePerceptions(float dt);
    void Init();
    void Reset();
    void GetNetOutput();
    void TrainNetAndSave();
    void ReTrainNetAndSave();

    //perception data 
    float       m_powerupScanDist;

    //network output variables
    bool        m_shouldThrust;
    bool        m_shouldTurnLeft;
    bool        m_shouldTurnRight;

private:
    int         m_numIterationsToTrain;
    int         m_numSavedTrainingSets;
    float       m_maximumAllowedError;

    //network input variables
    float       m_speedMovingTogether;
    Point3f     m_nearestAsteroidDelta;
    float       m_shipMovingDirection;
    
    //net, used for training and for actual usage in game
    NeuralNet*    m_net;
    vector<float> m_inputs;
    vector<float> m_outputs;
    int m_numInputs;
    int m_numOutputs;
    int m_numHiddenLayers;
    int m_numHiddenNodes;
    int m_netMode;
};
