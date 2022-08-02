// PongMain.cpp
// Driver program for the game of Pong
#include <iostream>
#include "Pong.h" // Pong class definition
using namespace std;

// If running on Windows, include windows.h and define WinMain function
#if OGRE_PLATFORM==PLATFORM_WIN32 || OGRE_PLATFORM==OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

int WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )

// If not, define normal main function
#else
int main()
#endif
{
   try
   {
      Pong game; // create a Pong object
      game.run(); // start the Pong game
   } // end try
   catch ( runtime_error &error )
   {
      #if OGRE_PLATFORM==PLATFORM_WIN32 || OGRE_PLATFORM==OGRE_PLATFORM_WIN32
      MessageBoxA( NULL, error.what(), "Exception Thrown!",
         MB_OK | MB_ICONERROR | MB_TASKMODAL );
      #else
      cerr << "Exception Thrown: " << error.what() << endl;
      #endif
   } // end catch
} // end main

/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
