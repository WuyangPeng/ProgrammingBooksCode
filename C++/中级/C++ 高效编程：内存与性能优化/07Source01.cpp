#include <iostream.h>
#include <ctime>

#include "BookTools.h"

#define N 50000000


int j =1;

long do_switch()
{
  long i=0, k=0;

  for (i = 0; i < N; i++)
  {
      switch(j)
      {
         case 1: k+=1;
                 break;
         case 2: k+=3;
                 break;
         case 3: k+=5;
                 break;
         case 4: k+=7;
                 break;
         case 5: k+=11;
                 break;
         case 6: k+=13;
                 break;
         case 7: k+=17;
                 break;
         case 8: k+=19;
                 break;
         case 9: k+=23;
                 break;
         default:k+=27;
                 break;
      }
  }
//  cout << "SWITCH K= " << k << endl;	
  return(k);
}

long do_ifelse()
{
  long i=0, k=0;

  for (i = 0; i < N; i++)
  {
      if (j==1)
         k+=1;
      else if (j == 2)
         k+=3;
      else if (j == 3)
         k+=5;
      else if (j == 4)
         k+=7;
      else if (j == 5)
         k+=11;
      else if (j == 6)
         k+=13;
      else if (j == 7)
         k+=17;
      else if (j == 8)
         k+=19;
      else if (j == 9)
         k+=23;
      else 
         k+=27;
  }
//  cout << "IF ELSE K= " << k << endl;	
  return(k);
}

int main()
{
 cout << "Selected   Switch     If Else\n";
 cout << "-----------------------------\n";
 for (j = 1; j < 10; j++)
 {
   cout << j << "          "<< time_fn(do_switch); 
   cout << "       " << time_fn(do_ifelse) << endl; 
 }
 j=10;
 cout << "Default     "<< time_fn(do_switch); 
 cout << "       " << time_fn(do_ifelse) << endl; 
 return(0);
}

