/////////////////////////////////////////////////////////////////////////
// vectorLib.h
// by Dustin Clingman  1/16/04
//
// Purpose: This library provides functions for working with Vectors
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

#define RadsToDegrees( radian ) ((radian) * (180.0f / M_PI))
#define DegreesToRads( degrees ) ((degrees) * (M_PI/ 180.0f))


typedef struct{ float x; float y;} vector2D;
typedef struct{ float x; float y; float z;} vector3D;


float sumVector(vector2D vect);
float sumVector(vector3D vect);

vector2D sumVectors(vector2D a,vector2D b);
vector3D sumVectors(vector3D a,vector3D b);

vector2D subtractVectors(vector2D a, vector2D b);
vector3D subtractVectors(vector3D a, vector3D b);

float squareVector(vector2D vect);
float squareVector(vector3D vect);

float dotProduct(vector2D a, vector2D b);
float dotProduct(vector3D a, vector3D b);

vector3D crossProduct(vector3D a, vector3D b);

vector2D polartoCartesian(vector2D vect);
vector2D cartesianToPolar(vector2D vect);
vector2D scalarMultiply(float scalar, vector2D vect);
vector3D scalarMultiply(float scalar, vector3D vect);

vector2D scalarDivide(float scalar, vector2D vect);
vector3D scalarDivide(float scalar, vector3D vect);

vector2D normalizeVector(vector2D vect);
vector3D normalizeVector(vector3D vect);

void printVector(vector2D vect);
void printVector(vector3D vect);

float sumVector(vector2D vect)
    {
      float temp = vect.x+vect.y;
      return temp;
    }
float sumVector(vector3D vect)
    {
      float temp = vect.x+vect.y+vect.z;
      return temp;
    }

vector2D sumVectors(vector2D a,vector2D b)
    {
      vector2D temp;
      temp.x = a.x+b.x;
      temp.y = a.y+b.y;
      return temp;
    }



vector3D sumVectors(vector3D a,vector3D b)
    {
      vector3D temp;
      temp.x = a.x+b.x;
      temp.y = a.y+b.y;
      temp.z = a.z+b.z;
      return temp;
    }


vector2D subtractVectors(vector2D a, vector2D b)
    {
      vector2D temp;
      temp.x = a.x-b.x;
      temp.y = a.y-b.y;
      return temp;
    }

vector3D subtractVectors(vector3D a, vector3D b)
    {
      vector3D temp;
      temp.x = a.x-b.x;
      temp.y = a.y-b.y;
      temp.z = a.z-b.z;
      return temp;
    }

float squareVector(vector2D vect)
    {
        float temp = pow(vect.x,2)+pow(vect.y,2);
        return temp;
    }

float squareVector(vector3D vect)
    {
      float temp = pow(vect.x,2)+pow(vect.y,2)+pow(vect.z,2);
      return temp;
    }

float dotProduct(vector2D a, vector2D b)
    {
        vector2D temp;
        float scalar;
        temp.x = a.x*b.x;
        temp.y = a.y*b.y;
        scalar = sumVector(temp);
        return scalar;
    }

float dotProduct(vector3D a, vector3D b)
    {
        vector3D temp;
        float scalar;
        temp.x = a.x*b.x;
        temp.y = a.y*b.y;
        temp.z = a.z*b.z;
        scalar = sumVector(temp);
        return scalar;
    }

vector3D crossProduct(vector3D a, vector3D b)
    {
      vector3D temp;
      temp.x =(a.y*b.z) - (a.z*b.y);
      temp.y =(a.z*b.x) - (a.x*b.z);
      temp.z =(a.x*b.y) - (a.y*b.x);
      return temp;
    }

vector2D polarToCartesian(vector2D vect)
    {
        //componentize the vector from Polar to Cartesian coordinates.
        vector2D temp;
        float a = DegreesToRads(vect.y);
        temp.x = (vect.x)*cos(a);
        temp.y = (vect.x)*sin(a);
        return temp;      
    }

vector2D cartesianToPolar(vector2D vect)
    {
        //componentize the vector from Cartesian to Polar coordinates.
        vector2D temp;
        float mag, direction;
        mag = sqrt( pow(vect.x,2)+pow(vect.y,2));
        direction = atan(vect.x/vect.y);
        temp.x = mag;
        temp.y = RadsToDegrees(direction);
        return temp;      
     }


vector2D scalarMultiply(float scalar, vector2D vect)
    {
     vector2D temp; 
     temp.x = vect.x*scalar;
     temp.y = vect.y*scalar;
     return temp;
    }

vector3D scalarMultiply(float scalar, vector3D vect)
    {
     vector3D temp; 
     temp.x = vect.x*scalar;
     temp.y = vect.y*scalar;
     temp.z = vect.z*scalar;
     return temp;
    }

vector2D scalarDivide(float scalar, vector2D vect)
    {
     vector2D temp; 
     temp.x = vect.x/scalar;
     temp.y = vect.y/scalar;
     return temp;
    }

vector3D scalarDivide(float scalar, vector3D vect)
 {
     vector3D temp; 
     temp.x = vect.x/scalar;
     temp.y = vect.y/scalar;
     temp.z = vect.z/scalar;
     return temp;
    }


vector2D normalizeVector(vector2D vect)
    {
       float mag,square;
       vector2D temp;
       square = squareVector(vect);
       mag = sqrt(square);
     
       temp.x = vect.x/mag;
       temp.y = vect.y/mag;
       return temp;
    }

vector3D normalizeVector(vector3D vect)
    {
       float mag,square;
       vector3D temp;
       square = squareVector(vect);
       mag = sqrt(square);
     
       temp.x = vect.x/mag;
       temp.y = vect.y/mag;
       temp.z = vect.z/mag;
       return temp;
    }

void printVector(vector2D vect)
    {
     cout<<"This vector is "<<vect.x<<" "<<vect.y;
     cout<<"\n";
    }

void printVector(vector3D vect)
    {
     cout<<vect.x<<" "<<vect.y<<" "<<vect.z<<"\n";
     cout<<"\n";
    }