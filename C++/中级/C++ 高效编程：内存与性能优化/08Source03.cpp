
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include "BookTools.h"


template <class T>
unsigned long Count(T *array, T  test, unsigned int n)
{
  unsigned long cnt =0;
  for (unsigned int i = 0; i < n; i++)
    if (array[i] == test)
      cnt++;
  return (cnt);
}        

unsigned long CountLong(long *array, long  test, unsigned int n)
{
  unsigned long cnt =0;
  for (unsigned int i = 0; i < n; i++)
    if (array[i] == test)
      cnt++;
  return (cnt);
}        

unsigned long CountChar(char *array, char  test, unsigned int n)
{
  unsigned long cnt =0;
  for (unsigned int i = 0; i < n; i++)
    if (array[i] == test)
      cnt++;
  return (cnt);
}        


long Template()
{
  long result = 0;  
  long x[10] = {0, 1, 1, 2, 3, 4, 1, 2, 3, 1};
  char *a = "This is a test string";
  
  for (int i = 0; i < 2000000; i++)
  {
    result+= Count(a, 's', strlen(a));  
    result+= Count(x, 1L, 10);  
  }
  return(result);
}

long NoTemplate()
{
  long result = 0;  
  long x[10] = {0, 1, 1, 2, 3, 4, 1, 2, 3, 1};
  char *a = "This is a test string";
  
  for (int i = 0; i < 2000000; i++)
  {
    result+= CountChar(a, 's', strlen(a));  
    result+= CountLong(x, 1L, 10);  
  }
  return(result);
}



template <class T>
inline void Swap(T &x,  T  &y)
{
  T w = x;
  x = y;
  y = w;
}        

inline void UniversalSwap(void **x,  void  **y)
{
  void *w = *x;
  *x = *y;
  *y = w;
}        

template <class UST>
inline void TSwap(UST &x, UST &y)
{
	UniversalSwap((void **)&x, (void **)&y);
}


long SwapTemplate()
{
  int		x=1,     y=2;
  double	xx=1.1,   yy=2.2;
  char		*xxx = "One",   *yyy = "Two";
  
  //printf("x,y    : %d,%d\nxx,yy  : %f,%f\nxxx,yyy:  %s,%s\n", x, y, xx, yy, xxx, yyy);
  
  for (long i = 0; i <= 20000000; i++)
  {
    Swap(x, y);
    Swap(xx, yy);
    Swap(xxx, yyy);
  }
  //printf("x,y    : %d,%d\nxx,yy  : %f,%f\nxxx,yyy:  %s,%s\n", x, y, xx, yy, xxx, yyy);
	
  return(0);
}

long SwapNoTemplate()
{
  int		x=1,     y=2;
  double	xx=1.1,   yy=2.2;
  char		*xxx = "One",   *yyy = "Two";
  
  int		*p = &x,   *q = &y;
  double	*pp = &xx,   *qq = &yy;
  char		**ppp = &xxx,   **qqq = &yyy;
  
  //  printf("p,q    : %d,%d\npp,qq  : %f,%f\nppp,qqq:  %s,%s\n", *p, *q, *pp, *qq, *ppp, *qqq);
  for (long i = 0; i <= 20000000; i++)
  {
    UniversalSwap((void **)&p,(void **)&q);
    UniversalSwap((void **)&pp,(void **)&qq);
    UniversalSwap((void **)&ppp,(void **)&qqq);
  }
  //printf("p,q    : %d,%d\npp,qq  : %f,%f\nppp,qqq:  %s,%s\n", *p, *q, *pp, *qq, *ppp, *qqq);
  return(0);
}

long SwapFakeTemplate()
{
  int		x=1,     y=2;
  double	xx=1.1,   yy=2.2;
  char		*xxx = "One",   *yyy = "Two";
  
  int		*p = &x,   *q = &y;
  double	*pp = &xx,   *qq = &yy;
  char		**ppp = &xxx,   **qqq = &yyy;
  
  //  printf("p,q    : %d,%d\npp,qq  : %f,%f\nppp,qqq:  %s,%s\n", *p, *q, *pp, *qq, *ppp, *qqq);
  for (long i = 0; i <= 20000000; i++)
  {
    TSwap(p,q);
    TSwap(pp,qq);
    TSwap(ppp,qqq);
  }
//  printf("p,q    : %d,%d\npp,qq  : %f,%f\nppp,qqq:  %s,%s\n", *p, *q, *pp, *qq, *ppp, *qqq);
  return(0);
}


template <int N> 
class Fact 
{
	  public:
		enum { retval = N * Fact<N-1>::retval };
};

class Fact<1>
{
  public:
	enum { retval = 1 };
};

inline long fact1(int n)
{
   if (n == 0)
       return(1);
   else 
       return(n * fact1(n -1));
}
    
long fact2(int n)
{
  int x = n;
  int prod = 1;

  while ( x > 0)
  {
     prod = x * prod;
     x--;
  }
  return(prod);
}

long TimeFact1()
{
  long x;
  for (long i = 0; i <= 2000000; i++)
  {
	  x = Fact<12>::retval;
  }
//  printf("Result = %ld\n", x);
  return(0);
}

long TimeFact2()
{
  for (long i = 0; i <= 2000000; i++)
  {
    fact1(12);
  }
  return(0);
}

long TimeFact3()
{
  for (long i = 0; i <= 2000000; i++)
  {
    fact2(12);
  }
  return(0);
}


/**************************************************/
void main(int argc, char *argv)
{
	for(;;)
	{
		cout << "Fact Template     : " << time_fn(TimeFact1) << endl;
		cout << "Fact Recursive    : " << time_fn(TimeFact2) << endl;
		cout << "Fact Iterated     : " << time_fn(TimeFact3) << endl;

		cout << "SWAP Template     : " << time_fn(SwapTemplate) << endl;
		cout << "SWAP NO Template  : " << time_fn(SwapNoTemplate) << endl;
		cout << "SWAP Fake Template: " << time_fn(SwapFakeTemplate) << endl;
	}
}
