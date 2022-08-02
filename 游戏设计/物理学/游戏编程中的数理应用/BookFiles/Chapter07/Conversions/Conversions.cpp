/////////////////////////////////////////////////////////////////////////
// Conversions.cpp
// by Dustin Clingman  1/14/04
//
// Purpose: This program demonstrates mathematical conversion important to physics 
//
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "conversionsLib.h"
using namespace std;

//Prototypes of available conversions. 
void showSelection();
void convertAccel();
void convertTime();
void convertDistance();
void convertSpeed();


int main()
{
    char choice;

    showSelection();
    cin>>choice;

    while(choice != 'q')
    {
      switch(choice)
       {
           case 'a':
                 convertAccel();
                 break;
           case 'd':
                 convertDistance();
                 break;
           case 's':
                 convertSpeed();
                 break;
           case 't':
                 convertTime();
                 break;
           default:
           cout<<"That is not a valid selection, Please try again.";
           break;
       }
      showSelection();
      cin>>choice;
     }//end while

 cout<<"Thanks for converting units!\n";
 return 0;
}

void showSelection()
     {
      cout<<"\n";
      cout<<"Welcome to Unit Conversion Calculator!\n";
      cout<<"Please select a conversion\n"; 
      cout<<"[a]cceleration from mph^2 to m/s^2\n";
      cout<<"[d]istance from mile to meters\n";
      cout<<"[s]peed from mph to m/s\n";
      cout<<"[t]ime days to seconds\n";
      cout<<"Please enter q to quit\n";
	  cout<<"\n";
    }

 //Convert acceleration in miles/sec to meters/sec.
 void convertAccel()
     {
        float accelMiles,accelMeters;

        cout<<" Acceleration Conversion!\n";
        cout<<" Please enter an acceleration in miles per hour^2.\n";
        cin>>accelMiles;

        accelMeters = convertAccelMilesToMeters(accelMiles);

        cout<< "The Converted acceleration is "<<accelMeters<< "meters/second squared\n";
        cout<<"\n";
     }

 //Convert Days to Seconds.
 void convertTime()
     {
        float numDays, numSeconds;

        cout<<" Time Conversion!\n";
        cout<<" Please enter a number of days to convert to seconds.\n";
        cin>>numDays;

        numSeconds = convertDaysToSeconds(numDays);
        
        cout<<" The converted days are equal to " <<numSeconds<<"seconds\n";     
     }
 
 //Convert distance in Miles to Meters.
 void convertDistance()
     {
        float distanceMiles;
        float distanceMeters;

        cout<<" Distance Conversion!\n";
        cout<<" Please enter a distance in miles.\n";
        cin>>distanceMiles;

        distanceMeters = convertMilesToMeters(distanceMiles);

        cout<<" The converted distance is "<<distanceMeters<<" meters\n";
      
     }
 
 //Convert MPH to m/s
 void convertSpeed()
     {
        float speedMPH,speedMeters;

        cout<<"Speed Conversion!\n";
        cout<<"Please Enter a speed in Miles Per Hour.\n";
        cin>>speedMPH;

        speedMeters = convertSpeed(speedMPH);
        cout<<"The converted speed is "<<speedMeters<<" m/s\n";          
     }
//end Conversions.cpp