#pragma once

#include "AIControl.h"

class Ship;
class GAMachine;
class GameObj;

//main class declaration
class GAAIControl: public AIControl
{
public:
    //constructor/functions
    GAAIControl(Ship* ship = NULL);
    ~GAAIControl();
    void Update(float dt);
    void UpdatePerceptions(float dt,int index);
    void Init();
    void Reset();

    GAMachine*  m_GAMachine;
    //perception data 
    GameObj*    m_nearestAsteroid;
    float       m_nearestAsteroidDist;
    int         m_currentEvasionSituation;
    float       m_maxSpeed;
};
