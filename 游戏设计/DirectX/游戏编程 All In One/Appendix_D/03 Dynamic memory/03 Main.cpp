 /* 03 Main.cpp */

 /* Standard Input/Output */
#include <stdio.h>
 /* Standard library */
#include <stdlib.h>


void main ()
{
 short CurrentValue;
 short *Values;

  /* Allocate memory */
 Values = (short *) malloc (sizeof (Values) * 5);

  /* Enter some values to the array */
 for (CurrentValue = 0; CurrentValue < 5; CurrentValue++)
 {
  Values [CurrentValue] = CurrentValue * CurrentValue;
 }

  /* Go through every element and output it */ 
 for (CurrentValue = 0; CurrentValue < 5; CurrentValue++)
 {
  printf ("%d\n", Values [CurrentValue]);
 }

  /* Free allocated memory */
 free (Values);
}