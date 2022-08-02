/////////////////////////////////////////////////////////////////////////
// Chapter12 Examples.cpp
// by Dustin Clingman  1/17/04
//
// Purpose: This program demonstrates calculations of work and potential energy
//
//////////////////////////////////////////////////////////////////////////

#include "Chapter12.h"

void showSelection();
void Work();
void AngledWork();
void AngledWorkVector();
void KineticEnergy();
void PotentialEnergy();
void WorkEnergy();


int main()
{
    int choice;

    showSelection();
    cin>>choice;

    while(choice != 9)
    {
      switch(choice)
       {
           case 1:
                 Work();
                 break;
           case 2:
                 AngledWork();
                 break;
           case 3:
                 AngledWorkVector();
                 break;
           case 4:
                 KineticEnergy();
                 break;
           case 5:
                 PotentialEnergy();
           case 6:
                 WorkEnergy();
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
      cout<<"Welcome to the Work calculator!\n";
      cout<<"Please make a selection\n";
      cout<<"[1] To calculate the work to move an object a given displacement\n";
      cout<<"[2] To calculate the work to move an object with angled forces\n";
      cout<<"[3] To calculate the work with Force and Displacement at different angles\n";
      cout<<"[4] To calculate kinetic energy.\n";
      cout<<"[5] To calculate potential energy.\n";
      cout<<"[6] To calculate an object's speed using the Work Energy Theorem.\n";
      cout<<"\n";
	  cout<<"Enter [9] to exit\n";
      cout<<"\n";
    }

void Work()
    {
      float force,friction,displacement,work;
      cout<<"Lets calculate the work done given a force,the friction and the displacement\n";
      cout<<"\n";

      cout<<"First input the force applied to the object in Newtons\n";
      cin>>force;

      cout<<"Next input the force applied to the object by friction\n";
      cin>>friction;

      cout<<"Now give the total displacement the object needs to travel in meters\n";
      cin>>displacement;

      work = calculateWork(force,friction,displacement);
      cout<<"The total work required to move the object this far is "<<work<<" Joules\n";
    }

void AngledWork()
    {
       vector2D force;
       float friction,displacement,work;
       cout<<"Lets calculate the work done given a force,the friction and the displacement\n";
       cout<<"\n";

       cout<<"First input the force applied to the object in Newtons\n";
       cin>>force.x;

       cout<<"Next input the angular direction of the force in degrees\n";
       cin>>force.y;

       cout<<"Now input the kinetic friction on the object in Newtons\n";
       cin>>friction;

       cout<<"Now give the total displacement the object needs to travel in meters\n";
       cin>>displacement;

       work = calculateAngledWork(force,friction,displacement);
       cout<<"The total work required to move the object this far is "<<work<<" Joules\n";
    }

void AngledWorkVector()
    {
       vector2D force,displacement;
       float work;
       cout<<"Lets calculate the work when force and displacement have different angles\n";
       cout<<"\n";

       cout<<"First input the magnitude of the force Vector in Newtons\n";
       cin>>force.x;

       cout<<"Next input the direction of the force Vector in Degrees\n";
       cin>>force.y;
       cout<<"\n";

       cout<<"Now input the magnitude of the displacement Vector in Newtons\n";
       cin>>displacement.x;

       cout<<"Next input the direction of the displacement Vector in degrees\n";
       cin>>displacement.y;

       work = calculateAngledWorkFromVector(force,displacement);
       cout<<"The amount of work to move the object is "<<work<<" Joules\n";
    }

void KineticEnergy()
    {
        float mass, speed,kineticEnergy;
        cout<<"Lets calculate the Kinetic Energy of an object based on speed and mass\n";
        cout<<"Enter a mass in kilograms\n";
        cin>>mass;

        cout<<"Enter a speed in m/s\n";
        cin>>speed;

        kineticEnergy = calculateKineticEnergy(mass,speed);
            
        cout<<"The Kinetic Energy is "<<kineticEnergy<< " Joules\n";
        cout<<"\n";
    }

void PotentialEnergy()
    {
        float mass, height,potentialEnergy;
        cout<<"Lets calculate the Potential Energy of an object based on mass and height\n";
        cout<<"Enter a mass in kilograms\n";
        cin>>mass;

        cout<<"Enter a height in meters\n";
        cin>>height;

        potentialEnergy = calculatePotentialEnergy(mass,height);
        cout<<"The Kinetic Energy is "<<potentialEnergy<< " Joules\n";
        cout<<"\n";
    }



void WorkEnergy()
    {
        float force, mass, displacement,work, velocity;

        cout<<"Lets calculate an object's speed using the Work Energy Theorem\n";
        cout<<"Please enter the force behind the object in Newtons\n";
        cin>>force;

        cout<<"Enter a mass in kilograms\n";
        cin>>mass;

        cout<<"Enter an initial velocity in meters/sec\n";
        cin>>velocity;

        cout<<"Enter a displacement to use for the calculation of the speed in meters\n";
        cin>>displacement;
        cout<<"\n";
            
        work = calculateWorkEnergy(force,mass,displacement,velocity);
        cout<<"The final speed using the Work Energy Theorem is "<<work<<" m/s\n";
    }
//End Chapter12 Examples.cpp
