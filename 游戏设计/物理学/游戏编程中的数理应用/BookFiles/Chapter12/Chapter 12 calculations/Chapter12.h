/////////////////////////////////////////////////////////////////////////
// Chapter12.h
// by Dustin Clingman  1/16/04
//
// Purpose: This library provides functions for working with Matrices
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;
#include "vectorLib.h"

#define GRAVITY 9.81

float calculateWork(float force, float displacement);
float calculateWork(float force, float friction, float displacement);
float calculateAngledWork(vector2D vect, float friction);
float calculateAngledWorkFromVector(vector2D initial, vector2D change);
float calculateKineticEnergy(float mass, float speed);
float calculatePotentialEnergy(float mass,float height);
float calculateWorkEnergy(float force, float mass, float displacement);

float calculateWork(float force, float friction, float displacement)
    {
        //calculate the difference of the forces and multiply by displacement
        float netForce = force-friction;
        float temp = displacement*netForce;
        return temp;
    }

float calculateWork(float force, float displacement)
    {
        float temp = displacement*force;
        return temp;
    }

float calculateAngledWork(vector2D vect, float friction,float displacement)
    {
        float temp;
        //don't forget to convert to rads....
        temp = cos(DegreesToRads(vect.y));
        
        //calculate the horizontal force;
        float horizForce = vect.x*temp;
        
        float work = calculateWork(horizForce,friction,displacement);
        return work;
    }

float calculateAngledWorkFromVector(vector2D initial, vector2D change)
    {
        vector2D force, displacement,displacementNormal, temp;
        float projectionLength, work;
        
        //change vectors from Polar to Cartesian coordinates. Remember, most math.h trig functions take radian arguments.
        force = polarToCartesian(initial);
        displacement = polarToCartesian(change);

        //Normalize the displacementNormal
        displacementNormal = normalizeVector(displacement);
     
        //the length of the project is is the dot product of the force against the displacement normal.
        projectionLength = dotProduct(force,displacementNormal);

        //Lets see what that length is.
        cout<<"Projection Length "<< projectionLength<<"\n";

        //multiply projection times normalized displacement Vector
        temp = scalarMultiply(projectionLength,displacementNormal);
        
        //Get back to Polar coordinates to calculate work. Don't forget about radians.
        temp = cartesianToPolar(temp);
        
        //Finally, our work is calculated.
        work = temp.x * change.x;
        return work;   
        
    }

float calculateKineticEnergy(float mass, float speed)
    {
        float KE;
        KE = (mass/2)*(pow(speed,2));
        return KE;
    }

float calculatePotentialEnergy(float mass,float height)
    {
      float PE;
      PE = mass*GRAVITY*height;
      return PE;
    }




float calculateWorkEnergy(float force, float mass, float displacement,float velocityInitial)
    {
      float work,velocityFinal;
      work = calculateWork(force,displacement);
      velocityFinal = work/((mass/2) - calculateKineticEnergy(mass, velocityInitial));
      velocityFinal = sqrt(velocityFinal);
      return velocityFinal;
    }

  