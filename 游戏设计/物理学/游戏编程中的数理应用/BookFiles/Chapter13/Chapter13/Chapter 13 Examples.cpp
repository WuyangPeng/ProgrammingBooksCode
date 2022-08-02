/////////////////////////////////////////////////////////////////////////
// Chapter 13 Examples.cpp
// by Dustin Clingman  1/17/04
//
// Purpose: This program demonstrates calculations of collision and momentum
//
//////////////////////////////////////////////////////////////////////////

#include "Chapter13.h"

void showSelection();
void AxisAlignedReflection();
void NonAxis2D();
void NonAxis3D();
void Momentum();
void Momentum3D();
void Impulse();
void ConserveMomentum();
void ElasticCollision();

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
                 AxisAlignedReflection();
                 break;
           case 2:
                 NonAxis2D();
                 break;
           case 3:
                 NonAxis3D();
                 break;
           case 4:
                 Momentum();
                 break;
           case 5:
                 Momentum3D();
                 break;
           case 6:
                 Impulse();
                 break;
           case 7:
                 ConserveMomentum();
                 break;
           case 8:
                 ElasticCollision();
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
      cout<<"Welcome to the Collision and Momentum calculator!\n";
      cout<<"Please make a selection.\n";
      cout<<"[1] To calculate the work to move an object a given displacement.\n";
      cout<<"[2] To calculate a non axis aligned 2D collision.\n";
      cout<<"[3] To calculate a non axis aligned 3D collision.\n";
      cout<<"[4] To calculate an object's momentum.\n";
      cout<<"[5] To calculate a 3D object's momentum.\n";
      cout<<"[6] To calculate a 3D object's impulse.\n";
      cout<<"[7] To calculate a resulting velocity vector via the Conservation of Momentum.\n";
      cout<<"[8] To calculate velocity vectors from two object with the same mass via\n";
      cout<<"   elastic collision.\n";
      cout<<"\n";
	  cout<<"Enter [9] to exit\n";
      cout<<"\n";
    }

 void NonAxis2D()
     {
       float x1,x2,y1,y2; 
       vector2D boundary, object1,result;

       cout<<"Lets calculate the reflection vector of a non-axis aligned collision.\n";
       cout<<"First input points that describe the boundary line\n";
       cout<<"X2\n";
       cin>>x2;

       cout<<"Y2\n";
       cin>>y2;

       cout<<"X1\n";
       cin>>x1;

       cout<<"Y1\n";
       cin>>y1;
       cout<<"\n";

       boundary.x = x2-x1;
       boundary.y = y2-y1;
            
       cout<<"Now input the vector that decribes the incoming object\n";
       cout<<"X\n";
       cin>>object1.x;

       cout<<"Y\n";
       cin>>object1.y;
       result = nonAxisAlignedCollision(boundary,object1);
       cout<<"The resulting velocity vector is \n";
       printVector(result);
     }

void NonAxis3D()
     {
       float x1,x2,y1,y2,z1,z2; 
       vector3D boundary1,boundary2, object1,result;

       cout<<"Lets calculate the reflection vector of a non-axis aligned collision.\n";
       cout<<"First input points that describe the boundary plane line\n";
       cout<<"X2\n";
       cin>>boundary2.x;

       cout<<"Y2\n";
       cin>>boundary2.y;

       cout<<"Z2\n";
       cin>>boundary2.z;

       cout<<"X1\n";
       cin>>boundary1.x;

       cout<<"Y1\n";
       cin>>boundary1.y;
       
       cout<<"Z1\n";
       cin>>boundary1.z;
       cout<<"\n";

       cout<<"Now input the vector that decribes the incoming object\n";
       cout<<"X\n";
       cin>>object1.x;

       cout<<"Y\n";
       cin>>object1.y;

       cout<<"Z\n";
       cin>>object1.z;

       result = nonAxisAlignedCollision(boundary1,boundary2,object1);
       cout<<"The resulting velocity vector is \n";
       printVector(result);
     }

