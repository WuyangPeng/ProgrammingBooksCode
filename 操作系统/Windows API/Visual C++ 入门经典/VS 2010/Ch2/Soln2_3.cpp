// Soln2_3.cpp

/*
  1 + 2 + 3 + 4 is executed as:

  (((1 + 2) + 3) + 4)

  because addition is left-associative.
*/

/*
  16 * 4 / 2 * 3 is executed as:

  (((16 * 4) / 2) * 3)

  because multiply and divide are left asociative and of equal precedence. 
  The result will be 96
  If you want the numerator to be 16*4 and the denominator to be 2*3 you write
  the expression as:

  (16 * 4)/(2 * 3)

  The result of this expression will be 10.

*/

/*
  a > b ? a : c > d ? e : f is executed as:

  a > b ? a : (c > d ? e : f)

  because the conditional operator ?: is right_associative>
*/

/*
  a & b && c & d is executed as:

  (a & b) && (c & d)

  because the & operator is of higher precedence than the && operator
  so & operation are executed first.

*/