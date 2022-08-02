/////////////////////////////////////////////////////////////////////////
// TranslationDriver.cpp
// by Dustin Clingman  1/16/04
//
// Purpose: This program demonstrates several translation operations.
//
//////////////////////////////////////////////////////////////////////////

#include "TransformationLib.h"

void showSelection();
void translate3D();
void translate2DByMultiply();
void translate3DByMultiply();
void scale2D();
void scale3D();
void rotate2D();
void rotate3D();
void rotate2DFromOrigin();
void rotate3DAtOrigin();



int main()
{
    int choice;

    showSelection();
    cin>>choice;

    while(choice != 0)
    {
      switch(choice)
       {
           case 1:
                 translate3D();
                 break;
           case 2:
                 translate2DByMultiply();
                 break;
           case 3:
                 translate3DByMultiply();
                 break;
           case 4:
                 scale2D();
                 break;
           case 5:
                 scale3D();
                 break;
           case 6:
                 rotate2D();
                 break;
           case 7:
                 rotate3D(); 
                 break;
           case 8:
                 rotate2DFromOrigin();
                 break;
           case 9:
                 rotate3DAtOrigin();
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
      cout<<"Welcome to Translation Theme Park!\n";
      cout<<"Please select a Translation operation.\n"; 
      cout<<"[1] To translate a 3D point by addition.\n";
      cout<<"[2] To translate a 2D point using matrix multiplication.\n";
      cout<<"[3] To translate a 3D point using matrix multiplication.\n";
      cout<<"[4] To scale a 2D object.\n";
      cout<<"[5] To scale a 3D object.\n";
      cout<<"[6] To rotate a 2D object.\n";
      cout<<"[7] To rotate a 3D object.\n";
      cout<<"[8] To rotate a 2D object at the origin.\n";
      cout<<"[9] To scale a 3D object at the origin.\n";
	  cout<<"Enter [q] to exit\n";
      cout<<"\n";
    }

void translate3D()
     {
        int seed;
        char answer;
        Matrix3X1 trans, vertex1,vertex2,vertex3;
        cout<<"Lets translate a triangle!\n";
        cout<<"Would you like to use a random triangle? y/n\n";
        cin>>answer;
        if(answer == 'y')
          {
             cout<<"Please enter the seed for the random numbers\n";
             cin>>seed;
             vertex1 = createRandom3X1Matrix(seed);
             vertex2 = createRandom3X1Matrix(seed);
             vertex3 = createRandom3X1Matrix(seed);
             
             cout<<"The starting point for this matrix is: ";
             cout<<"Point 1\n";
             printMatrix(vertex1);
             cout<<"Point 2\n";
             printMatrix(vertex2);
             cout<<"Point 3\n";
             printMatrix(vertex3);
            }
        else
          {
            cout<<"Please enter the points for the triangle In the order XYZ.\n";
            cout<<"Point 1\n";
            cin>>vertex1.x[0];
            cin>>vertex1.x[1];
            cin>>vertex1.x[2];

            cout<<"Point 2\n";
            cin>>vertex2.x[0];
            cin>>vertex2.x[1];
            cin>>vertex2.x[2];

            cout<<"Point 3\n";
            cin>>vertex3.x[0];
            cin>>vertex3.x[1];
            cin>>vertex3.x[2];
          }//end if/else
           
            cout<<"Now enter the amount to translate by in XYZ.\n";
            cin>>trans.x[0];
            cin>>trans.x[1];
            cin>>trans.x[2];

        //Just reuse the temp to print out the new position
        cout<<"The new position of our triangle is: \n";
        
        Matrix3X1 temp = translate3DByAddition(vertex1,trans);
        cout<<"Point 1\n";
        printMatrix(temp);
        
        temp = translate3DByAddition(vertex2,trans);
        cout<<"Point 2\n";
        printMatrix(temp);

        temp = translate3DByAddition(vertex3,trans);
        cout<<"Point 3\n";
        printMatrix(temp);
     } 

void translate2DByMultiply()
    {
        Matrix3X1 start,temp;
        float dx,dy;
        cout<<"Let's translate a 2D postion using matrix multiplication!\n";
        cout<<"Please enter the coordinates of the current position X first, then Y.\n";
        cin>>start.x[0];
        cout<<"Now the Y coordinate\n";
        cin>>start.x[1];

        //make sure the last part of the matrix is a 1.
        start.x[2] = 1;
        cout<<endl;
        cout<<"Now enter the amount to translate by, X first then Y.\n";
        cin>>dx;
        cout<<"Now the Y component\n";
        cin>>dy;
        temp = translate2DByMultiplication(start,dx,dy);
        cout<<"The new position after translation is " <<temp.x[0]<<"," <<temp.x[1]<<"\n";

    }

void translate3DByMultiply()
    {
        Matrix4X1 start,temp;
        float dx,dy,dz;
        cout<<"Let's translate a 3D postion using matrix multiplication!\n";
        cout<<"Please enter the coordinates of the current position X first,Y, then Z.\n";
        cin>>start.x[0];
        cout<<"Now the Y coordinate\n";
        cin>>start.x[1];
        cout<<"Now the Z coordinate\n";
        cin>>start.x[2];

        //make sure the last part of the matrix is a 1.
        start.x[3] = 1;

        cout<<endl;
        cout<<"Now enter the amount to translate by, X first, Y, then Z.\n";
        cin>>dx;
        cout<<"Now the Y component\n";
        cin>>dy;
        cout<<"Now the Z component\n";
        cin>>dz;
        temp = translate3DByMultiplication(start,dx,dy,dz);
        cout<<"The new position after translation is " <<temp.x[0]<<"," <<temp.x[1]<<","<<temp.x[2]<<"\n";

    }

void scale2D()
    {
        Matrix3X1 start,temp;
        float dx,dy, height,width;
        cout<<"Let's uniformly scale a 2D rectangular using matrix multiplication!\n";
        cout<<"Please enter the coordinates and dimensions the rectangle.\n";
        cout<<"X coordinates\n";
        cin>>start.x[0];
        cout<<"Now the Y coordinate.\n";
        cin>>start.x[1];
        cout<<"Enter the rectangle's height.\n";
        cin>>height;
        cout<<"Enter the rectangle's width.\n";
        cin>>width;
                

        //make sure the last part of the matrix is a 1.
        start.x[2] = 1;
        cout<<endl;
        cout<<"Now enter the amount to scale by.\n";
        cin>>dx;
        dy = dx;
        
        temp = scale2DByMultiplication(start,dx,dy);

        width = temp.x[0]+width;
        height = temp.x[1]+height;

        cout<<"The new position after translation is "<<temp.x[0]<<","<<temp.x[1]<<"\n";
        cout<<"The right coordinate of the rectangle is "<<width<<","<<temp.x[1]<<"\n";
        cout<<"The bottom coordiante of the rectangle is "<<height<<","<<temp.x[0]<<"\n";
       }

void scale3D()
    {
        float seed,dx,dy,dz;
        char answer;
        Matrix4X1 trans, vertex1,vertex2,vertex3;
        cout<<"Lets uniformly scale a triangle!\n";
        cout<<"Would you like to use a random triangle? y/n\n";
        cin>>answer;
        if(answer == 'y')
          {
             cout<<"Please enter the seed for the random numbers\n";
             cin>>seed;
             vertex1 = createRandom4X1Matrix(seed);
             vertex1.x[3] = 1;
             vertex2 = createRandom4X1Matrix(seed);
             vertex2.x[3] = 1;
             vertex3 = createRandom4X1Matrix(seed);
             vertex3.x[3] = 1;
             
             cout<<"The starting point for this matrix is: ";
             cout<<"Point 1\n";
             printMatrix(vertex1);
             cout<<"Point 2\n";
             printMatrix(vertex2);
             cout<<"Point 3\n";
             printMatrix(vertex3);
            }
        else
          {
            cout<<"Please enter the points for the triangle In the order XYZ.\n";
            cout<<"Vertex 1\n";
            cin>>vertex1.x[0];
            cin>>vertex1.x[1];
            cin>>vertex1.x[2];
            vertex1.x[3] = 1;

            cout<<"Vertex 2\n";
            cin>>vertex2.x[0];
            cin>>vertex2.x[1];
            cin>>vertex2.x[2];
            vertex2.x[3] = 1;


            cout<<"Vertex 3\n";
            cin>>vertex3.x[0];
            cin>>vertex3.x[1];
            cin>>vertex3.x[2];
            vertex3.x[3] = 1;
          }//end if/else
           
            cout<<"Now enter the amount to scale by in XYZ.\n";
            cout<<"X scale\n";
            cin>>dx;
            cout<<"Y scale\n";
            cin>>dy;
            cout<<"Z scale\n";
            cin>>dz;
            cout<<"\n";

        trans = scale3DByMultiplication(vertex1,dx,dy,dz);
        cout<<"The new position of vertex one is "<<trans.x[0]<<","<<trans.x[1]<<","<<trans.x[2]<<"\n";
        cout<<"\n";
        
        trans = scale3DByMultiplication(vertex2,dx,dy,dz);
        cout<<"The new position of vertex one is "<<trans.x[0]<<","<<trans.x[1]<<","<<trans.x[2]<<"\n";
        cout<<"\n";

        trans = scale3DByMultiplication(vertex3,dx,dy,dz);
        cout<<"The new position of vertex one is "<<trans.x[0]<<","<<trans.x[1]<<","<<trans.x[2]<<"\n";
        cout<<"\n";


    }


void rotate2D()
    {
        Matrix3X1 start,temp;
        float height,width,theta;
        cout<<"Let's rotate a 2D!\n";
        cout<<"Please enter the coordinates and dimensions the rectangle.\n";
        cout<<"X coordinates\n";
        cin>>start.x[0];
        cout<<"Now the Y coordinate.\n";
        cin>>start.x[1];
        cout<<"Enter the rectangle's height.\n";
        cin>>height;
        cout<<"Enter the rectangle's width.\n";
        cin>>width;
                
        //make sure the last part of the matrix is a 1.
        start.x[2] = 1;
        cout<<endl;
        cout<<"Now enter the amount to rotate by in degrees.\n";
        cin>>theta;
                
        temp = rotate2D(start,theta);

        width = temp.x[0]+width;
        height = temp.x[1]+height;

        cout<<"The new position after rotation is "<<temp.x[0]<<","<<temp.x[1]<<"\n";
        cout<<"The right coordinate of the rectangle is "<<width<<","<<temp.x[1]<<"\n";
        cout<<"The bottom coordiante of the rectangle is "<<height<<","<<temp.x[0]<<"\n";
    }

void rotate2DFromOrigin()
    {

        Matrix3X1 point1,point2,point3,point4;
        float x,y,theta,length,temp;
        cout<<"Let's rotate a squre around the origin in 2D using a combo matrix!\n";
        cout<<"Please enter the coordinates representing the center of our object.\n";
        cout<<"X coordinates\n";
        cin>>x;
        cout<<"Now the Y coordinate.\n";
        cin>>y;             
        cout<<"\n";
        cout<<"Enter the length of the square's side.\n";
        cin>>length;

        //use this to figure out the rest of the points to be rotated.
        temp = length/2;

        cout<<"Now enter the amount to rotate by in degrees.\n";
        cin>>theta;

        
        point1 = rotate2DAtOrigin(x-temp,y-temp,theta);
        point2 = rotate2DAtOrigin(x+temp,y-temp,theta);
        point3 = rotate2DAtOrigin(x+temp,y+temp,theta);
        point4 = rotate2DAtOrigin(x-temp,y+temp,theta);

        cout<<"The new position of point 1 after rotation is "<<point1.x[0]<<","<<point1.x[1]<<"\n";
        cout<<"The new position of point 2 after rotation is "<<point2.x[0]<<","<<point2.x[1]<<"\n";
        cout<<"The new position of point 3 after rotation is "<<point3.x[0]<<","<<point3.x[1]<<"\n";
        cout<<"The new position of point 4 after rotation is "<<point4.x[0]<<","<<point4.x[1]<<"\n";
        
    }

void rotate3D()
    {
        int seed,choice;
        float theta;
        char answer;
        Matrix4X1 trans, vertex1,vertex2,vertex3;
        cout<<"Lets rotate a triangle!\n";
        cout<<"Would you like to use a random triangle? y/n\n";
        cin>>answer;
        if(answer == 'y')
          {
             cout<<"Please enter the seed for the random numbers\n";
             cin>>seed;
             vertex1 = createRandom4X1Matrix(seed);
             vertex1.x[3] = 1;
             vertex2 = createRandom4X1Matrix(seed);
             vertex2.x[3] = 1;
             vertex3 = createRandom4X1Matrix(seed);
             vertex3.x[3] = 1;
             
             cout<<"The starting point for this matrix is: ";
             cout<<"Vertex 1\n";
             printMatrix(vertex1);
             cout<<"Vertex 2\n";
             printMatrix(vertex2);
             cout<<"Vertex 3\n";
             printMatrix(vertex3);
            }
        else
          {
            cout<<"Please enter the points for the triangle In the order XYZ.\n";
            cout<<"Point 1\n";
            cin>>vertex1.x[0];
            cin>>vertex1.x[1];
            cin>>vertex1.x[2];
            vertex1.x[3] = 1;

            cout<<"Point 2\n";
            cin>>vertex2.x[0];
            cin>>vertex2.x[1];
            cin>>vertex2.x[2];
            vertex2.x[3] = 1;

            cout<<"Point 3\n";
            cin>>vertex3.x[0];
            cin>>vertex3.x[1];
            cin>>vertex3.x[2];
            vertex2.x[3] = 1;
          }//end if/else
           

        cout<<"Now that we have our triangle, which axis will we rotate with respect to?\n";
        cout<<"Please enter the number corresponding to your choice.\n";
        cout<<"[1] To rotate about the x-axis.\n";
        cout<<"[2] To rotate about the y-axis.\n";
        cout<<"[3] To rotate about the z-axis.\n";
        cin>>choice;
        cout<<"\n";

        switch(choice)
              {
                case 1:
                  cout<<"Please enter the amount by which to rotate in degrees.\n";
                  cin>>theta;
                  trans = rotate3DX(vertex1,theta);
                  cout<<"Vertex 1\n";
                  printMatrix(trans);
                  trans = rotate3DX(vertex2,theta);
                  cout<<"Vertex 2\n";
                  printMatrix(trans);
                  trans = rotate3DX(vertex3,theta);
                  cout<<"Vertex 3\n";
                  printMatrix(trans);
                  break;
                case 2:
                  cout<<"Please enter the amount by which to rotate in degrees.\n";
                  cin>>theta;
                  trans = rotate3DY(vertex1,theta);
                  cout<<"Vertex 1\n";
                  printMatrix(trans);
                  trans = rotate3DY(vertex2,theta);
                  cout<<"Vertex 2\n";
                  printMatrix(trans);
                  trans = rotate3DY(vertex3,theta);
                  cout<<"Vertex 3\n";
                  printMatrix(trans);
                  break;
                case 3:
                  cout<<"Please enter the amount by which to rotate in degrees.\n";
                  cin>>theta;
                  trans = rotate3DZ(vertex1,theta);
                  cout<<"Vertex 1\n";
                  printMatrix(trans);
                  trans = rotate3DZ(vertex2,theta);
                  cout<<"Vertex 2\n";
                  printMatrix(trans);
                  trans = rotate3DZ(vertex3,theta);
                  cout<<"Vertex 3\n";
                  printMatrix(trans);
                  break;
                  default:
                  cout<<"That is not a valid selection, Please try again.";
                  break;
                }

          cout<<"\n";
    }


 void rotate3DAtOrigin()
     {

        int seed;
        float thetax,thetay,thetaz;
        char answer;
        Matrix4X1 trans, vertex1,vertex2,vertex3;
        Matrix4X4 combo;
        cout<<"Lets rotate a triangle from the origin!\n";
        cout<<"Would you like to use a random triangle? y/n\n";
        cin>>answer;
        if(answer == 'y')
          {
             cout<<"Please enter the seed for the random numbers\n";
             cin>>seed;
             vertex1 = createRandom4X1Matrix(seed);
             vertex1.x[3] = 1;
             vertex2 = createRandom4X1Matrix(seed);
             vertex2.x[3] = 1;
             vertex3 = createRandom4X1Matrix(seed);
             vertex3.x[3] = 1;
             
             cout<<"The starting point for this matrix is: ";
             cout<<"Vertex 1\n";
             printMatrix(vertex1);
             cout<<"Vertex 2\n";
             printMatrix(vertex2);
             cout<<"Vertex 3\n";
             printMatrix(vertex3);
            }
        else
          {
            cout<<"Please enter the points for the triangle In the order XYZ.\n";
            cout<<"Point 1\n";
            cin>>vertex1.x[0];
            cin>>vertex1.x[1];
            cin>>vertex1.x[2];
            vertex1.x[3] = 1;

            cout<<"Point 2\n";
            cin>>vertex2.x[0];
            cin>>vertex2.x[1];
            cin>>vertex2.x[2];
            vertex2.x[3] = 1;

            cout<<"Point 3\n";
            cin>>vertex3.x[0];
            cin>>vertex3.x[1];
            cin>>vertex3.x[2];
            vertex2.x[3] = 1;
          }//end if/else
           

        cout<<"Now that we have our triangle, please apply the amount of rotation for each axis in degrees.\n";
        cout<<"[1] X-axis?\n";
        cin>>thetax;
        cout<<"[2] Y-axis?\n";
        cin>>thetay;
        cout<<"[3] Z-axis?\n";
        cin>>thetaz;
    
        //create the combo matrix.
        combo = createRotationCombo(thetax,thetay,thetaz);

        trans = rotate3DWithCombo(combo,vertex1);
        cout<<"The new position of vertex 1 after rotation is "<<trans.x[0]<<","<<trans.x[1]<<","<<trans.x[2]<<"\n";
        
        trans = rotate3DWithCombo(combo,vertex2);
        cout<<"The new position of vertex 2 after rotation is "<<trans.x[0]<<","<<trans.x[1]<<","<<trans.x[2]<<"\n";
        
        trans = rotate3DWithCombo(combo,vertex3);
        cout<<"The new position of vertex 3 after rotation is "<<trans.x[0]<<","<<trans.x[1]<<","<<trans.x[2]<<"\n";
        cout<<"\n";
      }


//End TranslationDriver.cpp