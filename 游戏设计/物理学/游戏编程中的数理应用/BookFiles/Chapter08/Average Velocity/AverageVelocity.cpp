/////////////////////////////////////////////////////////////////////////
// AverageVelocity.cpp
// by Dustin Clingman  1/14/04
//
// Purpose: This program demonstrates one way to calculate the average
//		    velocity over two points given the specified time. 
//          This program does not explicity use units, so refer back to the unit
//          conversion section in chapter 7 to add them to this example.
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

//this function will calculate our average velocity
float calcAvgVel(float start,float end, float time);

int main()
{
	float StartPos,EndPos;
	float velocity = 0.0f;
	float time = 0.0f;

	cout<<"Welcome to the Average Velocity Calculator!\n";
	cout<<"Please enter a Start Position\n";
    cout<<"\n";
	cin>>StartPos;

	cout<<"Please enter an Ending Position\n";
	cin>>EndPos;
    cout<<"\n";

    cout<<"Please enter a How much time it took to get there in seconds.\n";
	cin>> time;
    cout<<"\n";

	velocity = calcAvgVel(StartPos,EndPos,time);

	cout<<"Average Velocity from this input is calulated to be "<<velocity;
    cout<<"\n";

return 0;
}

//Passing through floats for velocity and time we return the resulting displacement.
float calcAvgVel(float start,float end, float time)
    {
      return (end - start)/ time;
    }


//end AverageVelocity.cpp