// Ball.h: interface for the Ball class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _BALL_H_
#define _BALL_H_

#include <gltools.h>
#include "3ds.h"

// The Ball class
class Ball  
{
private:
	// Holds the ball's number
	int number;
	// It's location and radius
	float x, y, rad;
	// How fast it's travelling
	float velocity;
	// It's direction of travel, the normal to that vector in the xy plane, respectively
	GLT_VECTOR3 vec, nvec, evec;
	// The amount of english
	GLT_POINT2 spin;
	// True if the ball has been pocketed
	bool pocketed;
	// The current rotation of the ball
	float rotation;
public:

	// Let's our main loop touch our privates
	friend class OGL_Wrapper;
	// Constructor 
	Ball();
	// Destructor, no dynamic memory equals no clean up
	virtual ~Ball() { }

	// Checking to see if two circles collide by seeing if they distance between their centers is
	// less than twice their radii
	bool collision(Ball &b1);

	// Swap the location of 2 balls.  Used to shuffle the balls on the intitial rack
	void Swap(Ball& b);

	// Our various access functions
	inline void setXY(float ex, float why) { x = ex; y = why; }
	inline float getX() const { return x; }
	inline float getY() const { return y; }
	inline void setX(float ex) { x = ex; }
	inline void setY(float why) { y = why; }
	inline void setRad(float r) { rad = r; }
	inline int getNumber() const { return number; }
	inline float getVel() const { return velocity; }
	inline void setVel(float v) { velocity = v; }
};

#endif 
