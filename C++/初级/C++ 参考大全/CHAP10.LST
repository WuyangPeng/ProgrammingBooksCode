listing 1
#include <stdio.h>  #include <stdlib.h>

listing 2
#define LEFT 1
#define RIGHT 0

listing 3
printf("%d %d %d", RIGHT, LEFT, LEFT+1);

listing 4
#define ONE    1 
#define TWO    ONE+ONE
#define THREE  ONE+TWO

listing 5
#define E_MS "standard error on input\n"
/* ... */
printf(E_MS);

listing 6
printf("standard error on input\n");

listing 7
#define XYZ this is a test

printf("XYZ");

listing 8
#define LONG_STRING "this is a very long \
string that is used as an example"

listing 9
#define MAX_SIZE 100
/* ... */
float balance[MAX_SIZE];
/* ... */
for(i=0; i<MAX_SIZE; i++) printf("%f", balance[i]);
/* ... */
for(i=0; i<MAX_SIZE; i++) x =+ balance[i];

listing 10
#include <stdio.h>

#define ABS(a)  (a)<0 ? -(a) : (a)

int main(void)
{
  printf("abs of -1 and 1: %d %d", ABS(-1), ABS(1));

  return 0;
}

listing 11
ABS(10-20)

listing 12
10-20<0 ? -10-20 : 10-20

listing 13
#include "stdio.h"
#include <stdio.h>

listing 14
/* Simple #if example. */
#include <stdio.h>

#define MAX 100

int main(void)
{
#if MAX>99
  printf("Compiled for array greater than 99.\n");
#endif

  return 0;
}

listing 15
/* Simple #if/#else example. */
#include <stdio.h>

#define MAX 10

int main(void)
{
#if MAX>99
  printf("Compiled for array greater than 99.\n");
#else
  printf("Compiled for small array.\n");
#endif 

  return 0;
}

listing 16
#define US 0 
#define ENGLAND 1
#define JAPAN 2

#define ACTIVE_COUNTRY US

#if ACTIVE_COUNTRY == US
  char currency[] = "dollar";
#elif ACTIVE_COUNTRY == ENGLAND
  char currency[] = "pound";
#else
  char currency[] = "yen";
#endif

listing 17
#if MAX>100
  #if SERIAL_VERSION
    int port=198;
  #elif
    int port=200;
  #endif
#else
  char out_buffer[100];
#endif

listing 18
#include <stdio.h>

#define TED 10

int main(void)
{
#ifdef TED
  printf("Hi Ted\n");
#else
  printf("Hi anyone\n");
#endif
#ifndef RALPH
  printf("RALPH not defined\n");
#endif

  return 0;
}

listing 19
#define LEN 100
#define WIDTH 100

char array[LEN][WIDTH];

#undef LEN
#undef WIDTH
/* at this point both LEN and WIDTH are undefined */

listing 20
#if defined MYFILE

listing 22
#if !defined DEBUG
  printf("Final version!\n");
#endif

listing 23
#include <stdio.h>

#line 100                  /* reset the line counter */
int main(void)            /* line 100 */
{                          /* line 101 */
  printf("%d\n",__LINE__); /* line 102 */

  return 0;
}

listing 24
#include <stdio.h>

#define mkstr(s)  # s

int main(void)
{
  printf(mkstr(I like C++));

  return 0;
}

listing 25
printf(mkstr(I like C++));

listing 26
printf("I like C++");

listing 27
#include <stdio.h>

#define concat(a, b)  a ## b

int main(void)
{
  int xy = 10;

  printf("%d", concat(x, y));

  return 0;
}

listing 28
printf("%d", concat(x, y));

listing 29
printf("%d", xy);

listing 30
#include <stdio.h>

int main(void)
{
  printf("hello");
  /* printf("there"); */

  return 0;
}

listing 31
/* this is a
multi-line
comment */

listing 32
x = 10+ /* add the numbers */5;

listing 33
swi/*this will not work*/tch(c) { ...

listing 34
/* this is an outer comment
  x = y/a;
  /* this is an inner comment - and causes an error */
*/

listing 35
// this is a single-line comment

