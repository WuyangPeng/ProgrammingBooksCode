 /* 'mrMouse.h' */

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

 /* Mirus Mouse class */
class mrMouse
{
protected:
  /* DirectInput objects */
 LPDIRECTINPUTDEVICE8 m_lpkDIDevice;
 DIDEVICEOBJECTDATA   m_akDeviceData [8];

public:
  /* Constructors / Destructor */
 mrMouse (void);
 ~mrMouse (void);

  /* Mouse manipulation routines */
 mrError32 Init (HWND hWindow);
 mrError32 Update (void);

 mrBool32 IsButtonDown (mrUInt32 iButton);
 mrBool32 IsButtonUp (mrUInt32 iButton);
 mrUInt32 GetXAxis (void);
 mrUInt32 GetYAxis (void);

 mrError32 Clear (void);
};