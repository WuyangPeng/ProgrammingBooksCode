#ifndef DEFINES_H
#define DEFINES_H



//------------------------------------------------------------------
//
//	general defines
//------------------------------------------------------------------
#define WINDOW_WIDTH				400	
#define WINDOW_HEIGHT				400

#define FRAMES_PER_SECOND		60

#define	PI						      3.14159265358979
#define HALF_PI				      PI/2
#define TWO_PI			      	PI*2

//------------------------------------------------------------------
//
//	defines used in CLander
//------------------------------------------------------------------
#define SHIPS_MASS            100

#define THRUST_PER_SECOND     350.0
#define ROTATION_PER_SECOND   3.0

//approx gravity on moon
#define GRAVITY               -1.63

#define LANDER_SCALE          10

//used to scale the physics so the game 'feels' right
#define SCALING_FACTOR        60


//this is how close to level the lander has to be when landing
//to satisfy the landing criteria
#define ROTATION_TOLERANCE     PI/16

//this is the maximum speed the ship can be travelling at 
//to satisfy the landing criteria
#define SPEED_TOLERANCE        0.5

//the is the maximum distance from the center of the landing pad
//the ship must be to satisfy the landing criteria
#define DIST_TOLERANCE         10





#endif