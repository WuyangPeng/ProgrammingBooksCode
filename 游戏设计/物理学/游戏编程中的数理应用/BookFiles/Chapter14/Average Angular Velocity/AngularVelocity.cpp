/////////////////////////////////////////////////////////////////////////
// AngularVelocity.cpp
// by Dustin Clingman  1/14/04
//
// Purpose: This program demonstrates one way to calculate the average
//		    angular velocity.
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "angularLib.h"
using namespace std;

//Prototypes 
void showSelection();
void AngularDisplacement();
void AvgAngularVelocity();
void AvgAngularAcceleration();
void TangentalVelocity();
void LinearSpeed();

int main()
{
    int choice;

    showSelection();
    cin>>choice;

    while(choice != 6)
    {
      switch(choice)
       {
           case 1:
                 AngularDisplacement();
                 break;
           case 2:
                 AvgAngularVelocity();
                 break;
           case 3:
                 AvgAngularAcceleration();
                 break;
           case 4:
                 TangentalVelocity();            
                 break;
           case 5:
                 LinearSpeed();
                 break;
           
           default:
           cout<<"That is not a valid selection, Please try again.";
           break;
       }
      showSelection();
      cin>>choice;
     }//end while

 return 0;
}

void showSelection()
     {
      cout<<"\n";
      cout<<"Welcome to the Circular Motion Calculator!\n";
      cout<<"Please select a calculation\n"; 
      cout<<"[1] Angular Displacement\n";
      cout<<"[2] Average Angular Velocity\n";
      cout<<"[3] Average Angular Acceleration\n";
      cout<<"[4] Tangential Velocity at a Point\n";
      cout<<"[5] Linear speed of a rolling object\n";
      cout<<"[6] Exit the program\n";
	  cout<<"\n";
    }

//Basic formula to determine the angular displacement.
 void AngularDisplacement()
     {
        float theta, arcLength, radius = 0.0f;

        cout<<"Angular Displacement!\n";
        cout<<"Please enter an arc length in meters\n";
        cout<<"\n";
        cin>>arcLength;

        cout<<"Please enter a radius in meters\n";
        cout<<"\n";
        cin>>radius;

        theta = angDisplacement(arcLength,radius);
        cout<<"The Angular displacement is "<<theta<<" radians\n";
        cout<<"\n";

     }
//calculate the average angular velocity.
 void AvgAngularVelocity()
     {
        float arcLengthStart,arcLengthEnd,time,radius = 0.0f;
        float omega = 0.0f;

        cout<<"Average Angular Displacement!\n";
        cout<<"Please enter a starting arc length in meters\n";
        cin>>arcLengthStart;

        cout<<"Please enter a ending arc length in meters\n";
        cin>>arcLengthEnd;

        cout<<"Please enter a radius in meters\n";
        cin>>radius;

        cout<<"Please enter a total time\n";
        cin>>time;

        //apply the formula.
        omega = avgAngularDisplacement(arcLengthStart, arcLengthEnd, time, radius);

        cout<<"The Average Angular Velocity is "<<omega<<" radians/second\n";
        cout<<"\n";
     }


 //calculate the average angular acceleration given a time interval.
 void AvgAngularAcceleration()
     {
       float alpha, initialAngVel, finalAngVel, time = 0.0f;

       cout<<"Average Angular Acceleration!\n";
       cout<<"Please enter a starting angular velocity in radians/second\n";
       cin>>initialAngVel;

       cout<<"Please enter a final angular velocity in radians/second\n";
       cin>>finalAngVel;

       cout<<"Please enter a total time\n";
       cin>>time;

        //calculate the angular acceleration over fixed time interval.
        alpha = (finalAngVel - initialAngVel)/time;
        cout<<"The Average Angular Acceleration is "<<alpha<<" radians/second^2\n";
        cout<<"\n";
     }
 //calculate the tangental velocity at a particular instant given omega and a radius
void TangentalVelocity()
    {
        float velT, omega, radius = 0.0f;

        cout<<"Tangental Velocity\n";
        cout<<"Please enter an instantaneous angular acceleration in radians/second\n";
        cin>>omega;

        cout<<"Please enter the radius of the arc in meters\n";
        cin>>radius;

        velT = tangVelocity(omega, radius);
        cout<<"The Tangental Velocity given these values is "<<velT<< " meters/second\n";
    }

//calculates the linear speed of a ball based on mass,inertia and height;
void LinearSpeed()
    {
     //lots of floats to play with.
     float mass,initialHeight,inertia,speed = 0.0f;

     cout<<"Lets calculate the linear speed of a rolling object!\n";
     cout<<"First, we need some information...\n";
     cout<<"Please specify a mass for the ball in kg\n";
     cin>>mass;
     cout<<"\n";
     cout<<"Next, please give us an intial height for the ball in meters\n";
     cin>>initialHeight;
     cout<<"\n";
     cout<<"Lastly, please give us an interia for the ball in mass moment per radius^2\n";
     cin>>inertia;
     cout<<"\n";
 
     speed = linearSpeed(mass,initialHeight,inertia);    
     cout<<"The final linear speed is "<<speed<< " meters/second\n";
  
    }
//end AngularVelocity.cpp