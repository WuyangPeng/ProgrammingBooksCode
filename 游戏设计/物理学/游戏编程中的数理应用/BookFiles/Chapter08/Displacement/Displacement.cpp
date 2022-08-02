/////////////////////////////////////////////////////////////////////////
// Displacement.cpp
// by Dustin Clingman  1/14/04
//
// Purpose: This program demonstrates one way to calculate displacement
//		    where velocity is constant. 
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;


//This function will calculate the displacement using a velocity and time in seconds.
float calcDisplacement(float vel, float time);

int main()
{
    //local floats for holding our data from the user.   
	float displacement = 0.0f;
	float velocity     = 0.0f;
	float time         = 0.0f;

	cout<<"Welcome to Displacement Calculation Central!\n";
	cout<<"Please enter a velocity\n";
	cin>>velocity;
	cout<<"Please enter a measure of time in seconds.\n";
	cin>> time;

	//calculate the displacement and return.
    displacement = calcDisplacement(velocity, time);

	cout<<"Displacement from this input is calulated to be "<<displacement;
    cout<<"\n";
    
return 0;
}

//Passing through floats for velocity and time we return the resulting displacement.
float calcDisplacement(float vel, float time)
    {
      return vel*time;
    }

//end Displacement.cpp