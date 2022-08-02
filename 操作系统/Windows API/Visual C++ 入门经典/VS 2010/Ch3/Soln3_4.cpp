// Soln3_4.cpp

/* This is a good test of your ability to work with hexadecimal values
   and individual bits. Remember, each hexadecimal digit defines 4 bits.
   There are six different combinations for the file open mode,
   read, write or append combined with each of text and binary modes.
   You can therefore set modes in a loop with six iterations.
*/

#include <iostream>
using std::cout;

const int text = 0x01;
const int binary = 0x02;

const int read = 0x10;
const int write = 0x20;
const int append = 0x40;

int main()
{
  int mode = 0;              // File open mode
  for(int modeSelect = 0 ; modeSelect<6 ; modeSelect++)
  {
    // Set a different mode for each loop iteration
    switch(modeSelect)
    {
    case 0:
      mode = text | read;
      break;
    case 1:
      mode = text | write;
      break;
    case 2:
      mode = text | append;
      break;
    case 3:
      mode = binary | read;
      break;
    case 4:
      mode = binary | write;
      break;
    case 5:
      mode = binary | append;
      break;
    }
 
    // Determine the mode that is set and output it
    if (mode & text)
      cout << "mode is (text,";
    else if (mode & binary)
      cout << "mode is (binary,";

    if (mode & read)
      cout << "read)\n";
    else if (mode & write)
      cout << "write)\n";
    else if (mode & append)
      cout << "append)\n";
  }

   return 0;
}
