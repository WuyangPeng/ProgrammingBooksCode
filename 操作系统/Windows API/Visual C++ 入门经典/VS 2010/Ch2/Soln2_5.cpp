// Ex2_5.cpp
#include <iostream>
using std::cout;
using std::endl;

/*
 You have to figure out what the following code does:

   unsigned s = 555;

   int i = (s >> 4) & ~(~0 << 3);
   cout << i;

   The expression (s >> 4) shifts the bits in s right 4 positions so the result is the
   same as s/16, which is 34. 34 in binary is 
   
   0000 0000 0000 0000 0000 0000 0100 0010

   The expression ~0 flips all the bits in 0 so the result is a word containing all 1 bits:

   1111 1111 1111 1111 1111 1111 1111 1111

   The expression (~0 << 3) shifts a word that is all 1 bits left by three bit positions
   because the ~ operator is of higher precedence than << and therefore executes first.
   The result of this expression is:

   1111 1111 1111 1111 1111 1111 1111 1000

   You should now see that ~(~0 >> 3) flips all the bits in the binary number above so
   the result is:

   0000 0000 0000 0000 0000 0000 0000 0111

   Finally the expression (s >> 4) & ~(~0 << 3) combines the first binary value with the binary value above
   by ANDing corresponding bits together so the result is:

      0000 0000 0000 0000 0000 0000 0000 0010

  This is decimal value 2 so that will be the output. Executing the code below will show
  that this is the case.
*/

int main(void)
{
   unsigned s = 555;

   int i = (s >> 4) & ~(~0 << 3);
   cout << i;
   cout << endl;
}