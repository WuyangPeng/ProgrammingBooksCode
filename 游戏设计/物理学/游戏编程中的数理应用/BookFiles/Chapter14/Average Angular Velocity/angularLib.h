/////////////////////////////////////////////////////////////////////////
// AngularLib.h
// by Dustin Clingman  1/16/04
//
// Purpose: This file contains the angular related calculation functions.
//
//////////////////////////////////////////////////////////////////////////

#include <math.h>

#define GRAVITY 9.81

//prototypes
float angDisplacement(float arc, float radius);
float avgAngularDisplacement(float arcStart, float arcEnd, float time, float radius);
float tangVelocity(float omega, float radius);
float avgAngAcceleration(float angVelBegin, float angVelEnd, float time);

float angDisplacement(float arc, float radius)
    {
      float theta;
      theta = arc/radius;
      return theta;

    }

float avgAngularDisplacement(float arcStart, float arcEnd, float time, float radius)
    {
     float initialDisplacement, endDisplacement,omega;

      //calculate the angular displacement.
      initialDisplacement = arcStart/radius;
      endDisplacement = arcEnd/radius;
    
      //apply the formula.
      omega = (endDisplacement - initialDisplacement) / time;
      return omega;
    }

float tangVelocity(float omega, float radius)
    {
      float velT;
      velT = omega*radius;
      return velT;
    }


float avgAngAcceleration(float angVelBegin, float angVelEnd, float time)
    {
      float alpha;
      alpha = (angVelEnd - angVelBegin)/time;
      return alpha;
    }
float linearSpeed(float mass, float height, float inertia)
    {
     float energy,halfMass,halfInertiaMass, linearSpeed, temp;

     //first figure out what is known for sure.
     energy = mass*height*GRAVITY;
     
     //this term is used to hold the reduced math equivalent of 1/2(m)vf^2
     halfMass = mass/2;

     //this term hold on to the reduced formula equivalent of 1/2(inertia)*(mass) r^2 * [omega]f^2
     halfInertiaMass = inertia*mass/2;

     //make a holding place.
     temp = energy/(halfMass+halfInertiaMass);
     
     //take the square root to find the speed in m/s
     linearSpeed = sqrt(temp);
     return linearSpeed;
    }