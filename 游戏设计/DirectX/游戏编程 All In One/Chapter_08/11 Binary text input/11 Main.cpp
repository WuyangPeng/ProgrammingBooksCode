 /* '11 Main.cpp' */

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
 File.open ("Data.bin", ios::in | ios::binary);

  /* If file was opened successfully continue */
 if (File.is_open ())
 {
   /* Read data from file */
  File.read ((char *) &FirstName, sizeof (char) * 256);
  File.read ((char *) &LastName, sizeof (char) * 256);
  File.read ((char *) &Age, sizeof (int)  );
  File.read ((char *) &IsMarried, sizeof (bool) );

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