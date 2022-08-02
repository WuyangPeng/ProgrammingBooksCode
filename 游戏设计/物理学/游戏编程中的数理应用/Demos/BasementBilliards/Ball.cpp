// Ball.cpp: implementation of the Ball class.
//
//////////////////////////////////////////////////////////////////////

#include "Ball.h"
#include <cmath>

// Constructor - initializing what needs to be initialized
Ball::Ball()
{
	x = y = velocity = vec[0] = vec[1] = vec[2] = nvec[0] = nvec[1] = nvec[2] = rotation = 0;
	spin[0] = spin[1] = evec[0] = evec[1] = evec[2] = 0;
	pocketed = false;
	rad = .12f;
}

// Checking to see if two circles collide by seeing if they distance between their centers is
// less than twice their radii
bool Ball::collision(Ball &b1)
{
	return (pow(x - b1.x, 2) + pow(y - b1.y, 2)) < (pow(2 * rad, 2) - .001);
}

// Swap the location of 2 balls.  Used to shuffle the balls on the intitial rack
void Ball::Swap(Ball& b)
{
	// Set a temp tp ball 1
	Ball temp = *this;
	// Set ball 1 to ball 2
	this->x = b.x;
	this->y = b.y;
	// Set ball 2 to the origianl ball 1
	b.x = temp.x;
	b.y = temp.y;
}	
