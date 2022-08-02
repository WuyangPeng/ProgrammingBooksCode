 /* '10 Main.cpp' */

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
 char IsMarriedReturn;
 bool IsMarried;

  /* Open the file for output */
 File.open ("Data.bin", ios::out | ios::binary);

  /* If file was opened successfully continue */
 if (File.is_open ())
 {
  std::cout << "What is your first name: ";
  std::cin >> FirstName;
  std::cout << "What is your last name: ";
  std::cin >> LastName;
  std::cout << "What is your age: ";
  std::cin >> Age;

  std::cout << "Are you married (y for yes, anything else for no): ";
  std::cin >> IsMarriedReturn;

  if ((IsMarriedReturn == 'y' || IsMarriedReturn == 'Y'))
  {
   IsMarried = true;
  }
  else
  {
   IsMarried = false;
  }

   /* Write data to file */
  File.write ((char *) &FirstName, sizeof (char) * 256);
  File.write ((char *) &LastName, sizeof (char) * 256);
  File.write ((char *) &Age, sizeof (int)  );
  File.write ((char *) &IsMarried, sizeof (bool) );

  /* Close file */
  File.close ();
 }

 return 0;
}