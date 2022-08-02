#ifndef GRAPHICS_OPERATIONS
#define GRAPHICS_OPERATIONS

#include "ezdraw.h"

void openWindow();     // initialize drawing surface
void viewWindow();     // wait until a key is pressed
void eraseWindow();    // erase the drawing window
void closeWindow();    // close the drawing surface

// wait secs seconds before executing next instruction
void delayWindow(double secs);
// return true if a key pressed; otherwise, return false  
bool keyPress();		

// ***********************************************************
//      graphic functions implementation
// ***********************************************************

void openWindow()
{
   ezdInitialize();
}

void viewWindow()
{
   ezdWaitForKeyPress();
}

void eraseWindow()
{
   ezdClearDrawSurface();
}

void closeWindow()
{
   ezdCleanUp();
}

void delayWindow(double secs)
{
   ezdWait((EZDUINT)(secs * 1000));
}

bool keyPress()
{
   if (ezdKeyPress() != 0)
      return true;
   else
      return false;
}

#endif	// GRAPHICS_OPERATIONS