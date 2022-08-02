 /* 02 Main.cpp */

 /* Standard Input/Output */
#include <stdio.h>


void main ()
{
 short Age;

  /* File */
 FILE *File;

  /* Print message */
 printf ("How old are you? ");
  /* Get input from the user */
 scanf ("%d", &Age);

  /* Open file fro writing in text mode */
 File = fopen ("file.txt", "wt");

  /* Write information to file */
 fprintf (File, "%d", Age);

  /* Close the file */
 fclose (File);

  /* Open file fro writing in text mode */
 File = fopen ("file.txt", "rt");

  /* Read information from file */
 fscanf (File, "%d", &Age);

  /* Close the file */
 fclose (File);

  /* Print the age from read file */
 printf ("You are %d years old.\n", Age);
}