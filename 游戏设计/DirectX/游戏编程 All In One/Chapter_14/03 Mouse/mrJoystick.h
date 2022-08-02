 /* 'mrJoystick.h' */

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

 /* Joystick enumeration callback */
BOOL CALLBACK EnumJoysticksCallback (
        const DIDEVICEINSTANCE * pdidInstance, VOID* pContext);

 /* Mirus Joystick class */
class mrJoystick
{
protected:
  /* DirectInput objects */
 LPDIRECTINPUTDEVICE8 m_lpkDIDevice;
 DIJOYSTATE2          m_kDeviceData;

public:
  /* Constructors / Destructor */
 mrJoystick (void);
 ~mrJoystick (void);

  /* Joystick manipulation methods */
 mrError32 Init (HWND hWindow, mrInt32 iMin, mrInt32 iMax, 
                 mrInt32 iDeadZone);
 mrError32 Update (void);

 mrBool32 IsButtonDown (mrUInt32 iButton);
 mrBool32 IsButtonUp (mrUInt32 iButton);

 mrUInt32 GetXAxis (void);
 mrUInt32 GetYAxis (void);
};