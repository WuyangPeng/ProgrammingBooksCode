 /* '06 Main.cpp' */

 /* File stream header file */
#include <fstream.h>
 /* Input Output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* File stream */
 fstream   File;

 std::cout << "Trying to open Data.txt for output..." << std::endl;
  /* Open the file normally */
 File.open ("Data.txt", ios::out);
 if (File.is_open ())
 {
  std::cout << "File opened sucessfully..." << std::endl;
 }
 else
 {
  std::cout << "File not opened..." << std::endl;
 }
 File.close ();

  /* Open the file without replacing */
 std::cout << "Trying to open Data.txt with ";
 std::cout << "ios::noreplace..." << std::endl;

 File.open ("Data.txt", ios::out | ios::noreplace);
 if (File.is_open ())
 {
  std::cout << "File opened sucessfully..." << std::endl;
 }
 else
 {
  std::cout << "File not opened..." << std::endl;
 }
 File.close ();

  /* Open the file without creating */
 std::cout << "Trying to open Data2.txt with ";
 std::cout << "ios::nocreate..." << std::endl;

 File.open ("Data2.txt", ios::out | ios::nocreate);
 if (File.is_open ())
 {
  std::cout << "File opened sucessfully..." << std::endl;
 }
 else
 {
  std::cout << "File not opened..." << std::endl;
 }
 File.close ();
 
 return 0;
}