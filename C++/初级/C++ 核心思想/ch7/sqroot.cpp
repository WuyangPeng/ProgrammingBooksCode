#include <iostream>
#include <cmath>

using namespace std;

int main()
{  
   cout << "Please enter a number: ";
   double a;
   cin >> a;
   
   const double EPSILON = 1E-14;
   double xnew = a;
   double xold;

   do
   {  
      xold = xnew;
      xnew = (xold + a / xold) / 2;
   }
   while (fabs(xnew - xold) > EPSILON);

   cout << "The square root is " << xnew << "\n";
   return 0;
}


