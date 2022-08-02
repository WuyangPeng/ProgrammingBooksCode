// Ball.h ////////////////////////////////////////////////////////////////////
//
// The Ball class contains all of the variables and methods needed to show
// a ball on the screen, move it around the screen, and check for a collision
// with a wall or another ball.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _BALL_H_
#define _BALL_H_

#include <windows.h>

class Ball
{
	private:
		int diameter;	// The size of the ball
		RECT bounds;	// Bounding rectangle for the ball
		SIZE vector;	// The direction the ball is traveling

	public:
		// Constructor for the ball
		// Initialize the bounding rectangle and the vector of the ball
		Ball();

		// Move the ball based on the vector of the ball
		void move();

		// Draw the ball on the screen
		//
		// In : hDC - The handle to the device context
		void show(HDC hDC);

		// Check for a collision with the wall
		void checkWallCollision();

		// Check for a collision with another ball
		//
		// In : ball2 - the ball to check collision with
		//
		// Return : True if there was a collision with another ball
		bool checkBallCollision(Ball &ball2);
		
		// The Destructor
		virtual ~Ball() {}
};

#endif