 /* '02 Main.cpp' */

 /* Input output stream header file */
#include <iostream>
 /* C++ math header file */
#include <math.h>

 /* Use definitions so you don't need to worry what value is which
    table */
#define COSTABLE 0
#define SINTABLE 1
#define TANTABLE 2

 /* Define PI */
#define PI 3.14159

 /* Start */
main (void)
{
  /* Declare look up table */
 double Table [3][360]; /* 360 elements for all angles between 0 and 
              359 times three for cosine, sine 
              and tangent */
 int Number;

  /* Calculate look up tables */
 std::cout << "Calculating look up tables..." << std::endl;

 for (Number = 0; Number < 360; Number++)
 {
  Table [COSTABLE] [Number] = cos (Number * PI / 180);
  Table [SINTABLE] [Number] = sin (Number * PI / 180);

   /* Check if number is different than 90 since tan (90) is not
      valid */
  if (Number != 90)
  {
   Table [TANTABLE] [Number] = tan (Number * PI / 180);
  }
 }

  /* Print cosine, sine and tangent of ten random values */
 for (Number = 0; Number < 10; Number++)
 {
  int TempNumber = rand () % 360;
  std::cout << "Number = " << TempNumber;
  std::cout << "  cos = " << Table [COSTABLE] [TempNumber];
  std::cout << "  sin = " << Table [SINTABLE] [TempNumber];
  std::cout << "  tan = " << Table [TANTABLE] [TempNumber] << std::endl;
 }
 return 0;
}