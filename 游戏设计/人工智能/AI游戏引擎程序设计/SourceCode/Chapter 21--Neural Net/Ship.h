#ifndef __SHIP
#define __SHIP

#include "GameObj.h"

class Bullet;
class Control;
class Sphere3;

#define MAX_SHOT_LEVEL    3
#define MAX_SHIP_SPEED    120
#define MAX_AG_SHIP_SPEED 120
#define MAX_TRACTOR_DIST  180
#define MAX_TRACTOR_POWER 300

class Ship : public GameObj
{
public:
	//constructor/functions
	Ship(int size = 3);
	virtual void Draw();
	virtual void Init();
	virtual void Update(float dt);
	virtual bool IsColliding(GameObj *obj);
	virtual void DoCollision(GameObj *obj);
	
	//controls
	void ThrustOn()     {m_thrust=true;m_revThrust=false;}
	void ThrustReverse(){m_revThrust=true;m_thrust=false;}
	void ThrustOff()    {m_thrust=false;m_revThrust=false;}
	void TurnLeft();	
	void TurnRight();	
	void StopTurn()		{m_angVelocity =    0.0f;}
	void Stop();
    void Hyperspace();

    void TractorBeamOn(Point3f &offset);
    void StopTractorBeam(){m_tractor = false;}
    void ApplyTractorBeam(float dt);
    void AGThrustOn(Point3f &offset);
    void AGThrustAccumulate(Point3f &offset);
    void StopAGThrust()   {m_agThrust = false;}
    void AGMove(float dt);
    Point3f& GetAGvector() {return m_agNorm;}
    bool IsThrustOn() {return m_thrust;}
    bool IsTurningRight();
    bool IsTurningLeft();

	//Powerup management
	virtual void GetPowerup(int powerupType);
	int GetShotLevel() {return m_shotPowerLevel;}
    int GetNumBullets(){return m_activeBulletCount;}
    void IncNumBullets(int num = 1){m_activeBulletCount+=num;}
    void MakeInvincible(float time){m_invincibilityTimer = time;}

	//bullet management
	virtual int MaxBullet();
	void TerminateBullet(){ if(m_activeBulletCount > 0)m_activeBulletCount--;};
	virtual void Shoot(float angle = -1);
	virtual float GetClosestGunAngle(float angle);
    virtual float GetClosestGunApproachAngle(float angle);
        
	//data
	Control* m_control;
    bool    m_willCollide;
protected:
	int		m_activeBulletCount;
	bool	m_thrust;
    bool	m_revThrust;
    bool	m_agThrust;
    bool	m_tractor;
	int		m_shotPowerLevel;
	float   m_invincibilityTimer;
    Point3f m_agNorm;
    Point3f m_tractorNorm;
};
#endif