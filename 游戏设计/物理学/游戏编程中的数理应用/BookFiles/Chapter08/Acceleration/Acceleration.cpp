/////////////////////////////////////////////////////////////////////////
// Acceleration.cpp
// by Dustin Clingman  1/14/04
//
// Purpose: This program demonstrates one way to calculate acceleration and decceleration
//		    over a given time interval.
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

float calcAccelerationSeconds( float startVel, float finalVel, float time);
float calcAccelerationHours( float startVel, float finalVel, float time);

int main()
{
    //local floats for holding our data from the user.   
	float acceleration = 0.0f;
	float velocityInitial, velocityFinal = 0.0f;
	float time = 0.0f;

	cout<<"Welcome to The Acceleration Calculator!\n";
	cout<<"Please enter an initial velocity in Miles per Hour\n";
	cin>>velocityInitial;
    cout<<"\n";

    cout<<"Please enter an final velocity in Miles per Hour\n";
	cin>>velocityFinal;
    cout<<"\n";

	cout<<"Please enter a measure of time in seconds.\n";
	cin>> time;

	//calculate the displacement and return.
    acceleration = calcAccelerationSeconds(velocityInitial,velocityFinal, time);

    cout<<"Acceleration is "<<acceleration<< " Miles/Second^2.";
    cout<<"\n";

    acceleration = calcAccelerationHours(velocityInitial,velocityFinal, time);
    cout<<"Acceleration is "<<acceleration<<" Miles/Hour^2.";
    cout<<"\n";
    
return 0;
}

//This function will calculate the acceleration in seconds.
float calcAccelerationSeconds( float startVel, float finalVel, float time)
    {

        return (finalVel-startVel)/time;
    }

//This function will calculate the acceleration in hours
float calcAccelerationHours( float startVel, float finalVel, float time)
    {
        float hourTime;
        hourTime = time/3600;

        return (finalVel-startVel)/hourTime;
    }




//end Acceleration.cpp