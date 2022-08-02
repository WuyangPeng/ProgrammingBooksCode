#ifndef TANK_H
#define TANK_H

#include "Entity.h"

class Tank : public Entity  
{
public:		
	Tank(void);
	~Tank(void);

	void SetBarrelColor(COLORREF color);
	void Render(void) const;
	void Place(float x, float y, float z = -0.1f);
	void FireProjectile(void);

	inline void RotateLeft(void)
	{
		angle += 1.0f;
		if (angle > 180)
			angle = 180;
	}
	inline void RotateRight(void)
	{
		angle -= 1.0f;
		if (angle < 0)
			angle = 0;
	}
	inline void ForceUp(float amount = 1.0f)
	{
		force += amount;
		if (force > MAX_FORCE)
			force = MAX_FORCE;
	}
	inline void ForceDown(float amount = 1.0f)
	{
		force -= amount;
		if (force < 0)
			force = 0;
	}

	inline void MassUp(void)
	{
		mass += 1.0f;
		if (force > MAX_FORCE)
			force = MAX_FORCE;
	}
	inline void MassDown(void)
	{
		mass -= 1.0f;
		if (force < 0)
			force = 0;
	}
	inline float GetAngle(void) const { return angle; }
	inline float GetForce(void) const { return force; }
	inline float GetMass(void) const { return mass; }
	inline float GetVelocity(void) const { return velocity; }
	inline float GetBarrelLength(void) const { return barrel_length; }
	inline void SetAngle(float ang) { angle = ang; }
	inline void SetBarrelLength(float len) { barrel_length = len; }

private:
	// The screen is 50 meters wide so we'll cap the projectile at 50 meters per second.
	enum { MAX_FORCE = 500, };

	struct rgb_value
	{
		BYTE red;
		BYTE green;
		BYTE blue;
	};
	
	float angle;							// The angle we are shooting
	float mass;								// The mass of 
	float force;							// The Newtons of Force.
	float velocity;							// The initial velocity that the cannonball is launched with.
	float base_width;						// The width the quad
	float base_height;						// The height of the quad
	Point3f barrel_position;				// Position of the barrel
	rgb_value barrel_color;					// Barrel color
	float barrel_length;					// Length of the barrel in meters
};

#endif
