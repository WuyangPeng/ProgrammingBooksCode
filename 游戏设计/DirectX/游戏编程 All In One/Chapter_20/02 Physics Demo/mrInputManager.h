 /* 'mrInputManager.h' */

 /* Mirus base types header */
#include "mrDatatypes.h"
 /* Mirus error definitions header */
#include "mrError.h"
 /* Windows header file */
#include <windows.h>
 /* Direct Music header file */
#include <dinput.h>
/* Assert header file */
#include <assert.h> 

 /* Include this file only once */
#pragma once

 /* Mirus Input Manager class */
class mrInputManager
{
protected:
  /* DirectInput objects */
 LPDIRECTINPUT8         m_lpkDInput;

  /* Singleton */
 static mrInputManager * m_pkSingleton;

public:
  /* Constructors / Destructor */
 mrInputManager (void);
 ~mrInputManager (void);

  /* Input devices manipulation routines */
 mrError32 Init (HINSTANCE hInstance);
 LPDIRECTINPUT8 GetInput (void);

  /* Singleton */
 static mrInputManager * GetSingleton (void);
};