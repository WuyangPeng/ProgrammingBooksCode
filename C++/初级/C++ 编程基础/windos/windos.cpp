#include "windos.h"
#include "keys.h"
#include <conio.h>

int windos::getkey()
{
const int UpArrow = 72;
const int DnArrow = 80;
 int extch ;
 char ch;

 ch = getch();
 int Result = ch;
 if (ch == 0)
   {
   extch = getch();
   if (extch == UpArrow)
     Result = K_Up;
   else if (extch == DnArrow)
     Result = K_Down;
   }

 return Result;
}
       
void windos::clrscr()
{
  ::clrscr();
}

int windos::ScreenRows()
{
  return 25;
}

void windos::ScreenGetCursor(int& row, int& col)
{
  row = wherey();
  col = wherex();
}

