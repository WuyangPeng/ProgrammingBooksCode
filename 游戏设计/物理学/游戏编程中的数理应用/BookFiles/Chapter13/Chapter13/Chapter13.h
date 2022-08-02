/////////////////////////////////////////////////////////////////////////
// Chapter13.h
// by Dustin Clingman  1/16/04
//
// Purpose: This library provides helper functions for working with collision and momentum
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#include "vectorLib.h"

#define GRAVITY 9.81
#define RESTITUTION 1

vector2D axisAlignedCollision(vector2D vect, char b);
vector2D nonAxisAlignedCollision(vector2D a, vector2D b);
vector3D nonAxisAlignedCollision(vector3D a, vector3D b, vector3D velocity);
float momentum(float velocity, float mass);
vector3D impulse3D (vector3D final, vector3D initial, float mass);
vector3D conserveMomentum(vector3D object1, vector3D object2, float mass1, float mass2);
void elasticCollision(vector3D object1, vector3D object2, float mass1, float mass2);

vector2D axisAlignedCollision(vector2D vect, char b)
    {
      vector2D temp = vect;

       if(b == 'v')
           temp.x = temp.x*= -1;
       else if(b =='h')
           temp.y = temp.y*= -1;
       
      return temp;
    }



vector2D nonAxisAlignedCollision(vector2D a, vector2D b)
    {
      vector2D temp,temp2,temp3,length,reflection;
      float projection;

      temp = normalizeVector(a);

      //reverse the vector. This should be made into a function.
      temp2 = scalarMultiply(-1,b);
      
      //find the project length using the dot product.
      projection = dotProduct(temp2,temp);

      length = scalarMultiply(projection,temp);

      //the reflection is going to be twice the length.
      reflection = scalarMultiply(2,length);

      //sum them all together making sure the reflection is inverted.
      temp3 = sumVectors(scalarMultiply(-1,reflection),temp2);

      //tada!!
      return temp3;
    }

vector3D nonAxisAlignedCollision(vector3D a, vector3D b,vector3D velocity)
    {
        vector3D temp,normal,velocityTemp,velocityFinal,length,reflection;

        velocityTemp = scalarMultiply(-1,velocity);        
        
        float projection;
        temp = crossProduct(a,b);

        //get the surface normal
        normal = normalizeVector(temp);

        //calculate the projection.
        projection = dotProduct(velocityTemp,normal);

        //Take the length of the projection against the normal.
        length = scalarMultiply(projection,normal);

        //Lets obtain the final vector.
        reflection = scalarMultiply(2,length);
        velocityFinal = sumVectors(reflection,velocity);
        return velocityFinal;


    }



float momentum(float velocity, float mass)
    {
      float momentum; 
      momentum = mass*velocity;
      return momentum;
    }
vector3D momentum3D(vector3D velocity, float mass)
    {
        vector3D temp;
        temp = scalarMultiply(mass,velocity);
        return temp;
    }

vector3D impulse3D (vector3D final, vector3D initial, float mass)
    {
        vector3D impulse,momentumFinal, momentumInitial;
        momentumFinal = momentum3D(final,mass);
        momentumInitial = momentum3D(initial,mass);
        impulse = subtractVectors(momentumFinal,momentumInitial);
        return impulse;
    }

vector3D conserveMomentum(vector3D object1Start,vector3D object1Stop, vector3D object2Start, float mass1, float mass2)
    {
        vector3D temp,temp2,sum,result;

        //First calculate the left hand side of the equation.
        temp  =  scalarMultiply(mass1,object1Start);
        temp2 =  scalarMultiply(mass2,object2Start);
        sum   =  sumVectors(temp,temp2);
        
        //Divide the left hand side by the second object's mass to get the vector;
        result = scalarDivide(mass2,sum);
        return result;
    }

void elasticCollision(vector2D object1, vector2D object2, float mass)
    {
        vector2D object1Temp,object2Temp, sum, sum2, object1Velocity,object2Velocity,temp;

        //First calculate the left hand side of the equation.
        object1Temp  =  scalarMultiply(mass,object1);
        object2Temp =  scalarMultiply(mass,object2);
        sum   =  sumVectors(object1Temp,object2Temp);

        //setup right side of equation; multiply through by restitution value.
        //This is only for illustration purposes in this example. 

        object1Temp = scalarMultiply(RESTITUTION,object1Temp);
        object2Temp = scalarMultiply(RESTITUTION,object2Temp);
    
        //for example purposes, since the equation switched to the right side. 
        object1Temp = scalarMultiply(-1,object1Temp);
        sum2 = sumVectors(object1Temp,object2Temp);

        //Now we have the two vectors we will need to complete the solution and 
        //calculate the vectors.
        temp = subtractVectors(sum,sum2);
        object2Velocity = scalarDivide(2,temp);

        object1Velocity = subtractVectors(sum,object2Velocity);

        //print the resulting velocities
        cout<<"The first object's resulting velocity vector is ";
        printVector(object1Velocity);
        cout<<"The second object's resulting velocity vector is \n";
        printVector(object2Velocity); 

    }


//End Chapter13.h