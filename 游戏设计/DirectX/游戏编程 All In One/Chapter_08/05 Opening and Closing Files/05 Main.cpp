 /* '05 Main.cpp' */

 /* File stream header file */
#include <fstream.h>
 /* Input Output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* File streams */
 fstream   FileOne;
 fstream   FileTwo;
 fstream   FileThree;

  /* Open the file for output in text mode */
 FileOne.open ("Data.txt", ios::out);
  /* Open the file for output in binary mode */
 FileTwo.open ("Data.bin", ios::out | ios::binary);
  /* Open the file for output in appending and text mode */
 FileThree.open ("Data.txt", ios::out | ios::app);


  /* Close files */
 FileOne.close ();
 FileTwo.close ();
 FileThree.close ();

 return 0;
}