void AxisAlignedReflection()
    {
     vector2D temp, result;
     char answer;

     cout<<"Lets determine the reflection against an axis aligned object\n";
     cout<<"\n";
     cout<<"Please enter the x component of the velocity\n";
     cin>>temp.x;

     cout<<"Please enter the y component of the velocity\n";
     cin>>temp.y;

     cout<<"Please indicate if the axis aligned object is\n";
     cout<<"(h)orizontal or (v)ertically aligned\n";
     cin>>answer;
     if(answer == 'h' ||answer == 'v')
         {
          result = axisAlignedCollision(temp,answer);
          cout<<"The resulting reflection is ";
          printVector(result);
         }
     else
        cout<<"Please enter an h or v for the alignement\n";
    }


void Momentum()
    {
       float mass,velocity,result;
       cout<<"lets calculate the momentum of an object!\n";
       cout<<"Please enter the object's mass in kilograms\n";
       cin>>mass;
       cout<<"Please enter the velocity in meters/second\n";
       cin>>velocity;

       result = momentum(velocity,mass);
       cout<<"The total momentum of this object is "<<result<<" kg/meters.second\n";
    }

void Momentum3D()
    {
       vector3D temp, result;
       float mass;
       cout<<"lets calculate the momentum of a 3D object!\n";
       cout<<"Please enter the object's mass in kilograms\n";
       cin>>mass;

       cout<<"Please enter the velocity vector components\n";
       cout<<"Enter x\n"; 
       cin>>temp.x;
       cout<<"Enter y\n";
       cin>>temp.y;
       cout<<"Enter z\n";
       cin>>temp.z;

       result = momentum3D(temp,mass);
       cout<<"The momentum vector of this object is ";
       printVector(result);
    }
void Impulse()
    {
       vector3D initial,final,result;
       float mass;
       cout<<"lets calculate the impulse of a 3D object!\n";
       cout<<"Please enter the object's mass in kilograms\n";
       cin>>mass;

       cout<<"Please enter the initial velocity vector components\n";
       cout<<"Enter x\n"; 
       cin>>initial.x;
       cout<<"Enter y\n";
       cin>>initial.y;
       cout<<"Enter z\n";
       cin>>initial.z;

       cout<<"Please enter the final velocity vector components\n";
       cout<<"Enter x\n"; 
       cin>>final.x;
       cout<<"Enter y\n";
       cin>>final.y;
       cout<<"Enter z\n";
       cin>>final.z;

       result = impulse3D(final,initial,mass);
       cout<<"The impulse of this object is ";
       printVector(result);
    }
void ConserveMomentum()
    {
       vector3D object1, stopped, result;
       float mass,mass2;

       cout<<"Lets calculate the velocity resulting from the collision of two 3D objects!\n";
       cout<<"For this example, the first object is in motion and comes to rest\n";
       cout<<"The second object conserves the momentum. The resultant velocity vector\n";
       cout<<"will describe the second object's velocity after the collision\n";
       cout<<"\n";
       cout<<"Please enter the first object's mass in kilograms\n";
       cin>>mass;

       cout<<"Please enter the first object's velocity vector components\n";
       cout<<"Enter x\n"; 
       cin>>object1.x;
       cout<<"Enter y\n";
       cin>>object1.y;
       cout<<"Enter z\n";
       cin>>object1.z;

       //The stopped vector used in our calculation. It represents the 
       //ending velocity for object1 and the starting velocity for object2.
       stopped.x=0;stopped.y=0;stopped.z =0;

       cout<<"Please enter the second object's mass in kilograms\n";
       cin>>mass2;
       cout<<"Since this object is at rest, it's initial vector is 0 0 0\n";
       
       result = conserveMomentum(object1,stopped,stopped,mass,mass2);
       
       cout<<"The velocity vector of object 2 is ";
       printVector(result);    
    }


void ElasticCollision()
    {
       vector2D object1,object2;
       float mass;

       cout<<"Lets calculate the velocity resulting from the collision of two 3D objects!\n";
       cout<<"For this example, both objects are in motion. Both have the same mass.\n";
       cout<<"\n";
       cout<<"Please enter the mass of both object in kilograms\n";
       cin>>mass;

       cout<<"Please enter the first object's initial velocity vector components\n";
       cout<<"Enter x\n"; 
       cin>>object1.x;
       cout<<"Enter y\n";
       cin>>object1.y;       

       cout<<"Please enter the second object's initial velocity vector components\n";
       cout<<"Enter x\n"; 
       cin>>object2.x;
       cout<<"Enter y\n";
       cin>>object2.y;

       elasticCollision(object1,object2,mass);    
    }
//End Chapter13 Examples.cpp