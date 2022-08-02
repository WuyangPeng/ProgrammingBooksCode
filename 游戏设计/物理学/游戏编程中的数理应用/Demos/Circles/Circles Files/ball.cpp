// Ball.cpp //////////////////////////////////////////////////////////////////
//
// Implementation for the Ball class
//
//////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "ball.h"

// Define a MACRO for squaring a number since none is defined by windows
#define SQUARE(x) ((x) * (x))

extern HWND g_main_window_handle;	// The main window handle

//////////////////////////////////////////////////////////////////////////////
// Constructor for the ball
// Initialize the bounding rectangle and the vector of the ball
//////////////////////////////////////////////////////////////////////////////
Ball::Ball() 
{	
	// Get the bounds of the arena
	RECT cr;
	GetClientRect(g_main_window_handle, &cr);

	// Set the diameter of the ball randomly between 35 and 45
	diameter = (rand() % 10) + 35;

	// Set the bounding rectangle of the ball.
	// Make the top left corner random, within the range of the screen
	// and then set the bottom right corner based on the balls diameter
	bounds.left = (rand() % ((cr.right - 50) - (cr.left + 15) + 1)) + (cr.left + 15);
	bounds.top = (rand() % ((cr.bottom - 50) - (cr.top + 15) + 1)) + (cr.top + 15);
	bounds.right = bounds.left + diameter;
	bounds.bottom = bounds.top + diameter;
	
	// Set up the direction of the ball
	vector.cx = (rand() % 15) + 5;
	vector.cy = (rand() % 15) + 5;
}

//////////////////////////////////////////////////////////////////////////////
// move : Move the ball based on the vector of the ball
//////////////////////////////////////////////////////////////////////////////
void Ball::move() 
{
	// Advance the ball
	bounds.left += vector.cx;
	bounds.right += vector.cx;
	bounds.top += vector.cy;
	bounds.bottom += vector.cy;
}

//////////////////////////////////////////////////////////////////////////////
// show : Draw the ball on the screen
//
// In : hDC - The handle to the device context
//////////////////////////////////////////////////////////////////////////////
void Ball::show(HDC hDC)
{
	// Show the Ball
	Ellipse(hDC, bounds.left, bounds.top, bounds.right, bounds.bottom);
}

//////////////////////////////////////////////////////////////////////////////
// checkWallCollision : Check for a collision with the wall
//////////////////////////////////////////////////////////////////////////////
void Ball::checkWallCollision() 
{
	// Get the Client Rectangle
	RECT cr;
	GetClientRect(g_main_window_handle, &cr);

	// Check for collision with Top Wall
	if (bounds.top <= cr.top) 
	{
		// Reverse the Y vector
		vector.cy = -vector.cy;

		// Reset the bounding rectangle so the ball never appears outside of the screen
		bounds.top = cr.top + 1;
		bounds.bottom = bounds.top + diameter;
	}
	// Check for collision with Bottom Wall
	else if (bounds.bottom >= cr.bottom) 
	{
		// Reverse the Y vector
		vector.cy = -vector.cy;

		// Reset the bounding rectangle so the ball never appears outside of the screen
		bounds.bottom = cr.bottom - 1;
		bounds.top = bounds.bottom - diameter;
	}
	// Check for collision with Left Wall
	else if (bounds.left <= cr.left)
	{
		// Reverse the X vector
		vector.cx = -vector.cx;

		// Reset the bounding rectangle so the ball never appears outside of the screen
		bounds.left = cr.left + 1;
		bounds.right = bounds.left + diameter;
	}
	// Check for collision with Right Wall
	else if (bounds.right >= cr.right) 
	{
		// Reverse the X vector
		vector.cx = -vector.cx;

		// Reset the bounding rectangle so the ball never appears outside of the screen
		bounds.right = cr.right - 1;
		bounds.left = bounds.right - diameter;
	}
}

//////////////////////////////////////////////////////////////////////////////
// checkBallCollision : Check for a collision with another ball
//
// In : ball2 - the ball to check collision with
//
// Return : True if there was a collision with another ball
//////////////////////////////////////////////////////////////////////////////
bool Ball::checkBallCollision(Ball &ball2)
{
	// The radius of the balls
	int radius1 = diameter / 2;
	int radius2 = ball2.diameter / 2;
	
	// The center point of the first ball
	POINT center1;
	center1.x = radius1 + bounds.left;
	center1.y = radius1 + bounds.top;

	// The center point of the second ball
	POINT center2;
	center2.x = radius2 + ball2.bounds.left;
	center2.y = radius2 + ball2.bounds.top;
	
	// The distance between the two balls centers
	double distance = sqrt(SQUARE(center2.x - center1.x) + SQUARE(center2.y - center1.y));

	// See if they have collided
	if (distance <= radius1 + radius2)
	{
		// Find the distance between the x and the y values
		int xDistance = abs(center1.x - center2.x);
		int yDistance = abs(center1.y - center2.y);

		if (xDistance <= yDistance)
		// They collided on the top or bottom of the balls
		{
			if ((vector.cy > 0 && bounds.top < ball2.bounds.top) || 
				(vector.cy < 0 && bounds.top > ball2.bounds.top))
			// Ball1 was traveling downward and collided with the top of ball2,
			// or ball1 was traveling upward and collided with the bottom of ball2,
			// so we want to send ball1 back in the opposite Y direction
			{
				vector.cy = -vector.cy;
			}
			if ((ball2.vector.cy > 0 && ball2.bounds.top < bounds.top) || 
				(ball2.vector.cy < 0 && ball2.bounds.top > bounds.top))
			// Ball2 was traveling downward and collided with the top of ball1,
			// or ball2 was traveling upward and collided with the bottom of ball1,
			// so we want to send ball2 back in the opposite Y direction
			{
				ball2.vector.cy = -ball2.vector.cy;
			}
		}
		else if (xDistance > yDistance)
		// They collided on the left or right of the balls
		{
			if ((vector.cx > 0 && bounds.left < ball2.bounds.left) || 
				(vector.cx < 0 && bounds.left > ball2.bounds.left))
			// Ball1 was traveling right and collided with the left of ball2,
			// or ball1 was traveling left and collided with the right of ball2,
			// so we want to send ball1 back in the opposite X direction
			{
				vector.cx = -vector.cx;
			}
			if ((ball2.vector.cx > 0 && ball2.bounds.left < bounds.left) || 
				(ball2.vector.cx < 0 && ball2.bounds.left > bounds.left))
			// Ball2 was traveling right and collided with the left of ball1,
			// or ball2 was traveling left and collided with the right of ball1,
			// so we want to send ball2 back in the opposite X direction
			{
				ball2.vector.cx = -ball2.vector.cx;
			}
		}

		// There was a collision
		return true;
	}
	// No collision was detected
	return false;
}