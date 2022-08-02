#include "NNAIControl.h"
#include "GameSession.h"
#include "utility.h"
#include <algorithm>
#include "NNetwork.h"
#include "FSMMachine.h"
#include "StateApproach.h"
#include "StateAttack.h"
#include "StateNNEvade.h"
#include "StateGetPowerup.h"
#include "StateIdle.h"

#include "Target.h"


//---------------------------------------------------------
NNAIControl::NNAIControl(Ship* ship)
{
    if(m_ship)
        m_ship->m_control = this;
    m_type = CONTROLTYPE_AI;
    
    m_debugTxt = new char[30];
    m_target   = NULL;
    m_net      = NULL;
    
    Init();
    
    if(m_netMode == NM_USE)
    {
        //construct the state machine and add the necessary states
        m_machine = new FSMMachine(FSM_MACH_MAINSHIP,this);
        StateApproach* approach = new StateApproach(this);
        m_machine->AddState(approach);
        m_machine->AddState(new StateAttack(this));
        m_machine->AddState(new StateNNEvade(this));
        m_machine->AddState(new StateGetPowerup(this));
        StateIdle* idle = new StateIdle(this);
        m_machine->AddState(idle);
        //  m_machine->SetDefaultState(idle);
        m_machine->SetDefaultState(approach);
        m_machine->Reset();

        m_net = new NeuralNet(m_numInputs,m_numOutputs,m_numHiddenLayers,m_numHiddenNodes);
        m_net->ReadWeights();
    }
    else if (m_netMode == NM_RETRAIN)
    {
        m_numSavedTrainingSets = 1000;
        ReTrainNetAndSave();
    }
    
}

//---------------------------------------------------------
NNAIControl::~NNAIControl()
{
    if(m_target)
        delete m_target;
}

//---------------------------------------------------------
void NNAIControl::Init()
{
    m_nearestAsteroid         = NULL;
    m_nearestPowerup          = NULL;
    m_maxSpeed                = 80.0f;
    m_powerupScanDist         = 180.0f;
    m_willCollide             = false;
    m_shouldThrust            = false;
    m_shouldTurnLeft          = false;
    m_shouldTurnRight         = false;

    //net setup variables
    m_inputs.clear();
    m_outputs.clear();
    m_numIterationsToTrain    = 2000;
    m_numSavedTrainingSets    = 0;
    m_maximumAllowedError     = 0.005f;
    m_netMode                 = NM_USE;
//    m_netMode                 = NM_RETRAIN;
//    m_netMode                 = NM_TRAIN;
    m_numInputs       = 4;
    m_numOutputs      = 3;
    m_numHiddenLayers = 1;
    m_numHiddenNodes  = 8;
    
    if(!m_target)
    {
        m_target = new Target;
        m_target->m_size = 1;
        Game.PostGameObj(m_target);
    }
}

//---------------------------------------------------------
void NNAIControl::Update(float dt)
{
    Ship* ship = Game.m_mainShip;
    if(!ship)
    {
        m_machine->Reset();
        return;
    }
    
    switch(m_netMode)
    {
        case NM_TRAIN:
            UpdatePerceptions(dt);
            if(m_willCollide)
            {
                //write test data to file
                FILE* pFile;
                if ((pFile = fopen("NNtrainingdata.txt","a")) == NULL)
                    return;
            
                fprintf(pFile,"%f %f %f %f ",m_nearestAsteroidDelta.x(),
                        m_nearestAsteroidDelta.y(),m_speedMovingTogether,m_shipMovingDirection);
                fprintf(pFile,"%d %d %d ",ship->IsThrustOn(),ship->IsTurningRight(),ship->IsTurningLeft());

                m_numSavedTrainingSets++;
                m_inputs.push_back(m_nearestAsteroidDelta.x());
                m_inputs.push_back(m_nearestAsteroidDelta.y());
                m_inputs.push_back(m_speedMovingTogether);
                m_inputs.push_back(m_shipMovingDirection);
                m_outputs.push_back(ship->IsThrustOn());
                m_outputs.push_back(ship->IsTurningRight());
                m_outputs.push_back(ship->IsTurningLeft());
            
                fclose(pFile);
            }
        
            if(m_numSavedTrainingSets == NUM_TRAINING_SETS_TO_AQUIRE)
            {
                TrainNetAndSave();
                Game.GameOver();
            }
            break;
        
        case NM_RETRAIN:
            Game.GameOver();
            break;

        case NM_USE:
        default:
            UpdatePerceptions(dt);
            if(m_willCollide)
                GetNetOutput();
            m_machine->UpdateMachine(dt);
            break;
    }
}

