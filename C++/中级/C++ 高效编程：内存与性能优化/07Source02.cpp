#include <iostream.h>
#include <ctime>

#include "BookTools.h"


#define N 50000000


int j =1;

long aa()
{
	return(1);
}
long bb()
{
	return(3);
}
long cc()
{
	return(5);
}
long dd()
{
	return(7);
}
long ee()
{
	return(11);
}
long ff()
{
	return(13);
}
long gg()
{
	return(17);
}
long hh()
{
	return(19);
}
long ii()
{
	return(23);
}
long jj()
{
	return(27);
}

long do_switch()
{
  long i=0, k=0;

  for (i = 0; i < N; i++)
  {
      switch(j)
      {
         case 1: k+=aa();
                 break;
         case 2: k+=bb();
                 break;
         case 3: k+=cc();
                 break;
         case 4: k+=dd();
                 break;
         case 5: k+=ee();
                 break;
         case 6: k+=ff();
                 break;
         case 7: k+=gg();
                 break;
         case 8: k+=hh();
                 break;
         case 9: k+=ii();
                 break;
         default:k+=jj();
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
         k+=aa();
      else if (j == 2)
         k+=bb();
      else if (j == 3)
         k+=cc();
      else if (j == 4)
         k+=dd();
      else if (j == 5)
         k+=ee();
      else if (j == 6)
         k+=ff();
      else if (j == 7)
         k+=gg();
      else if (j == 8)
         k+=hh();
      else if (j == 9)
         k+=ii();
      else 
         k+=jj();
  }
//  cout << "IF ELSE K= " << k << endl;	
  return(k);
}

long do_jumptable()
{
// Initialisation (only once!!)
	typedef long (*fn)();
	fn table[10] = {aa, bb, cc, dd, ee, ff, gg, hh, ii, jj};
        long i=0, k=0;

	  for (i = 0; i < N; i++)
		k+=table[j-1]();      // Jumptable is zero-based!!
  
//  cout << "JUMP TABLE K= " << k << endl;	
  return(k);
}

int main()
{

 cout << "Selected   Switch     If Else    Jump Table\n";
 cout << "-------------------------------------------\n";
 for (j = 1; j < 10; j++)
 {
   cout << j << "          "<< time_fn(do_switch); 
   cout << "       " << time_fn(do_ifelse); 
   cout << "       " << time_fn(do_jumptable) << endl; 
 }
 j=10;
 cout << "Default     "<< time_fn(do_switch); 
 cout << "       " << time_fn(do_ifelse); 
 cout << "       " << time_fn(do_jumptable) << endl; 
 return(0);
}

