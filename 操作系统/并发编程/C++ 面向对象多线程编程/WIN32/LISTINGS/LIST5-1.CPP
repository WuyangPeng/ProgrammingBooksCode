// Listing 5-1
// Demonstrates the use of command line
// arguments

#include <iostream.h>
#include "mtration.h"
#include <stdlib.h>

void main(int argc, char *argv[])
{

   if(argc == 5){
     try{
	  mt_rational X(atol(argv[1]),atol(argv[2]));
	  mt_rational Y(atol(argv[3]),atol(argv[4]));
	  cout << X + Y;
     }
     catch(general_exception &X)
     {
       cout << X.message() << endl;
     }
   }

}

