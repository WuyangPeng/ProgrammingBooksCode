//  qsort.cpp
//  A C program illustrating how to declare your own
//  function and function pointer to be used with qsort( )
//  Chris H. Pappas and William H. Murray, 2000
//

#include <iostream>
#include <stdlib>

#define IMAXVALUES 10

int icompare_funct(const void *iresult_a, const void *iresult_b);
int (*ifunct_ptr)(const void *,const void *);

void main( )
{
  int i;
  int iarray[IMAXVALUES]={0,5,3,2,8,7,9,1,4,6};

  ifunct_ptr=icompare_funct;
  qsort(iarray,IMAXVALUES,sizeof(int),ifunct_ptr);
  for(i = 0; i < IMAXVALUES; i++)
    cout <<[{|"|}]" << iarray[i];
}

int icompare_funct(const void *iresult_a, const void *iresult_b)
{
  return((*(int *)iresult_a) - (*(int *)iresult_b));
}
