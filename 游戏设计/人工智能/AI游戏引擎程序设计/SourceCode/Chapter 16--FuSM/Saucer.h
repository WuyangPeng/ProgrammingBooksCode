#ifndef __SAUCER
#define __SAUCER

#include "Ship.h"

class Bullet;
class Control;

class Saucer : public Ship
{
public:
    //constructor/functions
    Saucer(int size = 3);
    void Draw();
    void Init();
    
    //bullet management
    virtual void Shoot(float angle = -1);
    virtual float GetClosestGunAngle(float angle) {return angle;}
};
#endif