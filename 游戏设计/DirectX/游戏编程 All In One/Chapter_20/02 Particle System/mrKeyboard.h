 /* 'mrKeyboard.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Mirus Input Manafer header file */
#include "mrInputManager.h"
 /* Windows header file */
#include <windows.h>
 /* Direct Music header file */
#include <dinput.h>

 /* Include this file only once */
#pragma once

 /* Mirus Keyboard class */
class mrKeyboard
{
protected:
  /* DirectInput objects */
 LPDIRECTINPUTDEVICE8 m_lpkDIDevice;

  /* Our key buffer */
 mrUInt8              m_iKeyBuffer [256];

public:
  /* Constructors / Destructor */
 mrKeyboard (void);
 ~mrKeyboard (void);

  /* Keyboard manipulation routines */
 mrError32 Init (HWND hWindow);
 mrError32 Update (void);

 mrBool32 IsButtonDown (mrUInt32 iButton);
 mrBool32 IsButtonUp (mrUInt32 iButton);
};