//---------------------------------------------------------
void NNAIControl::UpdatePerceptions(float dt)
{
    Ship* ship = Game.m_mainShip;
    if(!ship)
        return;
    
    //determine current game evasion state
    int collisionState = -1;
    int directionState = -1;
    int distanceState  = -1;
    
    //store closest asteroid
    m_nearestAsteroid = Game.GetClosestGameObj(ship,GameObj::OBJ_ASTEROID);
    m_nearestPowerup  = Game.GetClosestGameObj(m_ship,GameObj::OBJ_POWERUP);
    
    //reset distance to a large bogus number
    m_nearestAsteroidDist = 100000.0f;
    
    m_willCollide       = false;
    ship->m_willCollide = false;
    float distDelta;
    if(m_nearestAsteroid)
    {
        if(m_willCollide)
            m_safetyRadius = 30.0f;
        else
            m_safetyRadius = 15.0f;
        
        float speed = m_ship->m_velocity.Length();
        m_nearestAsteroidDist = m_nearestAsteroid->m_position.Distance(m_ship->m_position);
        Point3f normDelta = m_nearestAsteroid->m_position - m_ship->m_position;
        normDelta.Normalize();
        float astSpeed = m_nearestAsteroid->m_velocity.Length();
        float shpSpeedAdj = DOT(m_ship->UnitVectorVelocity(),normDelta)*speed;
        float astSpeedAdj = DOT(m_nearestAsteroid->UnitVectorVelocity(),-normDelta)*astSpeed;
        m_speedMovingTogether = shpSpeedAdj+astSpeedAdj;
        
        float spdAdj = LERP(m_speedMovingTogether/m_maxSpeed,0.0f,90.0f);
        float adjSafetyRadius = (m_safetyRadius+spdAdj+m_nearestAsteroid->m_size);
        
        //if you're too close, and I'm heading somewhat towards you,
        //flag a collision
        distDelta = m_nearestAsteroidDist - adjSafetyRadius;
        if(distDelta <= 0 && m_speedMovingTogether > 0)
        {
            m_willCollide = true;
            ship->m_willCollide = true;
        }
    }

    if(m_nearestAsteroid)
        m_nearestAsteroidDelta = m_nearestAsteroid->m_position - m_ship->m_position;
    m_shipMovingDirection  = CALCDIR360(ship->m_velocity);
    
    //powerup near determination
    m_powerupNear = false;
    if(m_nearestPowerup)
    {
        m_nearestPowerupDist = m_nearestPowerup->m_position.Distance(m_ship->m_position);
        if(m_nearestPowerupDist <= m_powerupScanDist)
        {
            m_powerupNear     = true;
        }
    }
    
}


//---------------------------------------------------------
void NNAIControl::Reset()
{
    Init();
}

//---------------------------------------------------------
void NNAIControl::TrainNetAndSave()
{
    m_net = new NeuralNet(m_numInputs,m_numOutputs,m_numHiddenLayers,m_numHiddenNodes);
    
    vector<float> tempIns;
    vector<float> tempOuts;
    for(int i =0;i< m_numIterationsToTrain;++i)
    {
        for(int j = 0;j< m_numSavedTrainingSets; ++j)
        {
            tempIns.clear();
            tempOuts.clear();
            //get training set inputs
            for(int k = 0;k<m_numInputs;++k)
                tempIns.push_back(m_inputs[k+j*m_numInputs]);
            //get training set outputs
            for(k = 0;k<m_numOutputs;++k)
                tempOuts.push_back(m_outputs[k+j*m_numOutputs]);
            
            m_net->Train(tempIns,tempOuts);
        }
        float totalError = m_net->GetError();
        if(totalError < m_maximumAllowedError)
        {
            //save out net and exit
            m_net->WriteWeights();
            return;
        }
    }
}

//---------------------------------------------------------
void NNAIControl::ReTrainNetAndSave()
{
    FILE* pFile; 
    if ((pFile = fopen("NNtrainingdata.txt","r")) == NULL)
        return;
        
    m_net = new NeuralNet(m_numInputs,m_numOutputs,m_numHiddenLayers,m_numHiddenNodes);
    
    vector<float> tempIns;
    vector<float> tempOuts;
    for(int i =0;i< m_numIterationsToTrain;++i)
    {
        for(int j = 0;j< m_numSavedTrainingSets; ++j)
        {
            tempIns.clear();
            tempOuts.clear();
            //get training set inputs
            for(int k = 0;k<m_numInputs;++k)
            {
                float temp;
                fscanf(pFile,"%f ",&temp);
                tempIns.push_back(temp);
            }
            //get training set outputs
            for(k = 0;k<m_numOutputs;++k)
            {
                float temp;
                fscanf(pFile,"%f ",&temp);
                tempOuts.push_back(temp);
            }
            
            m_net->Train(tempIns,tempOuts);
        }
        float totalError = m_net->GetError();
        if(i> 100 && totalError < m_maximumAllowedError)
        {
            //save out net and exit
            m_net->WriteWeights();
            return;
        }
    }
}

//---------------------------------------------------------
void NNAIControl::GetNetOutput()
{
    //clear out temp storage
    m_inputs.clear();
    m_outputs.clear();

    //set up inputs
    m_inputs.push_back(m_nearestAsteroidDelta.x());
    m_inputs.push_back(m_nearestAsteroidDelta.y());
    m_inputs.push_back(m_speedMovingTogether);
    m_inputs.push_back(m_shipMovingDirection);

    //get output values
    m_net->Use(m_inputs,m_outputs);
    m_shouldThrust    = m_outputs[0] > BOOL_THRESHOLD;
    m_shouldTurnRight = m_outputs[1] > BOOL_THRESHOLD;
    m_shouldTurnLeft  = m_outputs[2] > BOOL_THRESHOLD;
}
