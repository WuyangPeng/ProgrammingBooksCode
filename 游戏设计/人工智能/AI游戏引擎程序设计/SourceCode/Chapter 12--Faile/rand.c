/*
MIT License

Copyright (c) 2000 Adrien M. Regimbald

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**************************************************
 * Random Number Facility                         *
 * Author: Adrien Regimbald                       *
 * E-mail: adrien@ee.ualberta.ca                  *
 * Web Page: http://www.ee.ualberta.ca/~adrien/   *
 *                                                *
 * File: rand.c                                   *
 * Purpose: provide functions to generate 32-bit  *
 * random numbers, as well as a testing function  *
 * to indicate how well the numbers are being     *
 * generated.                                     *
 **************************************************/

#include "rand.h"

long int ran_num = 1;

void rand_test (long int max) {

  /* perform a test of our random number generator.  Mean value is mapped
     to the range 0 -> 1, and thus we aim for a mean of 0.500000.  The
     standard deviation we are aiming for is 1/sqrt(12) ~=  0.288675 */

  float list[LIST_BUFF+1], mean, std_dev, sum = 0, sum_sq = 0;
  unsigned long int holder;
  long int i;
  FILE *output;

  if (max > LIST_BUFF || max <= 0) {
    fprintf (stderr, "Please choose size in range: "
	     "0 < size <= %d!\n", LIST_BUFF);
    exit (EXIT_FAILURE);
  }

  if ((output = fopen ("out.dat", "w")) == NULL) {
    fprintf (stderr, "Couldn't open file out.dat!\n");
  }

  srand (173);

  for (i = 1; i <= max; i++) {
    holder = rand_32 ();
    fprintf (output, "%10lu ", holder);
    if (!(i%5) && i)
      fprintf (output, "\n");
    list[i] = (float) holder/0xffffffff;
    sum += list[i];
    sum_sq += list[i]*list[i];
  }

  mean = sum/max;
  printf ("Mean Value: %f\n", mean);

  if (max > 1) {
    std_dev = sqrt ((sum_sq - max*(mean*mean))/(max-1));
    printf ("Standard Deviation: %f\n", std_dev);
  }
  else {
    printf ("Standard Deviation: N/A\n");
  }

  fclose (output);

}


void init_simple_rand (unsigned long int seed) {

  /* intitialize our generator */

  ran_num = seed;

}


int rand_255 (void) {

  /* return a random number between 0 and 255 */

  long int temp = 256;

  while (temp > 255) {
    temp = simple_rand ();
    temp %= 257;
  }

  return temp;

}


unsigned long int rand_32 (void) {

  /* return a 32 bit random number */

  int x1, x2, x3, x4;
  long int temp;

  x1 = rand_255 ();
  x2 = rand_255 ();
  x3 = rand_255 ();
  x4 = rand_255 ();

  temp = x1+(x2<<8)+(x3<<16)+(x4<<24);

  return temp;

}


unsigned long int simple_rand (void) {

  /* simple method of generating random numbers */

  ran_num = ran_num*1103515245 + 12345;
  return (unsigned long int) (ran_num/65536) % 32768;

}
