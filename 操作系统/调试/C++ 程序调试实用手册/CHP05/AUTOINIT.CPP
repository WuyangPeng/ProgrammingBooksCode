//
// autoinit.cpp
// Program demonstrating auto-initialization
// of local variables
// Chris H. Pappas and William H. Murray, 2000
//

#include <stdio.h>

void myFuncA(char **ppszString)
{
   /* output uninitialized ppszString address in hex       */
   printf("*ppszString = 0x%X\n", *ppszString);
   if(*ppszString == NULL)
      *ppszString = "/GZ option ACTIVE";
}
void myFuncB()
{
   int memBuff[25];      /* uninitiailzed internal variable */
   char * pszString;     /* uninitialized memBuff pointer   */

   myFuncA(&pszString);
   puts(pszString);      /* dangerous - attempts to print   */
}                        /* myFuncA allocated string!!!     */

void main( void )
{
   int memBuff[ 1000 ];  /* stack page - cleared            */
   myFuncB( );
}
