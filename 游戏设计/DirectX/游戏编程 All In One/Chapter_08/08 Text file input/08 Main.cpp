 /* '08 Main.cpp' */

 /* File stream header file */
#include <fstream.h>
 /* Input Output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* File stream */
 fstream   File;
  /* Program data */
 char FirstName [256];
 char LastName [256];
 int  Age;
 int  IsMarried;

  /* Open the file for input */
 File.open ("Data.txt", ios::in);

  /* If file was opened successfully continue */
 if (File.is_open ())
 {
   /* Read data from file */
  File >> FirstName >> LastName >> Age >> IsMarried;

  std::cout << "Your name is " << FirstName << " " << LastName;
  std::cout << " and you are " << Age << " years old." << std::endl;

  if (IsMarried == 1)
  {
   std::cout << "Good luck for your marriage!" << std::endl;
  }
  else
  {
   std::cout << "Good luck finding someone!" << std::endl;
  }

   /* Close file */
  File.close ();
 }

 return 0;
}