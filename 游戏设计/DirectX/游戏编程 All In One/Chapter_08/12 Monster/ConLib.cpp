 /* 'ConLib.cpp' */

 /* ConLib complement header file */
#include "ConLib.h"

 /* Get standard screen and keyboard handles */
ConLib::ConLib ()
{
 m_Screen = GetStdHandle (STD_OUTPUT_HANDLE);
 m_Keyboard = GetStdHandle (STD_INPUT_HANDLE);
 
 SetTextColor (ConRed | ConGreen | ConBlue);
 SetBackgroundColor (0);
}

 /* Does nothing */
ConLib::~ConLib ()
{

}

 /* Sets background color */
void ConLib::SetBackgroundColor (WORD Color)
{
 m_BackgroundColor = 0;

  /* Use bit manipulation to get the color combinations */
 if (Color & ConRed)
 {
  m_BackgroundColor |= BACKGROUND_RED;
 }
 if (Color & ConGreen)
 {
  m_BackgroundColor |= BACKGROUND_GREEN;
 }
 if (Color & ConBlue)
 {
  m_BackgroundColor |= BACKGROUND_BLUE;
 }

  /* Set the color using combinations from above */
 SetConsoleTextAttribute (m_Screen, m_TextColor | m_BackgroundColor);
}


 /* Sets text color */
void ConLib::SetTextColor (WORD Color)
{
 m_TextColor = 0;

  /* Use bit manipulation to get the color combinations */
 if (Color & ConRed)
 {
  m_TextColor |= FOREGROUND_RED;
 }
 if (Color & ConGreen)
 {
  m_TextColor |= FOREGROUND_GREEN;
 }
 if (Color & ConBlue)
 {
  m_TextColor |= FOREGROUND_BLUE;
 }

  /* Set the color using combinations from above */
 SetConsoleTextAttribute (m_Screen, m_TextColor | m_BackgroundColor);
}

 /* Sets window title */
void ConLib::SetTitle (char * Title)
{
 SetConsoleTitle (Title);
}

 /* Clears the screen */
void ConLib::Clear (void)
{
 COORD Start;
 DWORD Written;

 Start.X = 0;
 Start.Y = 0;

 FillConsoleOutputAttribute (m_Screen, m_TextColor | m_BackgroundColor, 
                             80*25, Start, &Written);
 FillConsoleOutputCharacter (m_Screen, ' ', 
                             80*25, Start, &Written);
 SetConsoleCursorPosition (m_Screen, Start);
}

 /* Sets the cursor position */
void ConLib::SetPosition (COORD Position)
{
 SetConsoleCursorPosition (m_Screen, Position);
}

 /* Sends a string to the screen */
void ConLib::OutputString (char * String)
{
 DWORD Written;

 WriteConsole (m_Screen, String, strlen (String), &Written, NULL);
}

 /* Reads a string from the keyboard */
void ConLib::Read (char * Buffer, DWORD BufferSize)
{
 DWORD Read;

 ReadConsole (m_Keyboard, Buffer, BufferSize, &Read, NULL);
}


 /* Gets a key from the keyboard */
int ConLib::GetKey (void)
{
 DWORD Read;
 INPUT_RECORD Event;

  /* Get console input */
 ReadConsoleInput (m_Keyboard, &Event, 1, &Read);

  /* If input event is a key event see if there is any key pressed
     and return its virtual-key code */
 if (Event.EventType == KEY_EVENT)
 {
  if (Event.Event.KeyEvent.bKeyDown)
  {
   return Event.Event.KeyEvent.wVirtualKeyCode;
  }
 }

 return 0;
}
