 /* '02 Main.cpp' */

 /* ConLib header file */
#include "ConLib.h"
 /* CGame header file */
#include "02 Game.h"

 /* Start */
void main ()
{
 ConLib        Console;
 CGame         Game (&Console);

  /* Set window title */
 Console.SetTitle ("Monster");

  /* Start and run game */
 while (Game.GetStatus () != GameExit)
 {
  Game.Process ();
 }
}