 /* '09 Main.cpp' */

 /* File stream header file */
#include <fstream.h>
 /* Input Output stream header file */
#include <iostream>

 /* Start */
main (void)
{
  /* File streams */
 fstream   InputFile;
 fstream   OutputFile;

  /* Program data */
 char  InputFileName [256];
 char  OutputFileName [256];
 char  TempInLine [256];
 char  TempOutLine [256];

 long  CurrentLine = 0;

  /* Get file names */
 std::cout << "Input file name: ";
 std::cin >> InputFileName;
 std::cout << "Output file name: ";
 std::cin >> OutputFileName;

  /* Open files */
 InputFile.open (InputFileName, ios::in);

 if (InputFile.is_open ())
 {
  OutputFile.open (OutputFileName, ios::out);
  
  if (OutputFile.is_open ())
  {
   while (1)
   {
     /* Increase line count */
    if (EOF == InputFile.peek ())
    {
     break;
    }

     /* Get the line and increase line count */
    CurrentLine ++;
    InputFile.getline (TempInLine, 256);
 
     /* Format the line with the line number and write to the file */
    sprintf (TempOutLine, "%ld: %s\n", CurrentLine, TempInLine);
    OutputFile << TempOutLine;
   }

   OutputFile.close ();
  }
  InputFile.close ();
 }

 return 0;
}