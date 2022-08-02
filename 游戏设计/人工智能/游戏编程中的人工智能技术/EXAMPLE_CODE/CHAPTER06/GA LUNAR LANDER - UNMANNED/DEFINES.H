#ifndef DEFINES_H
#define DEFINES_H

//-----------------------------------------------------------------------
//  
//  Name: defines.h
//  
//  Author: Mat Buckland 2002
//
//  Desc: all the #defines for the Lunar Lander code project
//
//------------------------------------------------------------------------


//------------------------------------------------------------------
//
//	general defines
//------------------------------------------------------------------
#define WINDOW_WIDTH				400	
#define WINDOW_HEIGHT				400

#define BIG_NUMBER          9999999

#define FRAMES_PER_SECOND		60

#define	PI						      3.14159265358979
#define HALF_PI				      PI/2
#define TWO_PI			      	PI*2

//------------------------------------------------------------------
//
//	defines used in CLander
//------------------------------------------------------------------

//maximim amount of frames an action may be undertaken
#define MAX_ACTION_DURATION   30

#define SHIPS_MASS            100.0

//approx gravity on moon
#define GRAVITY               -1.63 
#define THRUST                350.0
#define ROTATION              3.0

#define GRAVITY_PER_TICK      GRAVITY/FRAMES_PER_SECOND
#define THRUST_PER_TICK       THRUST/FRAMES_PER_SECOND
#define ROTATION_PER_TICK     ROTATION/FRAMES_PER_SECOND


#define LANDER_SCALE          10


//this is how close to level the lander has to be when landing
//to satisfy the landing criteria
#define ROTATION_TOLERANCE     PI/16

//this is the maximum speed the ship can be travelling at 
//to satisfy the landing criteria
#define SPEED_TOLERANCE        0.5

//the is the maximum distance from the center of the landing pad
//the ship must be to satisfy the landing criteria
#define DIST_TOLERANCE         10.0


//--------------------------------------------------------------------
//	
//	defines used in the genetic algorithm
//--------------------------------------------------------------------
#define POP_SIZE              100
#define CHROMO_LENGTH         30

#define MUTATION_RATE				  0.01
#define CROSSOVER_RATE				0.7

//used for elitism
#define NUM_ELITE             4
#define NUM_COPIES_ELITE      1

//this is the maximum amount of time the duration
//of an action can be altered by the mutation operator
#define MAX_MUTATION_DURATION MAX_ACTION_DURATION/2

//number of genomes to randomly choose and compare in
//standard tournament selection
#define NUM_TO_COMPARE  5

//maximum amount of generations the ga is allowed to run before
//restarting
#define MAX_GENERATIONS_ALLOWED 500



#endif