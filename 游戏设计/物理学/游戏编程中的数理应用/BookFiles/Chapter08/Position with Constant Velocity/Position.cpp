/////////////////////////////////////////////////////////////////////////
// Position.cpp
// by Dustin Clingman  1/14/04
//
// Purpose: This program demonstrates one way to calculate position
//		    where velocity is constant over a given time. 
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;


//This function will calculate the 1D displacement using a velocity and time in seconds.
float calcPosition(float position, float vel, float time);

int main()
{
    //local floats for holding our data from the user.   
	float currPosition, newPosition = 0.0f;
    float velocity     = 0.0f;
	float time         = 0.0f;

	cout<<"Welcome to The Amazing Position Calculator!\n";
    cout<<"With a constant velocity and a current position\n";
    cout<<"I can tell you where you will be in the future!\n";
    cout<<"\n";
	
    cout<<"Please enter a current position\n";
	cin>>currPosition;
    cout<<"\n";

    cout<<"Please enter a velocity\n";
	cin>>velocity;
    cout<<"\n";

	cout<<"Please enter a measure of time in seconds.\n";
	cout<<"\n";
    cin>> time;

	//calculate the new position.
    newPosition = calcPosition(currPosition, velocity, time);

	cout<<"The position from this input is calulated to be "<<newPosition;
    cout<<"\n";
    
return 0;
}


//Passing through floats for velocity and time we return the resulting position
//at the time specified.
float calcPosition(float oldPosition, float vel, float time)
    {
      return oldPosition + (vel*time);
    }

//end Position.cpp